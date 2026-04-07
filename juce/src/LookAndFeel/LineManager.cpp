#include "LineManager.h"

namespace LinusColours {
    const juce::Colour cobaltBlue  { 0xFF1E5AA8 };
    const juce::Colour grassGreen  { 0xFF2E8B57 };
    const juce::Colour sunnyYellow { 0xFFF4D03F };
}

LineManager::LineManager(TonyPlugsProcessor& processor)
    : processorRef(processor)
{
    gainRidge = std::make_unique<RidgeBump>(RidgeBump::Orientation::Vertical);
    freqLoop = std::make_unique<LoopKnot>();
    wobbleLoop = std::make_unique<LoopKnot>();
    audioPulse = std::make_unique<PulseLine>();

    gainRidge->setValue(0.5f);
    freqLoop->setValue(0.5f);
    wobbleLoop->setValue(0.5f);
    audioPulse->setValue(0.5f);

    startTimerHz(30);
}

LineManager::~LineManager()
{
    stopTimer();
}

void LineManager::resized()
{
    auto bounds = getLocalBounds().toFloat();
    float w = bounds.getWidth();
    float h = bounds.getHeight();

    gainRidge->setBounds(juce::Rectangle<float>(w * 0.15f, h * 0.3f, w * 0.15f, h * 0.5f));
    freqLoop->setBounds(juce::Rectangle<float>(w * 0.4f, h * 0.2f, w * 0.2f, h * 0.2f));
    wobbleLoop->setBounds(juce::Rectangle<float>(w * 0.65f, h * 0.2f, w * 0.2f, h * 0.2f));
    audioPulse->setBounds(juce::Rectangle<float>(40.0f, h * 0.7f, w - 80.0f, h * 0.2f));

    needsRebuild = true;
}

void LineManager::timerCallback()
{
    globalPhase += 0.05f;

    float wobbleVal = processorRef.getAPVTS().getRawParameterValue("wobble")->load();
    audioPulse->setValue(wobbleVal);
    audioPulse->setPhase(globalPhase);
    audioPulse->updateFromProcessor(processorRef);

    gainRidge->setPhase(globalPhase);
    freqLoop->setPhase(globalPhase);
    wobbleLoop->setPhase(globalPhase);

    needsRebuild = true;
    repaint();
}

void LineManager::updateValuesFromProcessor()
{
    gainRidge->setValue(processorRef.getAPVTS().getRawParameterValue("gain")->load());
    freqLoop->setValue(processorRef.getAPVTS().getRawParameterValue("freq")->load() / 2000.0f);
}

LineManager::InteractionTarget LineManager::findInteractionTarget(juce::Point<float> point)
{
    if (gainRidge->hitTest(point)) return InteractionTarget::GainRidge;
    if (freqLoop->hitTest(point)) return InteractionTarget::FreqLoop;
    if (wobbleLoop->hitTest(point)) return InteractionTarget::WobbleLoop;
    return InteractionTarget::None;
}

void LineManager::mouseDown(const juce::MouseEvent& e)
{
    activeInteraction = findInteractionTarget(e.position);
}

void LineManager::mouseDrag(const juce::MouseEvent& e)
{
    auto param = [&]() -> std::atomic<float>* {
        switch (activeInteraction) {
            case InteractionTarget::GainRidge: return processorRef.getAPVTS().getRawParameterValue("gain");
            case InteractionTarget::FreqLoop: return processorRef.getAPVTS().getRawParameterValue("freq");
            case InteractionTarget::WobbleLoop: return processorRef.getAPVTS().getRawParameterValue("wobble");
            default: return nullptr;
        }
    }();

    if (param) {
        float newValue = 0.5f;
        
        if (activeInteraction == InteractionTarget::GainRidge) {
            auto b = gainRidge->getBounds();
            newValue = juce::jlimit(0.0f, 1.0f, (e.position.y - b.getY()) / b.getHeight());
        } else if (activeInteraction == InteractionTarget::FreqLoop) {
            auto centre = freqLoop->getBounds().getCentre();
            float dx = e.position.x - centre.x;
            float dy = e.position.y - centre.y;
            float delta = (dx + dy) * 0.002f;
            newValue = juce::jlimit(0.0f, 1.0f, param->load() + delta);
        } else if (activeInteraction == InteractionTarget::WobbleLoop) {
            auto centre = wobbleLoop->getBounds().getCentre();
            float dx = e.position.x - centre.x;
            float dy = e.position.y - centre.y;
            float delta = (dx + dy) * 0.002f;
            newValue = juce::jlimit(0.0f, 1.0f, param->load() + delta);
        }
        
        param->store(newValue);
        
        switch (activeInteraction) {
            case InteractionTarget::GainRidge: gainRidge->setValue(newValue); break;
            case InteractionTarget::FreqLoop: freqLoop->setValue(newValue); break;
            case InteractionTarget::WobbleLoop: wobbleLoop->setValue(newValue); break;
            default: break;
        }
        
        needsRebuild = true;
    }
}

