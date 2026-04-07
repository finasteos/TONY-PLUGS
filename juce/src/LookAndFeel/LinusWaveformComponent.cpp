#include "LinusWaveformComponent.h"
#include "LinusLookAndFeel.h"

LinusWaveformComponent::LinusWaveformComponent(TonyPlugsProcessor& processor)
    : processorRef(processor)
{
    displayPoints.resize(kTargetPointCount);
    for (int i = 0; i < kTargetPointCount; ++i)
    {
        displayPoints[i] = std::sin(i * 0.2f) * 0.5f + std::sin(i * 0.5f) * 0.2f;
    }

    startTimerHz(30);
}

LinusWaveformComponent::~LinusWaveformComponent()
{
    stopTimer();
}

void LinusWaveformComponent::timerCallback()
{
    wobblePhase += 0.05f;
    updateFromProcessor();
    repaint();
}

void LinusWaveformComponent::updateFromProcessor()
{
    if (!processorRef.waveformReady.load(std::memory_order_acquire))
        return;

    int readIdx = 1 - processorRef.writeBufferIndex.load(std::memory_order_acquire);
    auto& buffer = processorRef.waveformBuffer[readIdx];

    int copyCount = juce::jmin((int)buffer.size(), kTargetPointCount);
    for (int i = 0; i < copyCount; ++i)
    {
        displayPoints[i] = buffer[i];
    }
}

float LinusWaveformComponent::calculateAverageAmplitude() const
{
    float sum = 0.0f;
    for (float p : displayPoints)
        sum += std::abs(p);
    return sum / (float)displayPoints.size();
}

void LinusWaveformComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(bounds, 20.0f);

    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.drawRoundedRectangle(bounds, 20.0f, 4.0f);

    float waveWidth = bounds.getWidth() - 40.0f;
    float waveHeight = bounds.getHeight() - 60.0f;
    float stepSize = waveWidth / (float)(displayPoints.size() - 1);

    juce::Path waveformPath;
    float avgAmp = calculateAverageAmplitude();
    float dynamicThickness = kBaseThickness + (avgAmp * 4.0f);

    for (size_t i = 0; i < displayPoints.size(); ++i)
    {
        float x = bounds.getX() + 20.0f + i * stepSize;
        float wobble1 = std::sin(i * 0.1f + wobblePhase) * 3.0f * wobbleAmount;
        float wobble2 = std::sin(i * 0.03f + wobblePhase * 0.5f) * 1.5f * wobbleAmount;
        float y = bounds.getCentreY() + displayPoints[i] * waveHeight * 0.35f
                  + wobble1 + wobble2;

        if (i == 0) waveformPath.startNewSubPath(x, y);
        else        waveformPath.lineTo(x, y);
    }

    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.strokePath(waveformPath, juce::PathStrokeType(
        dynamicThickness * 1.4f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    g.setColour(juce::Colours::white);
    g.strokePath(waveformPath, juce::PathStrokeType(
        dynamicThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font{}.withHeight(10.0f).withTypefaceStyle("Bold"));
    g.drawText("WOBBLY OSCILLOSCOPE",
               bounds.removeFromTop(24).reduced(12, 0),
               juce::Justification::topLeft);
}

void LinusWaveformComponent::resized()
{
}
