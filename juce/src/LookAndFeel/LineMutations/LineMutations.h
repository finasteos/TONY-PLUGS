#pragma once

#include "LineMutation.h"
#include "PluginProcessor.h"

class RidgeBump : public LineMutation
{
public:
    enum class Orientation { Horizontal, Vertical };

    RidgeBump(Orientation orientation = Orientation::Vertical);

    void setValue(float v) override;
    float getValue() const override;
    bool hitTest(juce::Point<float> point) const override;

    void setBounds(juce::Rectangle<float> b);
    juce::Path generateRidgePath(float baseX, float baseY, float lineThickness);

private:
    Orientation orientation;
};

class LoopKnot : public LineMutation
{
public:
    void setValue(float v) override;
    float getValue() const override;
    bool hitTest(juce::Point<float> point) const override;

    void setBounds(juce::Rectangle<float> b);
    juce::Path generateLoopPath(float anchorX, float anchorY, float baseThickness);

private:
    float calculateTightness() const;
};

class PulseLine : public LineMutation
{
public:
    PulseLine();

    void setValue(float v) override;
    float getValue() const override;
    bool hitTest(juce::Point<float> point) const override;

    void setBounds(juce::Rectangle<float> b);
    void updateFromProcessor(TonyPlugsProcessor& processor);
    juce::Path generatePulsePath(float startX, float startY, float length, float baseThickness);

private:
    std::vector<float> displayData;
    std::atomic<int> readBuffer{0};
    static constexpr int kTargetPointCount = 128;
};
