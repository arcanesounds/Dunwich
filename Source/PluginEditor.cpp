/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
DunwichAudioProcessorEditor::DunwichAudioProcessorEditor (DunwichAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize(800, 572);
    
        backgroundImage = juce::ImageCache::getFromMemory(
                                                          BinaryData::bgon_png,
                                                          BinaryData::bgon_pngSize
                                                          );
        backgroundOff = juce::ImageCache::getFromMemory(
            BinaryData::bgoff_png,
            BinaryData::bgoff_pngSize
                                                        );
    
    
    // ============================================================
        // 1. CARICA LE FILMSTRIP
        // ============================================================
      knobFilmstrip = juce::ImageCache::getFromMemory (
            BinaryData::small_knob_png,
            BinaryData::small_knob_pngSize
        );
        
        bypassFilmstrip = juce::ImageCache::getFromMemory (
            BinaryData::switch_png,
            BinaryData::switch_pngSize
        );
    
    cabFilmStrip = juce::ImageCache::getFromMemory (
        BinaryData::switch2_png,
        BinaryData::switch2_pngSize
    );
    
    leadFilmStrip = juce::ImageCache::getFromMemory (
        BinaryData::switch3_png,
        BinaryData::switch3_pngSize
    );
        
        // ============================================================
        // 2. CREA I LOOK AND FEEL
        // ============================================================
        // Crea il LookAndFeel (es. 2 frame: 0=off, 1=on)
        addAndMakeVisible(cabBtn);
        cabLookAndFeel = std::make_unique<CustomToggleLookAndFeel>(cabFilmStrip, 2);
        cabBtn.setLookAndFeel(cabLookAndFeel.get());

        // Imposta lo stato iniziale (se hai un getter nel processore)
         cabBtn.setToggleState(audioProcessor.isCab(), juce::dontSendNotification);

        // Oppure forza a ON come nel prepareToPlay (che imposta bypass=1)
        cabBtn.setToggleState(false, juce::dontSendNotification);

        // Collega il cambiamento
        cabBtn.onClick = [this]
        {
            audioProcessor.setCab(cabBtn.getToggleState());
        };
    
    
    
    
    
        addAndMakeVisible(bypassBtn);
        bypassLookAndFeel = std::make_unique<CustomToggleLookAndFeel>(bypassFilmstrip, 2);
        bypassBtn.setLookAndFeel(bypassLookAndFeel.get());

        // Imposta lo stato iniziale (se hai un getter nel processore)
         bypassBtn.setToggleState(audioProcessor.isBypassed(), juce::dontSendNotification);

        // Oppure forza a ON come nel prepareToPlay (che imposta bypass=1)
       // bypassBtn.setToggleState(false, juce::dontSendNotification);

        // Collega il cambiamento
        bypassBtn.onClick = [this]
        {
            audioProcessor.setBypass(bypassBtn.getToggleState());
            repaint();
            
        };
    
    
        addAndMakeVisible(leadBtn);
        leadLookAndFeel = std::make_unique<CustomToggleLookAndFeel>(leadFilmStrip, 2);
        leadBtn.setLookAndFeel(leadLookAndFeel.get());

        // Imposta lo stato iniziale (se hai un getter nel processore)
         leadBtn.setToggleState(audioProcessor.isLead(), juce::dontSendNotification);

        // Oppure forza a ON come nel prepareToPlay (che imposta bypass=1)
    //    leadBtn.setToggleState(true, juce::dontSendNotification);

        // Collega il cambiamento
        leadBtn.onClick = [this]
        {
            audioProcessor.setLead(leadBtn.getToggleState());
            repaint();
            
        };
    
    
        



        // Sostituisci 60 con il numero effettivo di frame nella tua filmstrip
        knobLookAndFeel = std::make_unique<CustomKnobLookAndFeel>(knobFilmstrip, 128);

        addAndMakeVisible(gateKnob);
        gateKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        gateKnob.setLookAndFeel(knobLookAndFeel.get());
        gateKnob.setRange(-100.0, 0.0);
        gateKnob.setSkewFactorFromMidPoint(-50.0);
        gateKnob.setValue(-65);
        gateKnob.setDoubleClickReturnValue(true, -85.0);   // true = attiva il double-click, poi il valore di reset
        gateKnob.onValueChange = [this] {
            audioProcessor.setGate(gateKnob.getValue());
            };

        addAndMakeVisible(gainKnob);
        gainKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        gainKnob.setLookAndFeel(knobLookAndFeel.get());
        gainKnob.setRange(0.0, 2.0);
        gainKnob.setSkewFactorFromMidPoint(1.0);
        gainKnob.setDoubleClickReturnValue(true, 0.85);   // true = attiva il double-click, poi il valore di reset
        gainKnob.setValue(0.85);
        gainKnob.onValueChange = [this] {
            audioProcessor.setGain(gainKnob.getValue());
            };

/*
        addAndMakeVisible(toneKnob);
        toneKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        toneKnob.setLookAndFeel(knobLookAndFeel.get());
        toneKnob.setRange(0.00, 1.00);
        toneKnob.setSkewFactorFromMidPoint(0.50);
        toneKnob.setDoubleClickReturnValue(true, 0.85);   // true = attiva il double-click, poi il valore di reset
        toneKnob.setValue(0.85);
        toneKnob.onValueChange = [this] {
            audioProcessor.setTone(toneKnob.getValue());
            };

*/
        addAndMakeVisible(levelKnob);
        levelKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        levelKnob.setLookAndFeel(knobLookAndFeel.get());
        levelKnob.setRange(0.0, 1.0);
        levelKnob.setSkewFactorFromMidPoint(0.5);
        levelKnob.setDoubleClickReturnValue(true, 0.5);   // true = attiva il double-click, poi il valore di reset
        levelKnob.setValue(0.5);
        levelKnob.onValueChange = [this] {
            audioProcessor.setlevel(levelKnob.getValue());
            };


        gateKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        gainKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
   //     toneKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);



        
        gateKnob.setValue(audioProcessor.getGateValue(), juce::dontSendNotification);
        gainKnob.setValue(audioProcessor.getGainValue(), juce::dontSendNotification);
   //     toneKnob.setValue(audioProcessor.getToneValue(), juce::dontSendNotification);
        levelKnob.setValue(audioProcessor.getlevelValue(), juce::dontSendNotification);
        bypassBtn.setToggleState(audioProcessor.isBypassed(), juce::dontSendNotification);
        cabBtn.setToggleState(audioProcessor.isCab(), juce::dontSendNotification);
        leadBtn.setToggleState(audioProcessor.isLead(), juce::dontSendNotification);

            
        
        
        
        
        
        
        
    //levelKnob.setValue(audioProcessor.getlevelValue(), juce::dontSendNotification);
        bypassBtn.setToggleState(audioProcessor.isBypassed(), juce::dontSendNotification);
        

}

