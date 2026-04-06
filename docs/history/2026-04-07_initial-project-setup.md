# TONY-PLUGS: Initial Project Setup Plan
## Date: 2026-04-07
## Session: Antigravity (Claude Opus 4.6 thinking)

### Objective
Set up the TONY-PLUGS JUCE VST plugin project with:
- OpenViking shared memory integration
- OpenCode CLI multi-agent workflow (5 specialized agents)
- JUCE CMake setup (VST3/AU/Standalone — no AAX)
- Comprehensive documentation and style guide

### Architecture Decision
**Dual-track approach:**
- React/Vite/TypeScript app = Design system prototype & visual reference
- `juce/` directory = Production JUCE C++ plugin code

### Agents Configured
| Agent | Model | Role |
|-------|-------|------|
| qwen-coder | Qwen Medium | Daily coding |
| qwen-debugger | Qwen HIGH | Debugging sessions |
| minimax-planner | MiniMax M2.5 | Architecture/planning |
| nemotron-refactor | Nemotron | Refactoring/cleanup |
| qwen-docs | Qwen 1M | Documentation |

### Visual Style: "Linus på linjen"
- Colors: Cobalt blue `#1E5AA8`, Grass green `#2E8B57`, Sunny yellow `#F4D03F`
- Line thickness: 6px (waveforms), 12px (knobs)
- Ink-bleed: Multi-pass Gaussian blur → color matrix → composite
- Wobble: `sin(i * 0.1 + phase) * 3` + `sin(i * 0.03 + phase * 0.5) * 1.5`

### Key JUCE Decisions
- JUCE 8.x via CMake `FetchContent` (not Projucer)
- C++17 minimum
- No AAX format
- Custom `LookAndFeel_V4` subclass
- `AudioProcessorValueTreeState` for parameters
