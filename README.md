<div align="center">
<img width="1200" height="475" alt="GHBanner" src="https://github.com/user-attachments/assets/0aa67016-6eaf-458a-adb2-6e31a0763ed6" />
</div>

# TONY-PLUGS 🎹

**La Linea inspired JUCE VST plugins** — thick white lines, bold backgrounds, hand-drawn wobble.

Inspired by [Osvaldo Cavandoli's La Linea](https://en.wikipedia.org/wiki/La_Linea_(TV_series)) and the Amiga demoscene.

## Architecture

```
TONY-PLUGS/
├── src/                          # React/TS Design Prototype
│   ├── App.tsx                   # Main showcase page
│   └── components/               # La Linea UI components
│       ├── VSTPlugin.tsx         # Interactive synth mockup
│       ├── WaveformPrototype.tsx # Wobbly waveform
│       ├── JuceReference.tsx     # C++ porting snippets
│       ├── LineCharacter.tsx     # Animated Linus character
│       └── LineUI.tsx            # Button/card/input library
├── juce/                         # JUCE C++ Plugin (Production)
│   ├── CMakeLists.txt            # Modern CMake (FetchContent JUCE 8.x)
│   └── src/
│       ├── PluginProcessor.h/cpp # Audio processing + APVTS
│       ├── PluginEditor.h/cpp    # UI with wobbly waveform
│       └── LookAndFeel/          # LinusLookAndFeel (12px knobs)
├── .opencode/agents/             # 5 Specialized OpenCode Agents
│   ├── qwen-coder/               # Daily coding (Qwen Medium)
│   ├── qwen-debugger/            # Debugging (Qwen HIGH)
│   ├── minimax-planner/          # Architecture (MiniMax M2.5)
│   ├── nemotron-refactor/        # Refactoring (Nemotron)
│   └── qwen-docs/                # Documentation (Qwen 1M)
├── .viking/                      # OpenViking Shared Memory
│   ├── config.yaml               # Resource URIs
│   ├── preferences/              # Color palette, line weights
│   └── skills/                   # Waveform, ink-bleed, chunky knob
└── docs/                         # Documentation
    ├── AGENTS.md                 # Agent team guide
    ├── SKILLS.md                 # Reusable patterns
    ├── STYLE_GUIDE.md            # Visual design spec
    └── history/                  # Implementation plan archive
```

## Quick Start

### React Prototype (Design System)
```bash
npm install
npm run dev
# → http://localhost:3000
```

### JUCE Plugin (C++)
```bash
cd juce
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```
**Formats**: VST3, AU, Standalone (no AAX)
**Requires**: CMake 3.22+, C++17 compiler

### Multi-Agent Workflow
```bash
# Start OpenCode agents (5 terminal tabs)
cd .opencode/agents/qwen-coder && opencode       # Daily coding
cd .opencode/agents/qwen-debugger && opencode     # Debugging
cd .opencode/agents/minimax-planner && opencode   # Architecture
cd .opencode/agents/nemotron-refactor && opencode # Refactoring
cd .opencode/agents/qwen-docs && opencode         # Documentation
```

## Design Language

| Token | Value | Usage |
|-------|-------|-------|
| 🔵 Cobalt Blue | `#1E5AA8` | Primary background |
| 🟢 Grass Green | `#2E8B57` | Secondary / success |
| 🟡 Sunny Yellow | `#F4D03F` | Accent / highlights |
| Line thickness | 6px / 12px | Waveforms / Knobs |
| Wobble | dual-sine | Hand-drawn feel |
| Ink-bleed | multi-pass | Organic edges |

See [docs/STYLE_GUIDE.md](docs/STYLE_GUIDE.md) for full spec.

## Tools
- **OpenCode** (5 instances) — AI-powered coding with specialized agents
- **OpenViking** — Shared memory across agents (`viking://resources/...`)
- **PromptFoo** — A/B testing, regression tests

---
© 2026 Inspired by Cavandoli & the Demoscene
