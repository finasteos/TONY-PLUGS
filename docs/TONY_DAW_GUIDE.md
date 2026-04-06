# Hur Tony testar TONY-PLUGS i sin DAW 🎧

Hallå Tony! Eftersom vi nu har släppt vår **Sprint 1 (Version 0.1.0-alpha)** så ligger pluginen redan redo på din (och Pers) dator.

Här är en snabbguide för hur du får igång pluginen och kollar in "La Linea"-stilen direkt i ditt musikprogram!

## 1. Vad finns installerat?
När kod-agenten byggde projektet installerades filerna automatiskt på OSet (om ni är på macOS):
- **VST3:** `~/Library/Audio/Plug-Ins/VST3/Tony Plugs.vst3`
- **Audio Unit (AU):** `~/Library/Audio/Plug-Ins/Components/Tony Plugs.component`

Dessa är standardvägarna som Ableton, Logic, Studio One och FL Studio läser.

## 2. Hur du testar i DAW

**Om du kör Ableton Live:**
1. Öppna Ableton.
2. Gå till Plug-Ins > VST3 i browsern till vänster.
3. Leta efter mappen **Tnpl** (vår Manufacturer Code).
4. Dra in **Tony Plugs** på ett ljudspår!

**Om du kör Logic Pro (kräver AU):**
1. Öppna Logic.
2. Lägg till en Audio FX på ett spår.
3. Scrolla längst ner till `Audio Units` -> `TonyPlugs` -> `Tony Plugs`.
*(Tips: Om den inte dyker upp, öppna Logics Plug-in Manager och tryck på "Reset & Rescan Selection").*

## 3. Sandlådan — Standalone Appen
Om du bara vill designa ljud eller kolla in grafiken utan en DAW kan du starta pluginen som en helt vanlig app:
- Öppna din terminal och klistra in detta:
  ```bash
  open /Users/perbrinell/Documents/TONY-PLUGS/juce/build/TonyPlugs_artefacts/Release/Standalone/Tony\ Plugs.app
  ```

## 4. Nuvarande Design & Regler (Linus Style)
Just nu har pluginen:
1. **Cobalt Blue** bakgrund (`#1E5AA8`).
2. En generativ dubbel-sine "wobble-linje" med ink-bleed simulering.
3. **12px tjocka chunky knobs** — som för stunden mappar `Gain`, `Freq` och `Wobble`.

Eftersom du kollar på mer stil för **Linus på Linjen-temat** just nu:
- Kom fram till nya färger eller animationsbeslut? Lägg in dem i `docs/STYLE_GUIDE.md` eller be dina kära agenter (*MiniMax* & *Coder*) att uppdatera koden!
- Det viktiga design-språket i JUCE styrs just nu i `LinusLookAndFeel.cpp`.

Kör hårt och lek runt! TONY-PLUGS är numera en levande 30fps VST-plugin!
