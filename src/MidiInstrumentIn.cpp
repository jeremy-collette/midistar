/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "midistar/MidiInstrumentIn.h"

#include "midistar/Config.h"

namespace midistar {

MidiInstrumentIn::MidiInstrumentIn(int midi_port)
        : MidiPortIn{ midi_port } {
}

MidiInstrumentIn::~MidiInstrumentIn() {
}

bool MidiInstrumentIn::GetMessage(MidiMessage* message) {
    if (!MidiPortIn::GetMessage(message)) {
        return false;
    }

    if (message->IsNote()) {
        message->SetKey(Config::GetInstance().GetInstrumentMidiNoteRemapping(
                message->GetKey()));
    }
    return true;
}

}  // End namespace midistar
