# Skill: Draw Linus Waveform
## viking://agent/skills/draw-linus-waveform

### Description
Renders a wobbly waveform in the La Linea style with dual-wobble animation and
amplitude-based dynamic stroke width.

### Prerequisites
- Color palette from `viking://user/preferences/linus-style`
- Audio buffer data (or generated sine test data)

### Steps

#### 1. Generate Base Points
```cpp
// From audio buffer or test signal
std::vector<float> points(numSamples);
for (int i = 0; i < numSamples; ++i)
    points[i] = audioBuffer[i]; // normalized -1.0 to 1.0
```

#### 2. Apply Dual-Wobble
```cpp
float phase = currentPhase; // incremented by Timer at 30fps
for (size_t i = 0; i < points.size(); ++i) {
    float wobble1 = std::sin(i * 0.1f + phase) * 3.0f;      // fast wobble
    float wobble2 = std::sin(i * 0.03f + phase * 0.5f) * 1.5f; // slow wobble
    float x = i * stepSize;
    float y = (height / 2.0f) + (points[i] * height * 0.4f) + wobble1 + wobble2;

    if (i == 0) path.startNewSubPath(x, y);
    else        path.lineTo(x, y);
}
```

#### 3. Calculate Dynamic Stroke Width
```cpp
float avgAmplitude = 0.0f;
for (auto p : points) avgAmplitude += std::abs(p);
avgAmplitude /= points.size();

float baseThickness = 6.0f; // from preferences
float dynamicThickness = baseThickness + (avgAmplitude * 4.0f);
```

#### 4. Render with Ink-Bleed
```cpp
// Pass 1: Soft halo
g.setColour(juce::Colours::white.withAlpha(0.3f));
g.strokePath(path, juce::PathStrokeType(
    dynamicThickness * 1.4f,
    juce::PathStrokeType::curved,
    juce::PathStrokeType::rounded));

// Pass 2: Core line
g.setColour(juce::Colours::white);
g.strokePath(path, juce::PathStrokeType(
    dynamicThickness,
    juce::PathStrokeType::curved,
    juce::PathStrokeType::rounded));
```

#### 5. Timer-Driven Animation
```cpp
// In your component:
class WobblyWaveform : public juce::Component, public juce::Timer {
    float phase = 0.0f;

    void timerCallback() override {
        phase += 0.05f;
        repaint();
    }

    WobblyWaveform() { startTimerHz(30); }
};
```

### TypeScript Equivalent
See `src/components/WaveformPrototype.tsx` for the React reference implementation.

### Parameters
| Name | Default | Range | Description |
|------|---------|-------|-------------|
| `wobble_primary_freq` | 0.1 | 0.05–0.3 | Fast wobble frequency |
| `wobble_primary_amp` | 3.0 | 1.0–6.0 | Fast wobble amplitude (px) |
| `wobble_secondary_freq` | 0.03 | 0.01–0.1 | Slow wobble frequency |
| `wobble_secondary_amp` | 1.5 | 0.5–3.0 | Slow wobble amplitude (px) |
| `base_thickness` | 6.0 | 3.0–12.0 | Base stroke width (px) |
| `phase_speed` | 0.05 | 0.01–0.2 | Phase increment per frame |
