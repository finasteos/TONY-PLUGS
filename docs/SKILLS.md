# TONY-PLUGS Reusable Skills

## Overview
Skills are step-by-step patterns for common TONY-PLUGS tasks. They are shared via OpenViking
(`viking://agent/skills/`) so all agents have consistent implementation references.

## Skill Catalog

### 🌊 Draw Linus Waveform
**URI**: `viking://agent/skills/draw-linus-waveform`
**File**: `.viking/skills/draw-linus-waveform.md`

Renders a wobbly waveform with dual-sine wobble and amplitude-based dynamic stroke width.
- Wobble: `sin(i * 0.1 + phase) * 3.0` + `sin(i * 0.03 + phase * 0.5) * 1.5`
- Dynamic thickness: `baseThickness + (avgAmplitude * 4.0)`
- Timer-driven at 30fps

---

### 🖋️ Implement Ink-Bleed
**URI**: `viking://agent/skills/implement-ink-bleed`
**File**: `.viking/skills/implement-ink-bleed.md`

Multi-pass rendering for the organic "ink on paper" look.
- **Approach A** (Recommended): 2-pass (halo + core)
- **Approach B**: 3-pass (extra soft outer layer)
- **Approach C**: SVG filter chain (web only)

---

### 🎛️ Create Chunky Knob
**URI**: `viking://agent/skills/create-chunky-knob`
**File**: `.viking/skills/create-chunky-knob.md`

12px-thick rotary slider with rounded caps and centered value label.
- Track: 12px, 20% white opacity background
- Active arc: 12px, full white with ink-bleed
- Value: centered bold text
- Hidden range input for accessibility

---

## JUCE Patterns

### Parameter Setup
```cpp
juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "gain", "Gain", 0.0f, 1.0f, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "freq", "Frequency",
        juce::NormalisableRange<float>(20.0f, 2000.0f, 1.0f, 0.3f),
        440.0f));
    return { params.begin(), params.end() };
}
```

### Custom LookAndFeel Registration
```cpp
// In PluginEditor constructor:
setLookAndFeel(&linusLookAndFeel);

// In PluginEditor destructor:
setLookAndFeel(nullptr);
```

### Timer-Based Repaint
```cpp
class AnimatedComponent : public juce::Component, private juce::Timer {
    void timerCallback() override { repaint(); }
public:
    AnimatedComponent() { startTimerHz(30); } // 30fps wobble
    ~AnimatedComponent() override { stopTimer(); }
};
```

## TypeScript Patterns

### Motion Spring Animation
```tsx
<motion.circle
  animate={{ strokeDashoffset: 408 - (408 * value) / 100 }}
  transition={{ type: "spring", stiffness: 100 }}
/>
```

### SVG Ink-Bleed Filter
```tsx
<defs>
  <filter id="inkBleed">
    <feGaussianBlur stdDeviation="1" result="blur" />
    <feColorMatrix values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 18 -7" />
    <feComposite in="SourceGraphic" in2="ink" operator="atop" />
  </filter>
</defs>
```
