# TONY-PLUGS Visual Style Guide

## Inspiration
**"La Linea" (Linus på linjen)** by Osvaldo Cavandoli — thick white lines, simple shapes,
hand-drawn feel. Combined with the **Amiga demoscene** ethos: maximum impact from minimal resources.

## Color Palette

| Swatch | Name | Hex | RGB | JUCE | Usage |
|--------|------|-----|-----|------|-------|
| 🔵 | Cobalt Blue | `#1E5AA8` | 30, 90, 168 | `Colour(0x1E, 0x5A, 0xA8)` | Primary background |
| 🟢 | Grass Green | `#2E8B57` | 46, 139, 87 | `Colour(0x2E, 0x8B, 0x57)` | Secondary / success |
| 🟡 | Sunny Yellow | `#F4D03F` | 244, 208, 63 | `Colour(0xF4, 0xD0, 0x3F)` | Accent / highlights |
| ⚪ | Pure White | `#FFFFFF` | 255, 255, 255 | `Colours::white` | Lines, text, controls |
| ⚫ | Pitch Black | `#000000` | 0, 0, 0 | `Colours::black` | Contrast, borders |

## Line Rendering

### Thickness Scale
| Element | Thickness | Notes |
|---------|-----------|-------|
| Waveform | 6px base | Dynamic ±2px based on amplitude |
| Knob track | 12px | Always rounded caps |
| Card border | 4px | Both C++ and CSS |
| Section border | 8px | Major section dividers |
| Character outline | 4px | Animated stroke width 3.5–5px |

### Stroke Style
- **Cap**: Rounded (`strokeLinecap="round"` / `PathStrokeType::rounded`)
- **Join**: Rounded (`strokeLinejoin="round"` / `PathStrokeType::rounded`)
- **No sharp corners** — everything curves

## Wobble Effect
Two sine waves layered for organic hand-drawn feel:
```
fast_wobble  = sin(index × 0.10 + phase) × 3.0    // pixel displacement
slow_wobble  = sin(index × 0.03 + phase × 0.5) × 1.5
total_offset = fast_wobble + slow_wobble
```
Phase increments at 0.05 radians/frame, updated at 30fps.

## Ink-Bleed Effect
Multi-pass rendering to simulate ink spreading on paper:
- **Pass 1**: 140% thickness, 30% opacity (soft halo)
- **Pass 2**: 100% thickness, 100% opacity (crisp core)

## Component Anatomy

### Rotary Knob
```
    ╭─────────────────╮
    │  ╭══════════╮   │   bg track: 12px, white @ 20%
    │  │  VALUE   │   │   value: bold, centered
    │  ╰═══════···╯   │   active arc: 12px, white, ink-bleed
    ╰─────────────────╯
```

### Waveform Display
```
    ┌─────────────────────────┐
    │  LABEL          10px    │   label: uppercase, tracking-widest
    │                         │
    │  ~~~∿∿∿~∿∿~~~∿~~∿~~  │   waveform: 6px, wobble, ink-bleed
    │                         │
    └─────────────────────────┘
    Background: solid color from palette
    Border: 4px black, rounded 32px
    Shadow: 8px offset, black @ 100%
```

### Button
```
    ╭────────────────────────╮
    │  LABEL  →              │   font: black, uppercase
    ╰────────────────────────╯
    Border: 4px black
    Hover: invert colors
    Press: scale 0.95
    Shadow: 8px offset brutalist (optional)
```

## Animation Principles
1. **Fluidity** — Motion feels like ink flowing on paper
2. **Exaggeration** — Squash & stretch conveys emotion
3. **Anticipation** — "Prepare" before action changes
4. **Staging** — Focus on the line's interaction with the void

## Typography
- **Labels**: Inter/system, 900 weight, uppercase, 0.1em letter-spacing
- **Values**: Inter/system, 700 weight, normal case
- **Code/mono**: JetBrains Mono, 400 weight
- **Size scale**: 10px (labels) → 16px (body) → 24px (values) → 48px (headers)

## Shadow Style (Brutalist)
```css
/* CSS */
box-shadow: 8px 8px 0px 0px rgba(0,0,0,1);

/* Large emphasis */
box-shadow: 24px 24px 0px 0px rgba(0,0,0,1);
```
No blur radius. Pure offset. Always black.
