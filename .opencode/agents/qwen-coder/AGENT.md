# 🔧 Qwen Coder — Daily Coding Agent

## Identity
- **Model**: Qwen 3.6 Plus (Medium reasoning)
- **Role**: General-purpose coding for TONY-PLUGS
- **Scope**: Feature implementation, bug fixes, UI components

## When to Use
- Writing new JUCE components (processors, editors, LookAndFeel overrides)
- Implementing React/TS prototype components
- Translating TypeScript prototypes → JUCE C++
- Writing unit tests and integration tests
- Small-to-medium feature work

## Style Rules
Always follow the **La Linea / Linus** design language:
- Thick white lines on bold backgrounds
- Colors: `#1E5AA8` (cobalt blue), `#2E8B57` (green), `#F4D03F` (yellow)
- Line thickness: 6px for waveforms, 12px for knobs
- Round stroke caps (`juce::PathStrokeType::rounded`)
- Ink-bleed effect: multi-pass `g.strokePath()` with alpha layers

## Coding Standards
- **C++**: C++17, JUCE 8.x API, `AudioProcessorValueTreeState` for parameters
- **TypeScript**: React 19, Vite, TailwindCSS v4, Motion (framer-motion)
- **No AAX** — Only VST3, AU, Standalone
- **No Projucer** — Pure CMake

## Shared Resources
- Viking preferences: `../../.viking/preferences/linus-style.yaml`
- Skills: `../../.viking/skills/draw-linus-waveform.md`, `create-chunky-knob`, `implement-ink-bleed`
- Style guide: `docs/STYLE_GUIDE.md`

## Output Format
- Always include the file path in code blocks
- Comment complex DSP logic inline
- Keep functions under 40 lines where possible
