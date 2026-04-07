#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

class TonyPlugsProcessor : public juce::AudioProcessor
{
public:
    TonyPlugsProcessor();
    ~TonyPlugsProcessor() override;

    // ── AudioProcessor Overrides ──
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    // ── Editor ──
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    // ── Plugin Properties ──
    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    // ── Presets ──
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    // ── State ──
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // ── Parameter Access ──
    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }

    // ── Waveform Data (for Editor visualization) ──
    std::array<float, 512> waveformBuffer[2];
    std::atomic<int> writeBufferIndex{0};
    std::atomic<bool> waveformReady{ false };

private:
    juce::AudioProcessorValueTreeState apvts;
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // ── DSP Chain ──
    juce::dsp::Oscillator<float> osc;
    juce::dsp::Oscillator<float> lfo;
    juce::dsp::Gain<float> gain;

    double currentSampleRate = 44100.0;
    float oscPhase = 0.0f;
    float lfoPhase = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TonyPlugsProcessor)
};
