# Skill: Implement Ink-Bleed Effect
## viking://agent/skills/implement-ink-bleed

### Description
Creates the organic, hand-drawn ink-bleed look that gives La Linea its characteristic warmth.
Two approaches: Multi-pass (simple, recommended) and SVG filter (for web prototypes).

### Approach A: Multi-Pass Rendering (JUCE — Recommended)
Simple, performant, 90% of the visual quality.

```cpp
void drawInkBleedPath(juce::Graphics& g,
                       const juce::Path& path,
                       float baseThickness,
                       juce::Colour color)
{
    // Pass 1: Wide soft halo (simulates ink spreading)
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
```

### Approach B: Triple-Pass (More Analog)
For when "flat" doesn't feel analog enough.

```cpp
void drawHeavyInkBleed(juce::Graphics& g,
                        const juce::Path& path,
                        float baseThickness,
                        juce::Colour color)
{
    // Pass 1: Outer blur (very faint)
    g.setColour(color.withAlpha(0.15f));
    g.strokePath(path, juce::PathStrokeType(
        baseThickness * 1.8f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    // Pass 2: Inner blur
    g.setColour(color.withAlpha(0.35f));
    g.strokePath(path, juce::PathStrokeType(
        baseThickness * 1.3f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));

    // Pass 3: Core line
    g.setColour(color);
    g.strokePath(path, juce::PathStrokeType(
        baseThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
}
```

### Approach C: SVG Filter (React/Web Prototypes)
For the TypeScript design system.

```xml
<defs>
  <filter id="inkBleed">
    <feGaussianBlur in="SourceGraphic" stdDeviation="1" result="blur" />
    <feColorMatrix in="blur" mode="matrix"
      values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 18 -7"
      result="ink" />
    <feComposite in="SourceGraphic" in2="ink" operator="atop" />
  </filter>
</defs>
```

### Performance Notes
- Multi-pass rendering adds ~15% GPU overhead per pass
- For 60fps animation, stick with 2-pass (Approach A)
- Use `setBufferedToImage(true)` on static ink-bleed components
- Only repaint animated elements, not the entire plugin window

### When to Use Which
| Scenario | Approach |
|----------|----------|
| Knob tracks (static) | A — Multi-Pass (cached) |
| Waveform (animated) | A — Multi-Pass (live) |
| Heavy vintage feel | B — Triple-Pass |
| Web prototype | C — SVG Filter |
