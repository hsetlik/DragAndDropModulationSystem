/*
  ==============================================================================

    ModTargetComponent.cpp
    Created: 2 Mar 2021 6:03:45pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModTargetComponent.h"

SourceButtonGroup::SourceButtonGroup(ModSourceComponent* s, int srcIndex, juce::Button::Listener* l) : sourceComp(s), sourceIndex(srcIndex), selButton(s->getColor(), srcIndex), closeButton(srcIndex)
{
    addAndMakeVisible(&closeButton);
    addAndMakeVisible(&selButton);
    closeButton.addListener(l);
    selButton.addListener(l);
    allColors.add(Color::RGBColor(38, 48, 55), "slateBkg");
    background = allColors.getByDesc("slateBkg");
}

void SelectorButton::paintButton(juce::Graphics &g, bool, bool)
{
    g.setColour(allColors.getByDesc("destRim"));
    g.fillEllipse(getLocalBounds().toFloat());
    g.setColour(centerColor);
    g.fillEllipse(getLocalBounds().toFloat().reduced(3.5f));
}

void RemoveButton::paintButton(juce::Graphics &g, bool, bool)
{
    juce::Path p;
    auto bounds = getLocalBounds().toFloat();
    g.setColour(allColors.getByDesc("SatRed"));
    g.fillEllipse(bounds);
    g.setColour(allColors.getByDesc("DarkRed"));
    auto centerX = getWidth() / 2;
    auto centerY = getHeight() / 2;
    auto rWidth = bounds.getWidth() * 0.2f;
    auto rLength = bounds.getHeight() * 0.8f;
    auto fRadius = rWidth * 0.3f;
    g.saveState();
    p.addRoundedRectangle(centerX - (rWidth / 2.0f), centerY - (rLength / 2.0f), rWidth, rLength, fRadius);
    p.addRoundedRectangle(centerX - (rLength / 2.0f), centerY - (rWidth / 2.0f), rLength, rWidth, fRadius);
    g.addTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::halfPi / 2, centerX, centerY));
    g.fillPath(p);
    g.restoreState();
}

void SourceButtonGroup::resized()
{
    //reserve the middle third of the component for the drag/drop target
    auto n = getHeight() / 3;
    closeButton.setBounds(0, 0, n, n);
    selButton.setBounds(0, 2 * n, n, n);
}
 void SourceButtonGroup::paint(juce::Graphics &g)
{
   
}

ModTargetComponent::ModTargetComponent(juce::DragAndDropContainer* c) : numSources(0), target(c, this), container(c)
{
    selectedGroup = nullptr;
    addAndMakeVisible(&target);
    target.toFront(true);
}

void ModTargetComponent::buttonClicked(juce::Button *b)
{
    SelectorButton* sel;
    if((sel = dynamic_cast<SelectorButton*>(b)))
    {
        auto src = dynamic_cast<SourceButtonGroup*>(sel->getParentComponent());
        selectedGroup = src;
    }
    RemoveButton* rem;
    if((rem = dynamic_cast<RemoveButton*>(b)))
    {
        auto src = dynamic_cast<SourceButtonGroup*>(rem->getParentComponent());
        sources.removeObject(src);
    }
    else
    {
        ++numSources;
        sources.add(new SourceButtonGroup(target.getNewSource(), numSources, this));
        addAndMakeVisible(sources.getLast());
        resized();
    }
}

void ModTargetComponent::resized()
{
    auto n = getHeight() / 3;
    if(sources.size() > 0)
    {
        for(auto* i : sources)
            i->setBounds(getLocalBounds());
    }
    target.setBounds(0, n, n, n);
    target.toFront(true);
}


void ModTargetComponent::paint(juce::Graphics &g)
{
    
}
