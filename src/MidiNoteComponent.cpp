/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#include "midistar/MidiOutputComponent.h"

namespace midistar {

MidiNoteComponent::MidiNoteComponent(bool on, int chan, int note, int vel)
        : Component{Component::MIDI_NOTE}
        , chan_{chan}
        , note_{note}
        , on_{on}
        , vel_{vel} {
}

void MidiNoteComponent::Update(Game* g, GameObject* o, int) {
    auto midi_out_game_object = g->GetCurrentScene().GetFirstGameObjectByTag(
        "MidiOut");
    auto midi_out_component = midi_out_game_object->GetComponent<
        MidiOutputComponent>(Component::MIDI_OUTPUT);

    if (on_) {
        midi_out_component->TurnMidiNoteOn(chan_, note_, vel_);
    } else {
        midi_out_component->TurnMidiNoteOff(chan_, note_);
    }
    o->DeleteComponent(GetType());
}

}   // End namespace midistar
