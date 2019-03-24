/*
 * midistar
 * Copyright (C) 2018-2019 Jeremy Collette.
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

#include "midistar/InstrumentInputHandlerComponent.h"

#include "midistar/CollidableComponent.h"
#include "midistar/DelayedComponentComponent.h"
#include "midistar/Config.h"
#include "midistar/Game.h"
#include "midistar/InvertColourComponent.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"

namespace midistar {

InstrumentInputHandlerComponent::InstrumentInputHandlerComponent(
    sf::Keyboard::Key key
    , bool ctrl
    , bool shift)
        : Component{Component::INSTRUMENT_INPUT_HANDLER}
        , ctrl_{ctrl}
        , key_{key}
        , key_down_{false}
        , note_played_{false}
        , set_active_{false}
        , shift_{shift}
        , uninvert_delay_{MAXIMUM_UNINVERT_DELAY}
        , was_active_{false} {
}

bool InstrumentInputHandlerComponent::GetNotePlayed() {
    return note_played_;
}

void InstrumentInputHandlerComponent::SetActive(bool active) {
    set_active_ = active;
}

void InstrumentInputHandlerComponent::SetNotePlayed(bool note_played) {
    note_played_ = note_played;
}

void InstrumentInputHandlerComponent::Update(Game* g, GameObject* o, int delta){
    // Check for required component
    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return;
    }

    // Check SFML events for key presses
    for (const auto& e : g->GetSfEvents()) {
        // Check if its the right key and event type
        if (e.key.code != key_ || (e.type != sf::Event::KeyPressed
                    && e.type != sf::Event::KeyReleased)) {
            continue;
        }

        // Determine if the key is up or down and the required modifiers are
        // pressed.
        key_down_ = e.type == sf::Event::KeyPressed
            && ctrl_ == e.key.control
            && shift_ == e.key.shift;
    }

    // Handle MIDI input port events.
    // If we find a note on event that matches this instruments MIDI note,
    // activate this instrument!
    for (const auto& msg : g->GetMidiInMessages()) {
        if (msg.IsNote() && msg.GetKey() == note->GetKey()) {
            key_down_ = msg.IsNoteOn();
        }
    }

    // If we've already played a note with this key press, disable collision (so
    // the player will have to play the instrument again).
    if (note_played_) {
        o->DeleteComponent(Component::COLLIDABLE);
    }

    // If this instrument is activated...
    if (key_down_ || set_active_) {
        // Set the GraphicsComponent and send a note on event
        if (!was_active_) {
            // If we've played another note before the instrument colour
            // un-inversion has taken place, cancel it so it doesn't mess up our
            // colours!
            if (o->HasComponent(Component::DELAYED_COMPONENT)
                    || o->HasComponent(Component::INVERT_COLOUR)) {
                o->DeleteComponent(Component::DELAYED_COMPONENT);
                o->DeleteComponent(Component::INVERT_COLOUR);
            } else {
                o->SetComponent(new InvertColourComponent{0xa0});
            }

            uninvert_delay_ = MAXIMUM_UNINVERT_DELAY;
            o->SetComponent(new CollidableComponent{});
            o->SetComponent(new MidiNoteComponent{
                    true
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()});
            was_active_ = true;
        } else {
            // If we were activated in a previous tick, let's start counting
            // down our uninvert delay.
            uninvert_delay_ -= delta;
        }
    // If it's not activated and the CollidableComponent is set... (just played
    // a note).
    } else if (was_active_) {
        // Remove it and send a note off event
        o->DeleteComponent(Component::COLLIDABLE);
        o->SetComponent(new MidiNoteComponent{
                false
                , note->GetChannel()
                , note->GetKey()
                , note->GetVelocity()});
        // We want to delay the colour of the instrument being uninverted
        // until a second after being played.
        o->SetComponent(new DelayedComponentComponent
            {
                new InvertColourComponent{0xa0}
                , uninvert_delay_
            });
        // Add reset logic here.
        note_played_ = false;
        was_active_ = false;
    }
}

}  // End namespace midistar
