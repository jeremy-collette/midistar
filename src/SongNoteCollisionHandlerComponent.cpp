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

#include "midistar/SongNoteCollisionHandlerComponent.h"

#include <algorithm>

#include "midistar/CollisionDetectorComponent.h"
#include "midistar/Config.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"

namespace midistar {

SongNoteCollisionHandlerComponent::SongNoteCollisionHandlerComponent()
        : CollisionHandlerComponent{Component::NOTE_COLLISION_HANDLER} {
}

void SongNoteCollisionHandlerComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , std::vector<GameObject*> colliding_with) {
    // Handle each collision
    for (auto& collider : colliding_with) {
        HandleCollision(g, o, collider);
    }
}

void SongNoteCollisionHandlerComponent::HandleCollision(
        Game* g
        , GameObject* o
        , GameObject* collider) {
    // We only want to handle collisions with instruments
    if (!collider->HasComponent(Component::INSTRUMENT)) {
        return;
    }

    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return;
    }
    auto graphics = o->GetComponent<GraphicsComponent>(Component::GRAPHICS);
    if (!graphics) {
        return;
    }
    auto other_note = collider->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
    // Check it's the correct instrument - we may collide with
    // neighbouring instruments if they overlap on the screen.
    if (!other_note || other_note->GetKey() != note->GetKey()) {
        return;
    }
    auto other_graphics = collider->GetComponent<GraphicsComponent>(
            Component::GRAPHICS);
    if (!other_graphics) {
        return;
    }

    // Get position and size info
    double x, y, width, height;
    o->GetPosition(&x, &y);
    graphics->GetSize(&width, &height);
    double inst_x, inst_y, inst_w, inst_h;
    collider->GetPosition(&inst_x, &inst_y);
    other_graphics->GetSize(&inst_w, &inst_h);

    // Check if the note is in the playable part of the insrtument.
    if (y > inst_y + NOTE_COLLISION_CUTOFF) {
        return;
    }

    // If the bottom of the note is outside the playable part, separate the
    // part below the cutoff in to a different (unplayable) note. This section
    // of the note has been missed.
    if (y + height > inst_y + NOTE_COLLISION_CUTOFF) {
        auto note = o->GetComponent<NoteInfoComponent>(
                Component::NOTE_INFO);
        if (!note) {
            return;
        }

        GameObject* half = g->GetGameObjectFactory().CreateSongNote(
                    note->GetTrack()
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()
                    , 0);

        // We don't want complete note behaviour - this is an
        // unplayable note
        half->DeleteComponent(Component::NOTE_COLLISION_HANDLER);
        half->SetPosition(x, inst_y + NOTE_COLLISION_CUTOFF);

        auto half_graphics = half->GetComponent<GraphicsComponent>(
                Component::GRAPHICS);
        if (!half_graphics) {
            return;
        }

        half_graphics->SetSize(width, (y + height) - (inst_y
                    + NOTE_COLLISION_CUTOFF));
        g->AddGameObject(half);
    }

    // Now we are guaranteed to have a note that ends before the bottom
    // of the instrument (see above).
    //
    // If the top of the note is before the instrument:
    if (y < inst_y) {
        // Resize the note so that it is intersecting with the instrument by
        // one pixel
        o->SetComponent(new ResizeComponent{width, inst_y-y + 1});
    } else {  // Otherwise 'o' is now purely within the instrument and
             // can be removed.
        o->SetComponent(new ResizeComponent{0, 0});
    }
}

}  // End namespace midistar
