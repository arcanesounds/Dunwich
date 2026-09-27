/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Dunwich.h" // MODIFICARE SEMPRE

//==============================================================================
DunwichAudioProcessor::DunwichAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    oversampler (2, 1, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR)
#endif
{
}

DunwichAudioProcessor::~DunwichAudioProcessor()
{
}


void DunwichAudioProcessor::setGate(float gate)
{
    fUI->setParamValue("gate", gate);
}

void DunwichAudioProcessor::setGain(float gain)
{
    fUI->setParamValue("gain", gain);
}

/*
void DunwichAudioProcessor::setTone(float tone)
{
    fUI->setParamValue("tone", tone);
}*/

void DunwichAudioProcessor::setlevel(float level)
{
    fUI->setParamValue("level", level);
}

void DunwichAudioProcessor::setBypass(bool bypass)
{
    if(bypass) {
        fUI->setParamValue("bypass",1);
    } else {
        fUI->setParamValue("bypass",0);
    }
}

void DunwichAudioProcessor::setCab(bool cabinet)
{
    if(cabinet) {
        fUI->setParamValue("cabBtn",1);
    } else {
        fUI->setParamValue("cabBtn",0);
    }
}

void DunwichAudioProcessor::setLead(bool lead)
{
    if(lead) {
        fUI->setParamValue("lead",1);
    } else {
        fUI->setParamValue("lead",0);
    }
}

float DunwichAudioProcessor::getGateValue() const
{
    return fUI ? fUI->getParamValue("gate") : -85.0;
}

float DunwichAudioProcessor::getGainValue() const
{
    return fUI ? fUI->getParamValue("gain") : 0.85;
}
/*
float DunwichAudioProcessor::getToneValue() const
{
    return fUI ? fUI->getParamValue("tone") : 0.85;
}
*/
float DunwichAudioProcessor::getlevelValue() const
{
    return fUI ? fUI->getParamValue("level") : 0.5;
}

bool DunwichAudioProcessor::isBypassed() const
{
    return fUI ? (fUI->getParamValue("bypass") > 0.5f) : false;
}

bool DunwichAudioProcessor::isCab() const
{
    return fUI ? (fUI->getParamValue("cabBtn") > 0.5f) : false;
}

bool DunwichAudioProcessor::isLead() const
{
    return fUI ? (fUI->getParamValue("lead") > 0.5f) : false;
}


//==============================================================================
const juce::String DunwichAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DunwichAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DunwichAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DunwichAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DunwichAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DunwichAudioProcessor::getNumPrograms()
{
    return 1;
}

int DunwichAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DunwichAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DunwichAudioProcessor::getProgramName (int index)
{
    return {};
}

void DunwichAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DunwichAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Inizializza Faust
    
    fDSP = new mydsp;
    fDSP->init(sampleRate * oversampler.getOversamplingFactor());
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    // Inizializza oversampler
    oversampler.reset();
    oversampler.initProcessing((size_t)samplesPerBlock);
    
    // Buffer grandi 4x (per l'oversampling)
    int numSamplesUp = samplesPerBlock * oversampler.getOversamplingFactor();
    
    inputs = new float*[2];
    outputs = new float*[2];
    for (int channel = 0; channel < 2; ++channel) {
        inputs[channel] = new float[numSamplesUp];
        outputs[channel] = new float[numSamplesUp];
    }
    
    fUI->setParamValue("bypass", 0);
    fUI->setParamValue("cabBtn", 0);
    fUI->setParamValue("lead", 1);
}

void DunwichAudioProcessor::releaseResources()
{
    delete fDSP;
    delete fUI;
    
    for (int channel = 0; channel < 2; ++channel) {
        delete[] inputs[channel];
        delete[] outputs[channel];
    }
    delete[] inputs;
    delete[] outputs;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DunwichAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
    
}
#endif

