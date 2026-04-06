#include "LinusLookAndFeel.h"
#include <cmath>

// ── Constructor ──
LinusLookAndFeel::LinusLookAndFeel()
{
    // Set default colour scheme: white on cobalt blue
    setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);
    setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::white.withAlpha(0.2f));
    setColour(juce::Slider::thumbColourId, juce::Colours::white);
    setColour(juce::Label::textColourId, juce::Colours::white);
}

// ── Chunky Knob: drawRotarySlider ──
void LinusLookAndFeel::drawRotarySlider(
    juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto centre = bounds.getCentre();
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f - 15.0f;

    const float trackThickness = 12.0f; // La Linea signature: chunky!

    // ── Background Track (full circle) ──
    g.setColour(juce::Colours::white.withAlpha(0.2f));
    g.drawEllipse(
        centre.x - radius, centre.y - radius,
        radius * 2.0f, radius * 2.0f,
        trackThickness);

    // ── Active Arc ──
    float activeEndAngle = rotaryStartAngle +
        (rotaryEndAngle - rotaryStartAngle) * sliderPos;

    if (activeEndAngle > rotaryStartAngle + 0.01f)
    {
        juce::Path activeArc;
        activeArc.addCentredArc(
            centre.x, centre.y,
            radius, radius,
            0.0f,
            rotaryStartAngle,
            activeEndAngle,
            true);

        // Apply ink-bleed to active arc
        drawInkBleedPath(g, activeArc, trackThickness, juce::Colours::white);
    }

    // ── Value Text ──
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(20.0f, juce::Font::bold));

    juce::String valueText;
    if (slider.getMaximum() <= 1.0)
        valueText = juce::String((int)(slider.getValue() * 100.0)) + "%";
    else
        valueText = juce::String((int)slider.getValue());

    g.drawText(valueText, bounds, juce::Justification::centred);
}

// ── Linear Slider ──
void LinusLookAndFeel::drawLinearSlider(
    juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
    juce::Slider::SliderStyle style,
    juce::Slider& /*slider*/)
{
    if (style != juce::Slider::LinearHorizontal &&
        style != juce::Slider::LinearVertical)
        return;

    const float trackThickness = 8.0f;

    if (style == juce::Slider::LinearHorizontal)
    {
        float trackY = y + height * 0.5f;

        // Background track
        juce::Path bgPath;
        bgPath.startNewSubPath((float)x, trackY);
        bgPath.lineTo((float)(x + width), trackY);

        g.setColour(juce::Colours::white.withAlpha(0.2f));
        g.strokePath(bgPath, juce::PathStrokeType(
            trackThickness,
            juce::PathStrokeType::curved,
            juce::PathStrokeType::rounded));

        // Active track
        juce::Path activePath;
        activePath.startNewSubPath((float)x, trackY);
        activePath.lineTo(sliderPos, trackY);

        drawInkBleedPath(g, activePath, trackThickness, juce::Colours::white);

        // Thumb: chunky white circle
        g.setColour(juce::Colours::white);
        g.fillEllipse(sliderPos - 10.0f, trackY - 10.0f, 20.0f, 20.0f);
    }
}

// ── Ink-Bleed: Multi-Pass Path Rendering ──
void LinusLookAndFeel::drawInkBleedPath(
    juce::Graphics& g,
    const juce::Path& path,
    float baseThickness,
    juce::Colour color)
{
    // Pass 1: Wide soft halo (simulates ink spreading on paper)
    g.setColour(color.withAlpha(0.3f));
    g.strokePath(path, juce::PathStrokeType(
        baseThickness * 1.4f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    // Pass 2: Core crisp line
    g.setColour(color);
    g.strokePath(path, juce::PathStrokeType(
        baseThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
}

// ── Wobbly Path Generator ──
juce::Path LinusLookAndFeel::generateWobblyPath(
    const std::vector<float>& points,
    float width, float height,
    float phase, bool isWobbly)
{
    juce::Path path;
    if (points.empty()) return path;

    float step = width / (float)(points.size() - 1);

    for (size_t i = 0; i < points.size(); ++i)
    {
        float x = i * step;
        float y = (height / 2.0f) + (points[i] * height * 0.4f);

        if (isWobbly)
        {
            // Dual-wobble: fast + slow sine for organic feel
            float wobble1 = std::sin(i * 0.1f + phase) * 3.0f;
            float wobble2 = std::sin(i * 0.03f + phase * 0.5f) * 1.5f;
            y += wobble1 + wobble2;
        }

        if (i == 0) path.startNewSubPath(x, y);
        else        path.lineTo(x, y);
    }

    return path;
}
