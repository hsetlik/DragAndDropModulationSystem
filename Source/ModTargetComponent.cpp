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
    g.setColour(centerColor);
    g.fillRect(getLocalBounds());
}

void RemoveButton::paintButton(juce::Graphics &g, bool, bool)
{
    g.setColour(juce::Colours::red);
    g.fillRect(getLocalBounds());
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
    auto area = getLocalBounds();
    g.setColour(background);
    g.fillRect(area);
}

ModTargetComponent::ModTargetComponent(juce::DragAndDropContainer* c) : numSources(0), target(c, this), container(c)
{
    selectedGroup = nullptr;
    addAndMakeVisible(&target);
    addAndMakeVisible(&zone);
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
    zone.setBounds(getLocalBounds());
    auto n = zone.getHeight() / 3;
    if(sources.size() > 0)
    {
        for(auto* i : sources)
            i->setBounds(zone.getBounds());
    }
    target.setBounds(0, n, n, n);
    target.toFront(true);
}


void ModTargetComponent::paint(juce::Graphics &g)
{
    g.setColour(juce::Colours::blue);
    g.fillAll();
}
