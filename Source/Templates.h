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
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

const char *HowTo =
"######################\n"
"# How to use PyoPlug #\n"
"######################\n"
"\n"
"# Press the 'Compute' button to compile your code in the plugin processor.\n"
"# Opening a file or typing some text don't automatically compile the code!\n"
"\n"
"# The Input object is the entry point of the plugin.\n"
"# Give it a list of the channels you want to process.\n"
"input = Input([0, 1])\n"
"\n"
"# The out() method send this particular signal to the plugin output(s).\n"
"input.out()\n"
"\n"
"# The BPM variable holds the project's BPM.\n"
"# Duration of a quarter.\n"
"quarter = 60 / BPM\n"
"\n"
"# Add some delay to the signal.\n"
"# Yes, you can call the out() method on many objects (signals will be added up).\n" 
"delay = Delay(input, delay=quarter, maxdelay=quarter, feedback=0.5, mul=0.7).out()\n"
"\n"
"# Up to 12 automations can be retrieved in the code, they're named PARAM1, PARAM2, ..., PARAM12.\n"
"# Automate the first parameter to hear a lower octave transposition on the input.\n"
"harmo = Harmonizer(input, transpo=-12, mul=PARAM1).out()\n";

const char *StereoDelay =
"input = Input([0, 1]).out()\n"
"\n"
"# Duration of a quarter.\n"
"delaytime = 60 / BPM\n"
"\n"
"stdel = Delay(input, delay=[delaytime, delaytime/2],\n"
"              maxdelay=delaytime, feedback=0.5).out()\n";

const char *StereoVerb =
"input = Input([0, 1]).out()\n"
"\n"
"highpassed = ButHP(input, 100)\n"
"stereorev = STRev(highpassed, inpos=[.1, .9], revtime=1.5,\n"
"                  cutoff=5000, bal=.3, roomSize=1.5).out()\n";

const char *ConvoVerb =
"input = Input([0, 1])\n"
"\n"
"reverb = CvlVerb(input, bal=0.25).out()\n";

const char *Resonators = 
"input = Input([0, 1])\n"
"\n"
"fundamental = 20\n"
"spread = 1.1\n"
"frequencies = [fundamental * pow(i, spread) for i in range(1, 25)]\n"
"\n"
"resonators = Waveguide(input, freq=frequencies, dur=30, mul=0.05)\n"
"\n"
"balance = Interp(input, resonators.mix(2), interp=0.3, mul=0.7).out()\n";

const char *Phasing =
"input = Input([0, 1], mul=0.7).out()\n"
"\n"
"# These LFOs modulate the `freq`, `spread` and `q` arguments of\n"
"# the Phaser object. We give a list of two frequencies in order\n"
"# to create two-streams LFOs, therefore a stereo phasing effect.\n"
"lf1 = Sine(freq=[.1, .15]).range(100, 400)\n"
"lf2 = Sine(freq=[.18, .13]).range(1.1, 1.9)\n"
"lf3 = Sine(freq=[.07, .09]).range(1, 8)\n"
"\n"
"# Apply the phasing effect with 20 notches.\n"
"b = Phaser(input, freq=lf1, spread=lf2, q=lf3, num=20, mul=0.7).out()\n";

const char *MidiSynth =
"class Synth:\n"
"    def __init__(self, transpo=1):\n"
"        # transposition factor.\n"
"        self.transpo = Sig(transpo)\n"
"        # receives midi notes, convert pitch to Hz and manage 10 voices of polyphony.\n"
"        self.note = Notein(poly=10, scale=1, first=0, last=127)\n"
"\n"
"        # handle pitch and velocity (Notein output normalized amplitude (0 -> 1).\n"
"        self.pit = self.note['pitch'] * self.transpo\n"
"        self.amp = MidiAdsr(self.note['velocity'], attack=0.001,\n" 
"                            decay=.1, sustain=.7, release=2, mul=.1)\n"
"\n"
"        # Stereo oscillator, mixed from 10 to 1 stream to avoid alternating channels.\n"
"        self.osc1 = RCOsc(self.pit, sharp=0.5, mul=self.amp).mix(1)\n"
"        self.osc2 = RCOsc(self.pit*0.997, sharp=0.5, mul=self.amp).mix(1)\n"
"\n"
"        # stereo mix\n"
"        self.mix = Mix([self.osc1, self.osc2], voices=2)\n"
"\n"
"    def out(self):\n"
"        'Activates the objet and return self.'\n"
"        self.mix.out()\n"
"        return self\n"
"\n"
"    def sig(self):\n"
"        'Returns the last audio objet for future processing.'\n"
"        return self.mix\n"
"\n"
"synth = Synth()\n"
"\n"
"rev = STRev(synth.sig(), inpos=[0.5], revtime=2, cutoff=4000, bal=.15).out()\n";

StringArray templates ({ nullptr, HowTo, StereoDelay, StereoVerb, ConvoVerb, Resonators, Phasing, MidiSynth });
StringArray templatesNames ({ "HowTo", "StereoDelay", "StereoVerb", "ConvoVerb", "Resonators", "Phasing", "MidiSynth" });
