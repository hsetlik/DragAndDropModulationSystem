/*
  ==============================================================================

    ModTargetComponent.h
    Created: 2 Mar 2021 6:03:45pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModSourceComponent.h"

class ModDropTarget : public juce::Component, public juce::DragAndDropTarget //note:: this base class has to be public
{
public:
    ModDropTarget(juce::DragAndDropContainer* p, juce::Button::Listener* l) : parentContainer(p)
    {
        addAndMakeVisible(hiddenButton);
        hiddenButton.setButtonText("hidden");
        hiddenButton.addListener(l);
        hiddenButton.setVisible(false);
        allColors.add(Color::RGBColor(52, 77, 96), "destDefault");
        centerColor = allColors.getByDesc("destDefault");
        allColors.add(Color::RGBColor(37, 49, 53), "destRim");
        rimColor = allColors.getByDesc("destRim");
    }
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        ModSourceComponent* sourceComp;
        if((sourceComp = dynamic_cast<ModSourceComponent*>(dragSourceDetails.sourceComponent.get())))
        {
            newSource = sourceComp;
            hiddenButton.triggerClick();
        }
        toFront(true);
    }
    void setColor(const char* d)
    {
        centerColor = allColors.getByDesc(d);
    }
    void setColor(juce::String& d)
    {
        centerColor = allColors.getByDesc(d);
    }
    ModSourceComponent* getNewSource() {return newSource;}
    void paint(juce::Graphics& g) override
    {
        auto fBounds = getLocalBounds().toFloat();
        g.setColour(rimColor);
        g.fillEllipse(fBounds);
        g.setColour(centerColor);
        g.fillEllipse(fBounds.reduced(fBounds.getWidth() * 0.1f));
    }
    void itemDragEnter(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        
    }
    void itemDragExit(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        
    }
    void itemDragMove(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        return true;
    }
    bool shouldDrawDragImageWhenOver() override
    {
        return false;
    }
private:
    juce::Colour rimColor;
    juce::Colour centerColor;
    juce::TextButton hiddenButton;
    juce::DragAndDropContainer* parentContainer;
    ModSourceComponent* newSource;
};

class SelectorButton : public juce::ShapeButton
{
public:
    SelectorButton(juce::Colour c, int srcIndex) : juce::ShapeButton("ModSelectButton" + juce::String(srcIndex), c, c, c), centerColor(c)
    {
        
    }
    ~SelectorButton() {}
    void paintButton(juce::Graphics& g, bool, bool) override;
private:
    juce::Colour centerColor;
};

class RemoveButton : public juce::ShapeButton
{
public:
    RemoveButton(int srcIndex) : juce::ShapeButton("ModRemoveButton" + juce::String(srcIndex), juce::Colours::black, juce::Colours::black, juce::Colours::black)
    {
        allColors.add(Color::RGBColor(186, 51, 77), "SatRed");
        allColors.add(Color::RGBColor(112, 32, 51), "DarkRed");
    }
    ~RemoveButton() {}
    void paintButton(juce::Graphics& g, bool, bool) override;
};

class SourceButtonGroup : public juce::Component
{
public:
    SourceButtonGroup(ModSourceComponent* s, int srcIndex, juce::Button::Listener* l);
    ~SourceButtonGroup() {}
    void resized() override;
    void paint(juce::Graphics& g) override;
private:
    juce::Colour background;
    ModSourceComponent* sourceComp;
    int sourceIndex;
    SelectorButton selButton;
    RemoveButton closeButton;
    
};

class SourceGroupZone : public juce::Component
{
public:
    SourceGroupZone()
    {
        
    }
    ~SourceGroupZone() {}
};

class ModTargetComponent : public juce::Component, juce::Button::Listener
{
public:
    ModTargetComponent(juce::DragAndDropContainer* c);
    ~ModTargetComponent() {}
    void buttonClicked(juce::Button* b) override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    int numSources;
    ModDropTarget target;
private:
    SourceButtonGroup* selectedGroup;
    juce::OwnedArray<SourceButtonGroup> sources;
    juce::DragAndDropContainer* container;
};
