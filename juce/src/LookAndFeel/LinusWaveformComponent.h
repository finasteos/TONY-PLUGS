#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class LinusWaveformComponent : public juce::Component,
                                private juce::Timer
{
public:
    explicit LinusWaveformComponent(TonyPlugsProcessor& processor);
    ~LinusWaveformComponent() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setWobbleAmount(float amount) { wobbleAmount = amount; }

private:
    void timerCallback() override;
    void updateFromProcessor();
    float calculateAverageAmplitude() const;

    TonyPlugsProcessor& processorRef;

    float wobblePhase = 0.0f;
    float wobbleAmount = 0.5f;
    std::vector<float> displayPoints;

    static constexpr int kTargetPointCount = 128;
    static constexpr float kBaseThickness = 6.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinusWaveformComponent)
};
