# Implementation Plan: The Infinite Line

## Översikt

TONY-PLUGS UI byggs om kring en central `LineManager` som hanterar EN kombinerad `juce::Path`. Varje komponent (sliders, knobs, waveform) är en "mutation" av linjen istället för en separat komponent.

## Arkitektur

```
┌─────────────────────────────────────────────────────────────┐
│                      TonyPlugsEditor                        │
│  ┌───────────────────────────────────────────────────────┐  │
│  │                   LineManager                         │  │
│  │  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐   │  │
│  │  │ RidgeBump   │  │  LoopKnot   │  │ PulseLine   │   │  │
│  │  │ (Fader)     │  │  (Knob)     │  │ (Waveform)  │   │  │
│  │  └─────────────┘  └─────────────┘  └─────────────┘   │  │
│  │                    │                                  │  │
│  │              ┌─────┴─────┐                            │  │
│  │              │ Combined   │                            │  │
│  │              │   Path     │                            │  │
│  │              └───────────┘                            │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

## LineManager Klass

### `LineManager.h`

```cpp
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class RidgeBump;
class LoopKnot;
class PulseLine;

class LineManager : public juce::Component,
                    private juce::Timer
{
public:
    explicit LineManager(TonyPlugsProcessor& processor);
    ~LineManager();

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Mouse interaction for Line Mutations
    void mouseDown(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

private:
    void timerCallback() override;
    void rebuildCombinedPath();

    // Line Mutation components
    std::unique_ptr<RidgeBump> gainRidge;
    std::unique_ptr<LoopKnot> freqLoop;
    std::unique_ptr<LoopKnot> wobbleLoop;
    std::unique_ptr<PulseLine> audioPulse;

    // Combined path for 90% unified line
    juce::Path combinedLine;
    float globalPhase = 0.0f;

    TonyPlugsProcessor& processorRef;
    float wobbleAmount = 0.5f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LineManager)
};
```

## Line Mutation-komponenter

### 1. RidgeBump (Fader)

```
┌────────────────────────────────────────────────────────────┐
│                                                            │
│                    ╱                                        │
│               ╱───                                          │
│          ╱───        ← Ridge (bump på linjen)              │
│     ╱───                                                    │
│─────              ← Linjen fortsätter vertikalt            │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

```cpp
class RidgeBump : public juce::Component {
public:
    enum class Orientation { Horizontal, Vertical };
    
    void setValue(float v) { value = v; dirty = true; }
    float getValue() const { return value; }
    
    // Generates bump path that integrates with main line
    juce::Path generateRidgePath(float baseY, float lineThickness);
    
private:
    float value = 0.5f;
    bool dirty = true;
    Orientation orientation = Orientation::Vertical;
};
```

### 2. LoopKnot (Knob)

```
┌────────────────────────────────────────────────────────────┐
│                                                            │
│         ╭──────────────╮                                   │
│        ╱                ╲                                  │
│       │   ◯◯◯◯◯◯◯◯◯     │  ← Loop tightened based on value │
│        ╲                ╱                                  │
│         ╰──────────────╯                                   │
│              │                                              │
│            ──┴────  ← Main line continues                  │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

```cpp
class LoopKnot : public juce::Component {
public:
    void setValue(float v) { value = v; dirty = true; }
    float getValue() const { return value; }
    
    // Generates loop that tightens/expands
    juce::Path generateLoopPath(float anchorX, float anchorY);
    
private:
    float value = 0.5f;
    bool dirty = true;
};
```

### 3. PulseLine (Waveform)

```
┌────────────────────────────────────────────────────────────┐
│                                                            │
│─────●──●──●──●──●──●──●──●──●──●──●──●──●──●──●──●──●───   │
│                                                            │
│    ↑                                                       │
│    │  ← Linjen själv pulserar/vibrerar                    │
│    │    istället för separata boxar                       │
│                                                            │
└────────────────────────────────────────────────────────────┘
```

```cpp
class PulseLine : public juce::Component {
public:
    void updateFromProcessor();
    
