/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DragDropContainer.h"
//==============================================================================
/**
*/
class DragDropModulationSystemAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DragDropModulationSystemAudioProcessorEditor (DragDropModulationSystemAudioProcessor&);
    ~DragDropModulationSystemAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DummyContainer container;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DragDropModulationSystemAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragDropModulationSystemAudioProcessorEditor)
};
