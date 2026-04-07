#include "LineMutations.h"
#include "PluginProcessor.h"

// ── RidgeBump Implementation ──

RidgeBump::RidgeBump(Orientation orientation)
    : orientation(orientation)
{
}

void RidgeBump::setValue(float v)
{
    value = juce::jlimit(0.0f, 1.0f, v);
    dirty = true;
}

float RidgeBump::getValue() const
{
    return value;
}

bool RidgeBump::hitTest(juce::Point<float> point) const
{
    return bounds.contains(point);
}

void RidgeBump::setBounds(juce::Rectangle<float> b)
{
    bounds = b;
    dirty = true;
}

juce::Path RidgeBump::generateRidgePath(float baseX, float baseY, float lineThickness)
{
    juce::Path ridge;
    
    if (orientation == Orientation::Vertical)
    {
        float height = bounds.getHeight();
        float width = bounds.getWidth();
        float peakHeight = height * value;
        float peakX = bounds.getCentreX();
        
        // Start at bottom
        ridge.startNewSubPath(baseX, baseY);
        
        // Build vertical bump with peak at value position
        float segments = 20.0f;
        for (float i = 0; i <= segments; i += 1.0f)
        {
            float t = i / segments;
            float x = baseX + t * width;
            
            // Gaussian-like curve for the bump
            float bumpHeight = peakHeight * std::exp(-std::pow((t - 0.5f) * 4.0f, 2.0f));
            float y = baseY - bumpHeight;
            
            ridge.lineTo(x, y);
        }
    }
    else // Horizontal
    {
        float width = bounds.getWidth();
        float peakWidth = width * value;
        float peakY = bounds.getCentreY();
        
        ridge.startNewSubPath(baseX, baseY);
        
        float segments = 20.0f;
        for (float i = 0; i <= segments; i += 1.0f)
        {
            float t = i / segments;
            float y = baseY + t * bounds.getHeight();
            
            float bumpWidth = peakWidth * std::exp(-std::pow((t - 0.5f) * 4.0f, 2.0f));
            float x = baseX + bumpWidth;
            
            ridge.lineTo(x, y);
        }
    }
    
    return ridge;
}

// ── LoopKnot Implementation ──

float LoopKnot::calculateTightness() const
{
    return 0.3f + (value * 0.7f); // 0.3 = loose, 1.0 = tight
}

void LoopKnot::setValue(float v)
{
    value = juce::jlimit(0.0f, 1.0f, v);
    dirty = true;
}

float LoopKnot::getValue() const
{
    return value;
}

bool LoopKnot::hitTest(juce::Point<float> point) const
{
    auto centre = bounds.getCentre();
    float dist = point.getDistanceFrom(centre);
    return dist < bounds.getWidth() * 0.6f;
}

void LoopKnot::setBounds(juce::Rectangle<float> b)
{
    bounds = b;
    dirty = true;
}

juce::Path LoopKnot::generateLoopPath(float anchorX, float anchorY, float baseThickness)
{
    juce::Path loop;

    if (bounds.isEmpty()) return loop;

    float tightness = calculateTightness();
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

    float loopRadius = radius * (1.2f - tightness * 0.5f);

    int wraps = 2 + (int)(tightness * 2.0f);

    loop.startNewSubPath(anchorX, anchorY);

    float angleStep = 0.15f;

    for (int w = 0; w < wraps; w++)
    {
        for (float angle = 0.0f; angle < juce::MathConstants<float>::twoPi; angle += angleStep)
        {
            float r = loopRadius * (1.0f - (float)w / wraps * 0.3f);
            float wobble = std::sin(angle * 3.0f + phase) * 2.0f;
            float x = anchorX + std::cos(angle) * (r + wobble);
            float y = anchorY + std::sin(angle) * (r + wobble);
            loop.lineTo(x, y);
        }
    }

    loop.lineTo(anchorX, anchorY);

    return loop;
}

// ── PulseLine Implementation ──

PulseLine::PulseLine()
{
    for (auto& buf : displayData)
        for (int i = 0; i < kTargetPointCount; i++)
            buf[i] = std::sin(i * 0.2f) * 0.5f + std::sin(i * 0.5f) * 0.2f;
}

void PulseLine::setValue(float v)
{
    value = v;
    // PulseLine doesn't use value the same way
}

float PulseLine::getValue() const
{
    return value;
}

bool PulseLine::hitTest(juce::Point<float> point) const
{
    return bounds.contains(point);
}

void PulseLine::setBounds(juce::Rectangle<float> b)
{
    bounds = b;
}

void PulseLine::updateFromProcessor(TonyPlugsProcessor& processor)
{
    if (!processor.waveformReady.load(std::memory_order_acquire))
        return;

    int srcIdx = 1 - processor.writeBufferIndex.load(std::memory_order_acquire);
    auto& srcBuffer = processor.waveformBuffer[srcIdx];

    int writeIdx = writeBufferIndex.load(std::memory_order_relaxed);
    int copyCount = juce::jmin((int)srcBuffer.size(), kTargetPointCount);
    for (int i = 0; i < copyCount; i++)
    {
        displayData[writeIdx][i] = srcBuffer[i];
    }

    std::atomic_thread_fence(std::memory_order_release);
    writeBufferIndex.store(1 - writeIdx, std::memory_order_relaxed);
    dataReady.store(true, std::memory_order_relaxed);
}

juce::Path PulseLine::generatePulsePath(float startX, float startY, float length, float baseThickness)
{
    juce::Path pulse;

    if (!dataReady.load(std::memory_order_acquire))
        return pulse;

    int readIdx = 1 - writeBufferIndex.load(std::memory_order_acquire);
    const auto& localData = displayData[readIdx];

    float step = length / (float)(kTargetPointCount - 1);

    for (int i = 0; i < kTargetPointCount; i++)
    {
        float x = startX + i * step;

        float wobble1 = std::sin(i * 0.1f + phase) * 3.0f * value;
        float wobble2 = std::sin(i * 0.03f + phase * 0.5f) * 1.5f * value;

        float amplitude = localData[i] * 40.0f;

        float y = startY + amplitude + wobble1 + wobble2;

        if (i == 0) pulse.startNewSubPath(x, y);
        else        pulse.lineTo(x, y);
    }

    return pulse;
}
