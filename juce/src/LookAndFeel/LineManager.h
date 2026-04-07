#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"
#include "LineMutations/LineMutations.h"

class LineManager : public juce::Component,
                    private juce::Timer
{
public:
    explicit LineManager(TonyPlugsProcessor& processor);
    ~LineManager() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

private:
    void timerCallback() override;
    void rebuildCombinedPath();
    void updateValuesFromProcessor();

    enum class InteractionTarget { None, GainRidge, FreqLoop, WobbleLoop };
    InteractionTarget findInteractionTarget(juce::Point<float> point);

    std::unique_ptr<RidgeBump> gainRidge;
    std::unique_ptr<LoopKnot> freqLoop;
    std::unique_ptr<LoopKnot> wobbleLoop;
    std::unique_ptr<PulseLine> audioPulse;

    juce::Path combinedLine;
    float globalPhase = 0.0f;
    bool needsRebuild = true;

    TonyPlugsProcessor& processorRef;
    InteractionTarget activeInteraction = InteractionTarget::None;

    static constexpr float kBaseThickness = 8.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LineManager)
};
