/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
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

#include "midistar/MidiNoteComponent.h"

namespace midistar {

MidiNoteComponent::MidiNoteComponent(bool on, int chan, int note, int vel)
        : Component{Component::MIDI_NOTE}
        , chan_{chan}
        , note_{note}
        , on_{on}
        , vel_{vel} {
}

void MidiNoteComponent::Update(Game* g, GameObject<sf::Transformable>* o, int) {
    if (on_) {
        g->TurnMidiNoteOn(chan_, note_, vel_);
    } else {
        g->TurnMidiNoteOff(chan_, note_);
    }
    o->DeleteComponent(GetType());
}

}   // End namespace midistar
