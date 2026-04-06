#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include "PluginProcessor.h"
#include "LookAndFeel/LinusLookAndFeel.h"
#include "LookAndFeel/LinusWaveformComponent.h"

class TonyPlugsEditor : public juce::AudioProcessorEditor,
                         private juce::Timer
{
public:
    explicit TonyPlugsEditor(TonyPlugsProcessor&);
    ~TonyPlugsEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    // ── References ──
    TonyPlugsProcessor& processorRef;

    // ── Custom LookAndFeel ──
    LinusLookAndFeel linusLookAndFeel;

    // ── Controls ──
    juce::Slider gainSlider;
    juce::Slider freqSlider;
    juce::Slider wobbleSlider;
    juce::Label  gainLabel;
    juce::Label  freqLabel;
    juce::Label  wobbleLabel;

    // ── APVTS Attachments ──
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wobbleAttachment;

    // ── Waveform Component ──
    LinusWaveformComponent waveformComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TonyPlugsEditor)
};
