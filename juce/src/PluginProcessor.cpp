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
void TonyPlugsProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = getTotalNumOutputChannels();

    osc.initialise([](float x) { return std::sin(x); }, 128);
    osc.prepare(spec);
    osc.setFrequency(440.0f);

    lfo.initialise([](float x) { return std::sin(x); }, 128);
    lfo.prepare(spec);
    lfo.setFrequency(0.05f);

    gain.prepare(spec);
    gain.setGainLinear(1.0f);

    oscPhase = 0.0f;
    lfoPhase = 0.0f;

    for (auto& buf : waveformBuffer)
        buf.fill(0.0f);
}

void TonyPlugsProcessor::releaseResources()
{
    osc.reset();
    lfo.reset();
    gain.reset();
}

void TonyPlugsProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, numSamples);

    auto freqValue = apvts.getRawParameterValue("freq")->load();
    auto wobbleValue = apvts.getRawParameterValue("wobble")->load();
    auto gainValue = apvts.getRawParameterValue("gain")->load();

    float lfoFreq = 0.05f + wobbleValue * 5.0f;
    float lfoPhaseInc = static_cast<float>(lfoFreq / currentSampleRate);
    float wobbleDepth = wobbleValue * 50.0f;

    gain.setGainLinear(gainValue);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float lfoPhaseNorm = lfoPhase - static_cast<float>(std::floor(lfoPhase));
        auto lfoOutput = lfo.processSample(lfoPhaseNorm);

        float freqMod = lfoOutput * wobbleDepth;
        float modulatedFreq = juce::jlimit(20.0f, 2000.0f, freqValue + freqMod);
        float samplePhaseInc = static_cast<float>(modulatedFreq / currentSampleRate);

        float oscPhaseNorm = oscPhase - static_cast<float>(std::floor(oscPhase));
        float sampleValue = osc.processSample(oscPhaseNorm);

        oscPhase += samplePhaseInc;
        if (oscPhase >= 1.0f) oscPhase -= static_cast<float>(std::floor(oscPhase));

        lfoPhase += lfoPhaseInc;
        if (lfoPhase >= 1.0f) lfoPhase -= static_cast<float>(std::floor(lfoPhase));

        for (int ch = 0; ch < totalNumOutputChannels; ++ch)
        {
            float inputSample = (ch < totalNumInputChannels) ? buffer.getSample(ch, sample) : 0.0f;
            buffer.setSample(ch, sample, inputSample + sampleValue);
        }
    }

    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> ctx(block);
    gain.process(ctx);

    if (numSamples > 0)
    {
        int writeIdx = writeBufferIndex.load(std::memory_order_relaxed);
        auto* channelData = buffer.getReadPointer(0);
        auto numToCopy = juce::jmin(numSamples, (int)waveformBuffer[0].size());

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
