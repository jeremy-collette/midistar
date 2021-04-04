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

#include "midistar/PhantomNoteComponent.h"

#include "midistar/Config.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiNoteComponent.h"

namespace midistar {

PhantomNoteComponent::PhantomNoteComponent(std::set<int> midi_keys)
    : Component{Component::PHANTOM_NOTE}
        , midi_keys_{ midi_keys } {
}

void PhantomNoteComponent::Update(Game* g, GameObject* o, int) {
    // Here we handle MIDI keys that are not handled by instruments.
    // This allows the playing of instrument notes that aren't shown on screen
    // (e.g. a drum that isn't part of the current song).
    auto midi_instrument_game_object = g->GetCurrentScene().
        GetFirstGameObjectByTag("MidiInstrument");
    auto midi_instrument_in = midi_instrument_game_object->GetComponent<
        MidiFileInComponent>(Component::MIDI_INSTRUMENT_IN);

    for (const auto& msg : midi_instrument_in->GetMessages()) {
        if (msg.IsNote() && midi_keys_.count(msg.GetKey())) {
            auto child = new GameObject{};
            child->SetComponent(new MidiNoteComponent{
                    msg.IsNoteOn()
                    , 9
                    , msg.GetKey()
                    , Config::GetInstance().GetMidiOutVelocity() });

            o->AddChild(child);
        }
    }
}

}   // End namespace midistar
