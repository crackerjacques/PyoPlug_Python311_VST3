/**************************************************************************
 * Copyright 2018 Olivier Belanger                                        *
 *                                                                        *
 * This file is part of pyo-plug, an audio plugin using the python        *
 * module pyo to create the dsp.                                          *
 *                                                                        *
 * pyo-plug is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU Lesser General Public License as         *
 * published by the Free Software Foundation, either version 3 of the     *
 * License, or (at your option) any later version.                        *
 *                                                                        *
 * pyo-plug is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU Lesser General Public License for more details.                    *
 *                                                                        *
 * You should have received a copy of the GNU LGPL along with pyo-plug.   *
 * If not, see <http://www.gnu.org/licenses/>.                            *
 *                                                                        *
 *************************************************************************/
#include "PluginProcessor.h"
#include "PluginEditor.h"

const char *initialDSP = "input = Input([0, 1])\n\ninput.out()\n";

AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    for (int i = 1; i <= 12; i++) {
        parameters.push_back(std::make_unique<Parameter>(String("PARAM") + String(i),
                                                         String("PyoPlug parameter ") + String(i),
                                                         String(), NormalisableRange<float>(0.0f, 1.0f),
                                                         0.0f, nullptr, nullptr, true, true));
    }

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
PyoPlugAudioProcessor::PyoPlugAudioProcessor()
    : parameters (*this, nullptr, Identifier(JucePlugin_Name), createParameterLayout()) {
    currentCode = String(initialDSP);

    for (int i = 1; i <= 12; i++) {
        parameters.addParameterListener(String("PARAM") + String(i), this);
    }
    parameters.state = ValueTree(Identifier(JucePlugin_Name));
}

PyoPlugAudioProcessor::~PyoPlugAudioProcessor() {}

//==============================================================================
const String PyoPlugAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool PyoPlugAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PyoPlugAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PyoPlugAudioProcessor::silenceInProducesSilenceOut() const {
    return false;
}

double PyoPlugAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PyoPlugAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int PyoPlugAudioProcessor::getCurrentProgram() {
    return 0;
}

void PyoPlugAudioProcessor::setCurrentProgram (int index) {}

const String PyoPlugAudioProcessor::getProgramName (int index) {
    return String();
}

void PyoPlugAudioProcessor::changeProgramName (int index, const String& newName) {}

//==============================================================================
void PyoPlugAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    AudioPlayHead::CurrentPositionInfo infos;
    getPlayHead()->getCurrentPosition(infos);

    pyo.setup(getTotalNumOutputChannels(), samplesPerBlock, sampleRate);
    pyo.setbpm(infos.bpm);

    if (currentCode != "") {
        computeCode(currentCode);
    }

    keyboardState.reset();
}

void PyoPlugAudioProcessor::releaseResources() {
    keyboardState.reset();
}

void PyoPlugAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midi) {
    const int numSamples = buffer.getNumSamples();
    keyboardState.processNextMidiBuffer (midi, 0, numSamples, true);

    if (midi.getNumEvents() > 0) {
        for (const auto metadata : midi) {
            const auto msg = metadata.getMessage();
            unsigned int status = 0, data1 = 0, data2 = 0;
            if (msg.getRawDataSize() > 0) { status = msg.getRawData()[0]; }
            if (msg.getRawDataSize() > 1) { data1 = msg.getRawData()[1]; }
            if (msg.getRawDataSize() > 2) { data2 = msg.getRawData()[2]; }
            pyo.midi(status, data1, data2);
        }
        midi.clear();
    }

    pyo.process(buffer);
}

//==============================================================================
bool PyoPlugAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PyoPlugAudioProcessor::createEditor() {
    return new PyoPlugAudioProcessorEditor (*this);
}

//==============================================================================
void PyoPlugAudioProcessor::getStateInformation (MemoryBlock& destData) {
    String content(currentCode);
    destData.replaceWith((&content)->toUTF8(),
                         CharPointer_UTF8::getBytesRequiredFor(content.getCharPointer()));
}

void PyoPlugAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    currentCode = String::createStringFromData(data, sizeInBytes);
}

//==============================================================================
void PyoPlugAudioProcessor::computeCode(String code) {
    pyo.clear();
    for (int i = 1; i <= 12; i++) {
        pyo.exec(String("PARAM") + String(i) + String(" = SigTo(0.0, 0.025)"));
    }
    currentCode = code;
    pyo.exec(currentCode);
}

void PyoPlugAudioProcessor::parameterChanged(const String& parameterID, float newValue) {
    pyo.value(parameterID, newValue);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new PyoPlugAudioProcessor();
}
