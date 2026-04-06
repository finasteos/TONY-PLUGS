#include "PluginProcessor.h"
#include "PluginEditor.h"

// ── Constructor ──
TonyPlugsProcessor::TonyPlugsProcessor()
    : AudioProcessor(BusesProperties()
          .withInput("Input", juce::AudioChannelSet::stereo(), true)
          .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameterLayout())
{
}

TonyPlugsProcessor::~TonyPlugsProcessor() = default;

// ── Parameter Layout ──
juce::AudioProcessorValueTreeState::ParameterLayout TonyPlugsProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Gain: 0-100%
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"gain", 1},
        "Gain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.5f));

    // Frequency: 20Hz - 2kHz (skewed for musical response)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"freq", 1},
        "Frequency",
        juce::NormalisableRange<float>(20.0f, 2000.0f, 1.0f, 0.3f),
        440.0f));

    // Wobble Amount: how much "hand-drawn" feel
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"wobble", 1},
        "Wobble",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
        0.5f));

    return { params.begin(), params.end() };
}

// ── Audio Processing ──
void TonyPlugsProcessor::prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/)
{
    // Initialize DSP chain here
}

void TonyPlugsProcessor::releaseResources()
{
    // Free DSP resources here
}

void TonyPlugsProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Apply gain
    auto gainValue = apvts.getRawParameterValue("gain")->load();
    buffer.applyGain(gainValue);

    // Copy waveform data for editor visualization (lock-free double-buffering)
    if (buffer.getNumSamples() > 0)
    {
        int writeIdx = writeBufferIndex.load(std::memory_order_relaxed);
        auto* channelData = buffer.getReadPointer(0);
        auto numToCopy = juce::jmin(buffer.getNumSamples(), (int)waveformBuffer[0].size());

        for (int i = 0; i < numToCopy; ++i)
            waveformBuffer[writeIdx][i] = channelData[i];

        std::atomic_thread_fence(std::memory_order_release);
        waveformReady.store(true, std::memory_order_relaxed);
        writeBufferIndex.store(1 - writeIdx, std::memory_order_relaxed);
    }
}

// ── Editor ──
juce::AudioProcessorEditor* TonyPlugsProcessor::createEditor()
{
    return new TonyPlugsEditor(*this);
}

// ── State Persistence ──
void TonyPlugsProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void TonyPlugsProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(apvts.state.getType()))
        apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

// ── Plugin Instantiation ──
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TonyPlugsProcessor();
}