void LineManager::mouseUp(const juce::MouseEvent&)
{
    activeInteraction = InteractionTarget::None;
}

void LineManager::rebuildCombinedPath()
{
    combinedLine.clear();
    
    float w = (float)getWidth();
    float h = (float)getHeight();
    
    float startX = 40.0f;
    float startY = 80.0f;
    
    combinedLine.startNewSubPath(startX, startY);
    combinedLine.lineTo(startX + w * 0.25f, startY);
    
    float loop1X = startX + w * 0.4f;
    float loop1Y = startY + 30.0f;
    combinedLine.startNewSubPath(loop1X, loop1Y);
    auto freqLoopPath = freqLoop->generateLoopPath(loop1X, loop1Y, kBaseThickness);
    combinedLine.addPath(freqLoopPath);
    
    combinedLine.startNewSubPath(startX + w * 0.5f, startY);
    combinedLine.lineTo(startX + w * 0.5f, h * 0.3f);
    
    float loop2X = startX + w * 0.65f;
    float loop2Y = h * 0.3f + 30.0f;
    combinedLine.startNewSubPath(loop2X, loop2Y);
    auto wobbleLoopPath = wobbleLoop->generateLoopPath(loop2X, loop2Y, kBaseThickness);
    combinedLine.addPath(wobbleLoopPath);
    
    combinedLine.startNewSubPath(startX + w * 0.75f, h * 0.3f);
    combinedLine.lineTo(startX + w * 0.85f, h * 0.5f);
    
    float ridgeX = startX + w * 0.92f;
    float ridgeBaseY = h * 0.3f;
    combinedLine.startNewSubPath(ridgeX, ridgeBaseY);
    auto ridgePath = gainRidge->generateRidgePath(ridgeX, ridgeBaseY, kBaseThickness);
    combinedLine.addPath(ridgePath);
    
    combinedLine.startNewSubPath(w - 40.0f, h * 0.5f);
    combinedLine.lineTo(w - 40.0f, h * 0.65f);
    combinedLine.lineTo(startX, h * 0.65f);
    combinedLine.lineTo(startX, startY);
    
    combinedLine.startNewSubPath(startX, h * 0.8f);
    auto pulsePath = audioPulse->generatePulsePath(startX, h * 0.8f, w - 80.0f, kBaseThickness);
    combinedLine.addPath(pulsePath);
    
    needsRebuild = false;
}

void LineManager::paint(juce::Graphics& g)
{
    g.fillAll(LinusColours::cobaltBlue);
    
    if (needsRebuild) {
        rebuildCombinedPath();
    }
    
    float breathe = std::sin(globalPhase * 0.5f) * 1.5f;
    
    g.setColour(juce::Colours::white.withAlpha(0.3f));
    g.strokePath(combinedLine, juce::PathStrokeType(
        kBaseThickness * 1.4f,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
    
    g.setColour(juce::Colours::white);
    g.strokePath(combinedLine, juce::PathStrokeType(
        kBaseThickness,
        juce::PathStrokeType::curved,
        juce::PathStrokeType::rounded));
    
    g.setColour(juce::Colours::white.withAlpha(0.5f));
    g.setFont(juce::Font{}.withHeight(10.0f).withTypefaceStyle("Bold"));
    g.drawText("THE INFINITE LINE",
               getLocalBounds().removeFromTop(30).reduced(20, 0),
               juce::Justification::centred);
}