DunwichAudioProcessorEditor::~DunwichAudioProcessorEditor()
{
}

//==============================================================================
void DunwichAudioProcessorEditor::paint (juce::Graphics& g)
{
    if (backgroundImage.isValid() && backgroundOff.isValid())
        {
            if (!bypassBtn.getToggleState()) {
                g.drawImageWithin(backgroundImage, 0, 0, getWidth(), getHeight(),
                                  juce::RectanglePlacement::fillDestination);
            }
            else {
                g.drawImageWithin(backgroundOff, 0, 0, getWidth(), getHeight(),
                                  juce::RectanglePlacement::fillDestination);
            }
        }
        else
        {
            // Fallback: se l'immagine non c'è, usa un colore scuro
            g.fillAll (juce::Colours::darkgrey);
            g.setColour (juce::Colours::white);
            g.drawText ("Immagine non caricata", getLocalBounds(),
                        juce::Justification::centred);
        }
    
   
}

void DunwichAudioProcessorEditor::resized()
{
   
    const int knobSize = 90;
    const int knobY = 426;
    const int knobCenter = knobSize / 2;
    
    gateKnob.setBounds(knobCenter + JUCE_LIVE_CONSTANT(250), knobY, knobSize, knobSize);
    gainKnob.setBounds(knobCenter + JUCE_LIVE_CONSTANT(368), knobY, knobSize, knobSize);
 //   toneKnob.setBounds(knobCenter + 453, knobY, knobSize, knobSize);
    levelKnob.setBounds(knobCenter + JUCE_LIVE_CONSTANT(608), knobY, knobSize, knobSize);
    
    const int bypassY = getHeight() / 2 + 100;   // adatta al tuo design
    const int bypassSize = 140;
    bypassBtn.setBounds(JUCE_LIVE_CONSTANT(62), bypassY, bypassSize, bypassSize);
  
    const int cabY = getHeight() / 2 + 100;   // adatta al tuo design
    cabBtn.setBounds(JUCE_LIVE_CONSTANT(158), cabY, bypassSize, bypassSize);
    
    const int leadSize = (72);
    const int leadX = leadSize / 2 + JUCE_LIVE_CONSTANT(506);
    const int leadY =leadSize / 2 + JUCE_LIVE_CONSTANT(415);
    leadBtn.setBounds(leadX, leadY, leadSize, leadSize);
    
}