//==============================================================================
void DunwichAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
        juce::ignoreUnused(midiMessages);
        juce::ScopedNoDenormals noDenormals;

        const int totalNumInputChannels  = getTotalNumInputChannels();
        const int totalNumOutputChannels = getTotalNumOutputChannels();

        // 1. Pulisce i canali di output in eccesso per evitare fruscii
        for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
            buffer.clear (i, 0, buffer.getNumSamples());

        if (inputs == nullptr || outputs == nullptr || fDSP == nullptr)
            return;

        // 2. Chiediamo a Faust di quanti canali ha realmente bisogno
        const int faustInputs  = fDSP->getNumInputs();  // Restituisce 1 (mono) o 2 (stereo)
        const int faustOutputs = fDSP->getNumOutputs(); // Restituisce 1 (mono) o 2 (stereo)

        // ============================================================
        // OVERSAMPLING + PROCESSING FAUST (Dinamico e Sicuro)
        // ============================================================

        // A. Crea il blocco audio e applica l'upsampling
        juce::dsp::AudioBlock<float> block(buffer);
        auto oversampledBlock = oversampler.processSamplesUp(block);
        
        const int numSamplesUp = (int)oversampledBlock.getNumSamples();
        const int numOversampledChannels = (int)oversampledBlock.getNumChannels();

        // B. COPIA INPUT: Riempie gli ingressi di Faust in sicurezza
        for (int ch = 0; ch < faustInputs; ++ch)
        {
            // Se Faust vuole 2 canali ma la DAW ne manda 1, usa il canale 0 per entrambi.
            // Se la DAW manda 2 canali e Faust ne vuole 1, prende solo il canale 0.
            int srcChannel = ch % numOversampledChannels;
            
            const float* src = oversampledBlock.getChannelPointer(srcChannel);
            float* dst = inputs[ch];

            std::copy(src, src + numSamplesUp, dst);
        }

        // C. PROCESSA CON FAUST
        fDSP->compute(numSamplesUp, inputs, outputs);

        // D. COPIA OUTPUT: Scrive i risultati nel buffer JUCE
        for (int ch = 0; ch < numOversampledChannels; ++ch)
        {
            // Se la DAW è Stereo (2 ch) ma Faust è Mono (1 ch), duplica l'uscita mono su L e R
            int srcChannel = ch % faustOutputs;
            
            const float* src = outputs[srcChannel];
            float* dst = oversampledBlock.getChannelPointer(ch);

            std::copy(src, src + numSamplesUp, dst);
        }

        // E. Downsample (torna a 1x nel buffer originale di JUCE)
        oversampler.processSamplesDown(block);
}

double DunwichAudioProcessor::getLatencySamples() const
{
    return oversampler.getLatencyInSamples();
}


//==============================================================================
bool DunwichAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* DunwichAudioProcessor::createEditor()
{
    return new DunwichAudioProcessorEditor (*this);
}

//==============================================================================
void DunwichAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ValueTree state("Dunwich");
    
    if (fUI != nullptr)
    {
        state.setProperty("gate", fUI->getParamValue("gate"), nullptr);
        state.setProperty("gain", fUI->getParamValue("gain"), nullptr);
   //     state.setProperty("tone", fUI->getParamValue("tone"), nullptr);
        state.setProperty("level", fUI->getParamValue("level"), nullptr);
        state.setProperty("bypass", fUI->getParamValue("bypass"), nullptr);
        state.setProperty("cabBtn", fUI->getParamValue("cabBtn"), nullptr);
        state.setProperty("lead", fUI->getParamValue("lead"), nullptr);
    } else {
                state.setProperty("gate", -85.0, nullptr);
                state.setProperty("gain", 0.85, nullptr);
             //   state.setProperty("tone", 0.85, nullptr);
                state.setProperty("level", 0.5, nullptr);
                state.setProperty("bypass", 0.0, nullptr);
                state.setProperty("cabBtn", 0.0, nullptr);
        
                state.setProperty("lead", 1.0, nullptr);
        
    }
    
        std::unique_ptr<juce::XmlElement> xml(state.createXml());
        copyXmlToBinary(*xml, destData);
}

void DunwichAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
       
       if (xml != nullptr && fUI != nullptr)
       {
           // Converte l'XML in ValueTree
           juce::ValueTree state = juce::ValueTree::fromXml(*xml);
           
           // Verifica che sia il ValueTree giusto
           if (state.isValid() && state.hasType("Dunwich"))
           {
               // Legge i valori salvati e li applica
               fUI->setParamValue("gate", state.getProperty("gate", -85.0));
               fUI->setParamValue("gain", state.getProperty("gain", 0.85));
             //  fUI->setParamValue("tone", state.getProperty("tone", 0.85));
               fUI->setParamValue("level", state.getProperty("level", 0.5));
               fUI->setParamValue("cabBtn", state.getProperty("cabBtn", 0.0));
               fUI->setParamValue("bypass", state.getProperty("bypass", 0.0));
               fUI->setParamValue("lead", state.getProperty("lead", 1.0));
           }
       }
}

//==============================================================================
// Factory del plugin
//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DunwichAudioProcessor();
}
