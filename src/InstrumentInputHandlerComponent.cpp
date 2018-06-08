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

#include "midistar/InstrumentInputHandlerComponent.h"

#include "midistar/CollidableComponent.h"
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
        , set_active_{false}
        , shift_{shift} {
}

void InstrumentInputHandlerComponent::SetActive(bool active) {
    set_active_ = active;
}

void InstrumentInputHandlerComponent::Update(Game* g, GameObject<sf::Transformable>* o, int) {
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
        // pressed
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

    // If this instrument is activated...
    if (key_down_ || set_active_) {
        // Set the GraphicsComponent and send a note on event
        if (!o->HasComponent(Component::COLLIDABLE)) {
            o->SetComponent(new CollidableComponent{});
            o->SetComponent(new InvertColourComponent{static_cast<char>(0xa0)});
            o->SetComponent(new MidiNoteComponent{
                    true
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()});
       }
    // If it's not activated but the CollidableComponent is set...
    } else if (o->HasComponent(Component::COLLIDABLE)) {
        // Remove it and send a note off event
        o->DeleteComponent(Component::COLLIDABLE);
        o->SetComponent(new InvertColourComponent{static_cast<char>(0xa0)});
        o->SetComponent(new MidiNoteComponent{
                false
                , note->GetChannel()
                , note->GetKey()
                , note->GetVelocity()});
    }
}

}  // End namespace midistar
