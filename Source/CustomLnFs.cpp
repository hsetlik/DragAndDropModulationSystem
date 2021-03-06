/*
  ==============================================================================

    CustomLnFs.cpp
    Created: 5 Mar 2021 7:43:39am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "CustomLnFs.h"

void ModSystemLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& s)
{
    g.fillAll(juce::Colours::transparentBlack);
    auto iBounds = juce::Rectangle<int> {x, y, width, height};
    auto fBounds = iBounds.toFloat();
    auto angle = (rotaryEndAngle - rotaryStartAngle) * sliderPos;
    auto strokeType = juce::PathStrokeType(5.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded);
    auto centerX = fBounds.getX() + (fBounds.getWidth() / 2.0f);
    auto centerY = fBounds.getY() + (fBounds.getHeight() / 2.0f);
    auto radius = fBounds.getWidth() * 0.45f;
    juce::Path track;
    track.addCentredArc(centerX, centerY, radius, radius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour(colors.getByDesc("dullGray"));
    g.strokePath(track, strokeType);
    g.setColour(colors.getByDesc("thumbYellow"));
    juce::Path thumb;
    juce::Point<float> p1 {centerX + 0.2f, centerY + (0.8f * radius)};
    juce::Point<float> p2 {centerX, centerY - (radius / 3.0f)};
    juce::Point<float> p3 {centerX - 0.2f, centerY + (0.8f * radius)};
    thumb.addTriangle(p3, p2, p1);
    thumb.applyTransform(juce::AffineTransform::rotation(angle).translated (centerX, centerY));
    g.fillPath(thumb);
}
