/*
  ==============================================================================

    DragDropContainer.h
    Created: 2 Mar 2021 6:10:17pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModTargetComponent.h"

class DummyContainer : public juce::DragAndDropContainer, public juce::Component
{
public:
    DummyContainer() : source(this, "source"), target(this)
    {
        addAndMakeVisible(source);
        addAndMakeVisible(target);
    }
    ~DummyContainer() {}
    void resized() override
    {
        auto n = getWidth() / 8;
        source.setBounds(n, n, n  / 2, n / 2);
        target.setBounds(5 * n, n, n, 3 * n);
    }
    void paint(juce::Graphics& g) override
    {
        
    }
private:
    ModSourceComponent source;
    ModTargetComponent target;
};
