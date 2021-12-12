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

#include "midistar/InstrumentPracticeModeComponent.h"

#include "midistar/NoteInfoComponent.h"
#include "midistar/SongNotePracticeModeComponent.h"

namespace midistar {

InstrumentPracticeModeComponent::InstrumentPracticeModeComponent()
        : CollisionHandlerComponent{ Component::INSTRUMENT_PRACTICE_MODE }
        , colliding_with_note_{ false } {
}

void InstrumentPracticeModeComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , int
        , std::vector<GameObject*> colliding_with) {

    colliding_with_note_ = false;

    // We don't want to pause during practice mode if the note is actually
    // being played.
    if (o->HasComponent(Component::COLLIDABLE)) {
        return;
    }

    auto note = o->GetComponent<NoteInfoComponent>(Component::NOTE_INFO);
    if (!note) {
        return;
    }

    for (auto collider : colliding_with) {
        if (!collider->HasComponent(Component::SONG_NOTE)
            || !collider->HasComponent(Component::SONG_NOTE_PRACTICE_MODE)) {
            continue;
        }
        auto other_note = collider->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
        if (!other_note) {
            continue;
        }
        if (note->GetKey() == other_note->GetKey()) {
            colliding_with_note_ = true;
        }
    }
}

bool InstrumentPracticeModeComponent::GetInstrumentIsCollidingWithNote() {
    return colliding_with_note_;
}

}  // End namespace midistar
