#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class TonyPlugsProcessor;

class LineMutation
{
public:
    virtual ~LineMutation() = default;

    virtual void setValue(float v) = 0;
    virtual float getValue() const = 0;
    virtual bool hitTest(juce::Point<float> point) const = 0;
    virtual void setPhase(float p) { phase = p; }

    juce::Rectangle<float> getBounds() const { return bounds; }

protected:
    float value = 0.5f;
    float phase = 0.0f;
    bool dirty = true;
    juce::Rectangle<float> bounds;
};
