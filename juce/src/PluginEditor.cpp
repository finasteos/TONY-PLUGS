#include "PluginEditor.h"

// ── La Linea Colors ──
namespace LinusColours
{
    const juce::Colour cobaltBlue  { 0xFF1E5AA8 };
    const juce::Colour grassGreen  { 0xFF2E8B57 };
    const juce::Colour sunnyYellow { 0xFFF4D03F };
}

// ── Constructor ──
TonyPlugsEditor::TonyPlugsEditor(TonyPlugsProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), waveformComponent(p)
{
    // Apply La Linea style
    setLookAndFeel(&linusLookAndFeel);

    // Window size
    setSize(700, 500);

    // ── Gain Knob ──
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(gainSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getAPVTS(), "gain", gainSlider);

    gainLabel.setText("GAIN", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(gainLabel);

    // ── Freq Knob ──
    freqSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    freqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(freqSlider);
    freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getAPVTS(), "freq", freqSlider);

    freqLabel.setText("FREQ", juce::dontSendNotification);
    freqLabel.setJustificationType(juce::Justification::centred);
    freqLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(freqLabel);

    // ── Wobble Knob ──
    wobbleSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    wobbleSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(wobbleSlider);
    wobbleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processorRef.getAPVTS(), "wobble", wobbleSlider);

    wobbleLabel.setText("WOBBLE", juce::dontSendNotification);
    wobbleLabel.setJustificationType(juce::Justification::centred);
    wobbleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(wobbleLabel);

    // Start wobble animation at 30fps
    startTimerHz(30);

    addAndMakeVisible(waveformComponent);
}

TonyPlugsEditor::~TonyPlugsEditor()
{
    setLookAndFeel(nullptr);
    stopTimer();
}

// ── Timer: Update Wobble Amount ──
void TonyPlugsEditor::timerCallback()
{
    auto wobbleValue = processorRef.getAPVTS().getRawParameterValue("wobble")->load();
    waveformComponent.setWobbleAmount(wobbleValue);
}

// ── Paint ──
void TonyPlugsEditor::paint(juce::Graphics& g)
{
    // Background: Cobalt Blue
    g.fillAll(LinusColours::cobaltBlue);

    // ── Header ──
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(32.0f, juce::Font::bold));
    g.drawText("TONY PLUGS", getLocalBounds().removeFromTop(60), juce::Justification::centred);

    g.setFont(juce::Font(10.0f));
    g.drawText("LA LINEA EDITION", getLocalBounds().removeFromTop(75),
               juce::Justification::centred);
}

// ── Layout ──
void TonyPlugsEditor::resized()
{
    auto bounds = getLocalBounds();

    // ── Waveform Display ──
    auto waveformArea = bounds.reduced(30).removeFromTop(150);
    waveformArea.setY(80);
    waveformComponent.setBounds(waveformArea);

    // Knob area: bottom half
    auto knobArea = bounds.removeFromBottom(240).reduced(40, 20);
    int knobSize = 120;
    int spacing = (knobArea.getWidth() - knobSize * 3) / 4;

    // Gain
    auto gainArea = knobArea.removeFromLeft(knobSize + spacing).removeFromRight(knobSize);
    gainSlider.setBounds(gainArea.removeFromTop(knobSize));
    gainLabel.setBounds(gainArea.removeFromTop(30));

    // Freq
    auto freqArea = knobArea.removeFromLeft(knobSize + spacing).removeFromRight(knobSize);
    freqSlider.setBounds(freqArea.removeFromTop(knobSize));
    freqLabel.setBounds(freqArea.removeFromTop(30));

    // Wobble
    auto wobbleArea = knobArea.removeFromLeft(knobSize + spacing).removeFromRight(knobSize);
    wobbleSlider.setBounds(wobbleArea.removeFromTop(knobSize));
    wobbleLabel.setBounds(wobbleArea.removeFromTop(30));
}
