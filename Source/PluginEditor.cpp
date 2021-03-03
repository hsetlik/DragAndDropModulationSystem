/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DragDropModulationSystemAudioProcessorEditor::DragDropModulationSystemAudioProcessorEditor (DragDropModulationSystemAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
}

DragDropModulationSystemAudioProcessorEditor::~DragDropModulationSystemAudioProcessorEditor()
{
}

//==============================================================================
void DragDropModulationSystemAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
}

void DragDropModulationSystemAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
