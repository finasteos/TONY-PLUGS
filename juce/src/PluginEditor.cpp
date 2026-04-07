#include "PluginEditor.h"

namespace LinusColours
{
    const juce::Colour cobaltBlue  { 0xFF1E5AA8 };
    const juce::Colour grassGreen  { 0xFF2E8B57 };
    const juce::Colour sunnyYellow { 0xFFF4D03F };
}

TonyPlugsEditor::TonyPlugsEditor(TonyPlugsProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setLookAndFeel(&linusLookAndFeel);
    setSize(700, 500);

    lineManager = std::make_unique<LineManager>(processorRef);
    addAndMakeVisible(*lineManager);

    startTimerHz(30);
}

TonyPlugsEditor::~TonyPlugsEditor()
{
    setLookAndFeel(nullptr);
    stopTimer();
}

void TonyPlugsEditor::timerCallback()
{
}

void TonyPlugsEditor::paint(juce::Graphics& g)
{
    g.fillAll(LinusColours::cobaltBlue);
}

void TonyPlugsEditor::resized()
{
    if (lineManager) {
        lineManager->setBounds(getLocalBounds());
    }
}
