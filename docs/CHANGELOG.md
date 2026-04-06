# Changelog

All notable changes to TONY-PLUGS will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [0.1.0-alpha] — 2026-04-07

### Added

#### Project Structure
- Initial repository setup with dual-track architecture (React prototype + JUCE production)
- Directory layout: `src/`, `juce/`, `docs/`, `.opencode/agents/`, `.viking/`
- `.gitignore`, `.env.example`, `package.json`, `tsconfig.json`, `vite.config.ts`

#### React/TypeScript Design Prototype
- Vite + TypeScript scaffolding with development server
- `src/App.tsx` — Main showcase page
- `src/components/VSTPlugin.tsx` — Interactive synth mockup
- `src/components/WaveformPrototype.tsx` — Wobbly waveform with dual-sine animation
- `src/components/JuceReference.tsx` — C++ porting reference snippets
- `src/components/LineCharacter.tsx` — Animated Linus character
- `src/components/LineUI.tsx` — Button, card, and input component library

#### JUCE C++ Plugin Boilerplate
- `juce/CMakeLists.txt` — Modern CMake with FetchContent (JUCE 8.x)
- `juce/src/PluginProcessor.h/cpp` — Audio processing + APVTS parameter layout
- `juce/src/PluginEditor.h/cpp` — Editor with wobbly waveform placeholder
- `juce/src/LookAndFeel/` — LinusLookAndFeel (12px chunky knobs, custom styling)
- Build targets: VST3, AU, Standalone (no AAX)

#### Multi-Agent Configuration
- **qwen-coder** — Qwen 3.6 Plus (Medium) for daily coding
- **qwen-debugger** — Qwen 3.6 Plus (HIGH) for debugging
- **minimax-planner** — MiniMax M2.5 for architecture decisions
- **nemotron-refactor** — Nemotron 3 Super for refactoring
- **qwen-docs** — Qwen 3.6 Plus (1M context) for documentation

#### Documentation
- `README.md` — Project overview, quick start, architecture diagram, design tokens
- `docs/AGENTS.md` — Agent team roster, roles, and start commands
- `docs/SKILLS.md` — Reusable patterns (waveform, ink-bleed, chunky knob) with JUCE/TypeScript code snippets
- `docs/STYLE_GUIDE.md` — Visual design spec (color palette, line thickness, wobble formula, ink-bleed, component anatomy, typography, brutalist shadows)
- `docs/history/2026-04-07_initial-project-setup.md` — Initial setup session notes

#### Design Language
- Color palette: Cobalt Blue `#1E5AA8`, Grass Green `#2E8B57`, Sunny Yellow `#F4D03F`, Pure White, Pitch Black
- Line rendering: 6px waveforms, 12px knobs, 4px card borders, 8px section dividers
- Wobble effect: dual-sine layer (`sin(i*0.1)*3.0 + sin(i*0.03)*1.5`) at 30fps
- Ink-bleed: multi-pass rendering (halo + core)
- Brutalist shadows: pure offset, no blur

---

## [Unreleased]

*Next release will include...*
