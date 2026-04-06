# TONY-PLUGS Agent Team

## Overview
TONY-PLUGS uses 5 specialized OpenCode CLI agents, each tuned for a specific type of work.
All agents share the La Linea style guide via OpenViking (`viking://user/preferences/linus-style`).

## Agent Roster

### 🔧 Qwen Coder — Daily Coding
| Property | Value |
|----------|-------|
| **Model** | Qwen 3.6 Plus (Medium reasoning) |
| **Directory** | `.opencode/agents/qwen-coder/` |
| **Start command** | `cd .opencode/agents/qwen-coder && opencode` |
| **Model command** | `/model qwen-3.6-plus` |

**Use for**: Feature implementation, TS→C++ porting, writing components, bug fixes.

---

### 🐛 Qwen Debugger — Debugging
| Property | Value |
|----------|-------|
| **Model** | Qwen 3.6 Plus (HIGH reasoning) |
| **Directory** | `.opencode/agents/qwen-debugger/` |
| **Start command** | `cd .opencode/agents/qwen-debugger && opencode` |
| **Model command** | `/model qwen-3.6-plus` + set reasoning to HIGH |

**Use for**: Crash analysis, DAW compatibility issues, audio thread bugs, memory leaks.

---

### 🏗️ MiniMax Planner — Architecture
| Property | Value |
|----------|-------|
| **Model** | MiniMax M2.5 |
| **Directory** | `.opencode/agents/minimax-planner/` |
| **Start command** | `cd .opencode/agents/minimax-planner && opencode` |
| **Model command** | `/model minimax-m2.5` |

**Use for**: Feature planning, DSP signal chain design, PR reviews, technology decisions.

---

### ♻️ Nemotron Refactor — Refactoring
| Property | Value |
|----------|-------|
| **Model** | Nemotron 3 Super |
| **Directory** | `.opencode/agents/nemotron-refactor/` |
| **Start command** | `cd .opencode/agents/nemotron-refactor && opencode` |
| **Model command** | `/model nemotron-3-super` |

**Use for**: Code cleanup, DRY enforcement, pattern extraction, naming normalization.

---

### 📚 Qwen Docs — Documentation
| Property | Value |
|----------|-------|
| **Model** | Qwen 3.6 Plus (1M context) |
| **Directory** | `.opencode/agents/qwen-docs/` |
| **Start command** | `cd .opencode/agents/qwen-docs && opencode` |
| **Model command** | `/model qwen-3.6-plus` + 1M context mode |

**Use for**: README updates, CHANGELOG, API docs, Doxygen comments, tutorials.

## Quick Start
```bash
# Open 5 terminal tabs and run:
cd /Users/perbrinell/Documents/TONY-PLUGS

# Tab 1: Coder
cd .opencode/agents/qwen-coder && opencode

# Tab 2: Debugger
cd .opencode/agents/qwen-debugger && opencode

# Tab 3: Planner
cd .opencode/agents/minimax-planner && opencode

# Tab 4: Refactorer
cd .opencode/agents/nemotron-refactor && opencode

# Tab 5: Docs
cd .opencode/agents/qwen-docs && opencode
```

## Workflow Tips
1. **Start with Planner** for architecture decisions
2. **Hand off to Coder** for implementation
3. **Use Debugger** when things break
4. **Run Refactorer** after features stabilize
5. **Update Docs** after each milestone