    // Path vibrates/oscillates - no separate box
    juce::Path generatePulsePath(float startX, float startY, 
                                   float length, float baseThickness);
    
private:
    std::vector<float> audioData;
    std::atomic<int> readBuffer{0};
};
```

## Kombinerad Path-bygge

```cpp
void LineManager::rebuildCombinedPath()
{
    combinedLine.clear();
    
    // Start position (top-left of UI)
    float x = 40.0f;
    float y = 100.0f;
    
    // ┌─────────────────────────────────────────────────────┐
    // │ LINE SEGMENT 1: Top horizontal                     │
    // └─────────────────────────────────────────────────────┘
    float loopY = y + 50.0f;
    
    // Generate LoopKnot for Freq at position (300, loopY)
    auto freqLoopPath = freqLoop->generateLoopPath(300.0f, loopY);
    
    // Generate LoopKnot for Wobble at position (500, loopY)
    auto wobbleLoopPath = wobbleLoop->generateLoopPath(500.0f, loopY);
    
    // ┌─────────────────────────────────────────────────────┐
    // │ LINE SEGMENT 2: Vertical down to RidgeBumps          │
    // └─────────────────────────────────────────────────────┘
    // Draw vertical line segment
    combinedLine.lineTo(x + 100.0f, y + 200.0f);
    
    // Generate RidgeBump for Gain
    auto gainRidgePath = gainRidge->generateRidgePath(y + 200.0f, 12.0f);
    
    // ┌─────────────────────────────────────────────────────┐
    // │ LINE SEGMENT 3: Audio Pulse Line                   │
    // └─────────────────────────────────────────────────────┘
    // Bottom section: pulse line
    auto pulsePath = audioPulse->generatePulsePath(40.0f, 350.0f, 620.0f, 6.0f);
}
```

## Renderings-pipeline

```cpp
void LineManager::paint(juce::Graphics& g)
{
    // Background
    g.fillAll(LinusColours::cobaltBlue);
    
    // Update global phase for breathing animation
    globalPhase += 0.02f;
    
    // Rebuild path if needed
    if (needsRebuild) rebuildCombinedPath();
    
    // ── PASS 1: Ink-Bleed Halo (140%, 30% opacity) ──
    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.strokePath(combinedLine, juce::PathStrokeType(
        baseThickness * 1.4f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
    
    // ── PASS 2: Core Line (100%, 100% opacity) ──
    g.setColour(juce::Colours::white);
    g.strokePath(combinedLine, juce::PathStrokeType(
        baseThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
}
```

## Interaktion

```cpp
void LineManager::mouseDown(const juce::MouseEvent& e)
{
    // Hit-test against RidgeBumps
    if (gainRidge->contains(e.position)) {
        activeInteraction = Interaction::GainRidge;
    }
    // Hit-test against LoopKnots
    else if (freqLoop->contains(e.position)) {
        activeInteraction = Interaction::FreqLoop;
    }
    else if (wobbleLoop->contains(e.position)) {
        activeInteraction = Interaction::WobbleLoop;
    }
}

void LineManager::mouseDrag(const juce::MouseEvent& e)
{
    switch (activeInteraction) {
        case Interaction::GainRidge:
            // Convert Y drag to value 0-1
            float newValue = (e.position.y - ridgeY) / ridgeHeight;
            gainRidge->setValue(juce::jlimit(0.0f, 1.0f, newValue));
            break;
        // ... similar for loops
    }
    
    // Update processor parameter
    processorRef.getAPVTS().getRawParameterValue("gain")->store(value);
    needsRebuild = true;
}
```

## Wobble-animering

```cpp
void LineManager::timerCallback()
{
    globalPhase += 0.05f;
    
    // Breathing animation: subtle 1-2px offset
    float breathe = std::sin(globalPhase * 0.5f) * 1.5f;
    
    // Update audio pulse
    audioPulse->updateFromProcessor();
    
    repaint();
}
```

## Filer att skapa

| Fil | Beskrivning |
|-----|-------------|
| `LineManager.h` | Huvudarkitektur |
| `LineManager.cpp` | Implementation |
| `LineMutations/RidgeBump.h` | Fader-mutation |
| `LineMutations/RidgeBump.cpp` | Implementation |
| `LineMutations/LoopKnot.h` | Knob-mutation |
| `LineMutations/LoopKnot.cpp` | Implementation |
| `LineMutations/PulseLine.h` | Waveform-mutation |
| `LineMutations/PulseLine.cpp` | Implementation |

## Implementations-steg

1. **Steg 1**: Skapa `LineMutations/`-mappen och basklasserna
2. **Steg 2**: Implementera `RidgeBump` (enkel vertikal bump)
3. **Steg 3**: Implementera `LoopKnot` (cirkel-loop som tighten/expands)
4. **Steg 4**: Implementera `PulseLine` (audio-vibrerande linje)
5. **Steg 5**: Skapa `LineManager` som kombinerar allt
6. **Steg 6**: Uppdatera `PluginEditor` att använda `LineManager`
7. **Steg 7**: Lägg till mus-interaktion (hit-testing + drag)
8. **Steg 8**: Fina justeringar (wobble, ink-bleed, breathing)

## Design-principer

- **EN linje**: 90% av UI är samma path-objekt
- **Inga boxar**: Waveform är linjen själv, inte en container
- **Mutation istället för komponent**: Varje kontroll är en förändring av linjen
- **Hand-drawn feel**: Wobble + Ink-Bleed på allt
- **Always alive**: Aldrig perfekt still, alltid 1-2px "breathing"
