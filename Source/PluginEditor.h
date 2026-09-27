/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CustomToggleLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomToggleLookAndFeel(juce::Image filmstrip, int numFrames)
        : filmstripImage(filmstrip), totalFrames(numFrames)
    {
        // Filmstrip VERTICALE: i frame sono impilati in altezza
        frameWidth  = filmstripImage.getWidth();
        frameHeight = filmstripImage.getHeight() / totalFrames;
    }

    void drawToggleButton(juce::Graphics& g,
                          juce::ToggleButton& button,
                          bool /*shouldDrawButtonAsHighlighted*/,
                          bool /*shouldDrawButtonAsDown*/) override
    {
        // Calcola l'indice del frame: 0 = off, 1 = on
        int frameIndex = button.getToggleState() ? 1 : 0;
        frameIndex = juce::jlimit(0, totalFrames - 1, frameIndex);

        // Ritaglia il frame VERTICALE dalla filmstrip
        juce::Rectangle<int> srcRect(0, frameIndex * frameHeight, frameWidth, frameHeight);
        auto frameImage = filmstripImage.getClippedImage(srcRect);

        // Disegna il frame al centro dell'area del pulsante
        g.drawImage(frameImage,
                    button.getLocalBounds().toFloat(),
                    juce::RectanglePlacement::centred);
    }

private:
    juce::Image filmstripImage;
    int totalFrames;
    int frameWidth;
    int frameHeight;
};


class CustomKnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomKnobLookAndFeel(juce::Image filmstrip, int numFrames)
        : filmstripImage(filmstrip), totalFrames(numFrames)
    {
        // Calcola la larghezza di ogni frame (assumendo che siano disposti in riga)
        frameWidth = filmstripImage.getWidth();
        frameHeight = filmstripImage.getHeight() / totalFrames;
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        // Calcola l'indice del frame in base al valore normalizzato (0..1)
        int frameIndex = juce::roundToInt(sliderPos * (totalFrames - 1));
        frameIndex = juce::jlimit(0, totalFrames - 1, frameIndex);

        // Estrai la porzione di immagine corrispondente al frame
        juce::Rectangle<int> sourceRect(0, frameIndex * frameHeight, frameWidth, frameHeight);
        auto frameImage = filmstripImage.getClippedImage(sourceRect);

        // Disegna il frame al centro dell'area del knob, scalandolo se necessario
        juce::Rectangle<float> destRect(x, y, width, height);
        g.drawImage(frameImage, destRect, juce::RectanglePlacement::centred);
    }

private:
    juce::Image filmstripImage;
    int totalFrames;
    int frameWidth;
    int frameHeight;
};

//==============================================================================
/**
*/
class DunwichAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DunwichAudioProcessorEditor (DunwichAudioProcessor&);
    ~DunwichAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Image backgroundImage;
    juce::Image backgroundOff;
    juce::Image knobFilmstrip;
    juce::Image cabFilmStrip;
    juce::Image leadFilmStrip;
        
    std::unique_ptr<CustomKnobLookAndFeel> knobLookAndFeel;

    
    juce::Slider gateKnob;
    juce::Slider gainKnob;
    juce::Slider toneKnob;
    juce::Slider levelKnob;
    
    juce::Image bypassFilmstrip;
    std::unique_ptr<CustomToggleLookAndFeel> bypassLookAndFeel;
    std::unique_ptr<CustomToggleLookAndFeel> cabLookAndFeel;
    std::unique_ptr<CustomToggleLookAndFeel> leadLookAndFeel;
    
    juce::ToggleButton bypassBtn;   // ora è un ToggleButton
    juce::ToggleButton cabBtn;   // ora è un ToggleButton
    juce::ToggleButton leadBtn;
    
    
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DunwichAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DunwichAudioProcessorEditor)
};
