# Skill: Create Chunky Knob
## viking://agent/skills/create-chunky-knob

### Description
Implements the La Linea rotary slider with 12px-thick arc track, rounded stroke caps,
and spring-animated value transitions. This is the signature control element.

### JUCE Implementation

#### LinusLookAndFeel::drawRotarySlider()
```cpp
void LinusLookAndFeel::drawRotarySlider(
    juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    // Layout
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto centre = bounds.getCentre();
    float radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f - 15.0f;

    const float trackThickness = 12.0f;  // Chunky!

    // ── Background Track ──
    g.setColour(juce::Colours::white.withAlpha(0.2f));
    juce::Path bgTrack;
    bgTrack.addCentredArc(
        centre.x, centre.y,
        radius, radius,
        0.0f,
        rotaryStartAngle,
        rotaryEndAngle,
        true);
    g.strokePath(bgTrack, juce::PathStrokeType(
        trackThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    // ── Active Arc ──
    float activeEndAngle = rotaryStartAngle +
        (rotaryEndAngle - rotaryStartAngle) * sliderPos;

    g.setColour(juce::Colours::white);
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

    // ── Value Text ──
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(24.0f, juce::Font::bold));

    auto valueText = juce::String(slider.getValue(), 0);
    g.drawText(valueText, bounds, juce::Justification::centred);
}
```

#### React/TypeScript Prototype
```tsx
<div className="relative w-40 h-40 flex items-center justify-center">
  <svg className="absolute inset-0 w-full h-full -rotate-90">
    {/* Background track */}
    <circle
      cx="80" cy="80" r="65"
      stroke="rgba(255,255,255,0.2)"
      strokeWidth="12"
      fill="none"
      strokeLinecap="round"
    />
    {/* Active arc */}
    <motion.circle
      cx="80" cy="80" r="65"
      stroke="white"
      strokeWidth="12"
      fill="none"
      strokeLinecap="round"
      strokeDasharray="408"
      animate={{ strokeDashoffset: 408 - (408 * value) / 100 }}
      transition={{ type: "spring", stiffness: 100 }}
    />
  </svg>
  <span className="text-4xl font-black">{value}%</span>
</div>
```

### Anatomy
```
    ╭─────────────────╮
    │                 │
    │  ╭───────────╮  │   ← 12px white track (30% opacity)
    │  │           │  │
    │  │   VALUE   │  │   ← Centered value label
    │  │           │  │
    │  ╰═══════════╯  │   ← 12px white active arc (ink-bleed)
    │                 │
    ╰─────────────────╯
```

### Parameters
| Name | Default | Description |
|------|---------|-------------|
| `track_thickness` | 12.0 | Arc stroke width in pixels |
| `bg_alpha` | 0.2 | Background track opacity |
| `radius_padding` | 15.0 | Inset from component bounds |
| `font_size` | 24.0 | Value label font size |
| `ink_bleed` | true | Enable ink-bleed on active arc |
| `start_angle` | -2.36 rad | ~225° (7 o'clock) |
| `end_angle` | 2.36 rad | ~315° (5 o'clock) |

### Accessibility
- Hidden range input overlay for keyboard/screen reader control
- Value text always visible in center
- High contrast (white on colored background)
