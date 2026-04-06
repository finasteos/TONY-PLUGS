#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/**
 * LinusLookAndFeel — Custom LookAndFeel_V4 for the La Linea / Linus design language.
 *
 * Design tokens:
 * - Knob track: 12px thick, rounded caps
 * - Colors: white on bold backgrounds
 * - Ink-bleed: multi-pass path rendering
 * - Wobble: dual-sine displacement
 */
class LinusLookAndFeel : public juce::LookAndFeel_V4
{
public:
    LinusLookAndFeel();
    ~LinusLookAndFeel() override = default;

    // ── Rotary Slider (Chunky Knob) ──
    void drawRotarySlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override;

    // ── Linear Slider ──
    void drawLinearSlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          juce::Slider::SliderStyle style,
                          juce::Slider& slider) override;

    // ── Ink-Bleed Helpers ──
    static void drawInkBleedPath(juce::Graphics& g,
                                  const juce::Path& path,
                                  float baseThickness,
                                  juce::Colour color);

    // ── Wobbly Path Generator ──
    static juce::Path generateWobblyPath(const std::vector<float>& points,
                                          float width, float height,
                                          float phase, bool isWobbly);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinusLookAndFeel)
};
