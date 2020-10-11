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

#include "midistar/DrumSongNoteCollisionHandlerComponent.h"

#include <algorithm>
#include <SFML/Graphics.hpp>

#include "midistar/Config.h"
#include "midistar/InstrumentInputHandlerComponent.h"
#include "midistar/GameObjectFactory.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/OutlineEffectComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

DrumSongNoteCollisionHandlerComponent::DrumSongNoteCollisionHandlerComponent(
    GameObjectFactory* game_object_factory)
        : CollisionHandlerComponent{ Component::DRUM_NOTE_COLLISION_HANDLER }
        , game_object_factory_{ game_object_factory }
        , dont_collide_{ false } {
}

void DrumSongNoteCollisionHandlerComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , int
        , std::vector<GameObject*> colliding_with) {
    if (dont_collide_) {
        return;
    }

    // Handle each collision
    GameObject* valid_collider = nullptr;
    for (auto& collider : colliding_with) {
        if (HandleCollision(g, o, collider)) {
            valid_collider = collider;
        }
    }

    // If we are being played, let's add a drum play effect
    if (valid_collider) {
        auto play_effect = game_object_factory_->CreateNotePlayEffect(o);
        g->GetCurrentScene().AddGameObject(play_effect);
    }
}

bool DrumSongNoteCollisionHandlerComponent::HandleCollision(
        Game*
        , GameObject* o
        , GameObject* collider) {
    // We only want to handle collisions with instruments
    if (!collider->HasComponent(Component::INSTRUMENT)) {
        return false;
    }

    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return false;
    }
    auto other_note = collider->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
    // Check it's the correct instrument - we may collide with
    // neighbouring instruments if they overlap on the screen.
    if (!other_note || other_note->GetKey() != note->GetKey()) {
        return false;
    }

    // Get position and size info
    double x, y, width, height;
    o->GetPosition(&x, &y);
    o->GetSize(&width, &height);
    double inst_x, inst_y, inst_w, inst_h;
    collider->GetPosition(&inst_x, &inst_y);
    collider->GetSize(&inst_w, &inst_h);

    // Check that the instrument has not already played a note this tick
    auto inst_input_handler = collider->GetComponent<
        InstrumentInputHandlerComponent>(
            Component::INSTRUMENT_INPUT_HANDLER);
    if (inst_input_handler) {
        if (inst_input_handler->GetNotePlayed()) {
            return false;
        }
        inst_input_handler->SetNotePlayed(true);
    }

    // Make the note invisible (it has been played)
    o->SetComponent(new ResizeComponent{0, 0});
    o->DeleteComponent(GetType());
    return true;
}

void DrumSongNoteCollisionHandlerComponent::SetDoNotCollide(bool dont_collide) {
    dont_collide_ = dont_collide;
}

}  // End namespace midistar
