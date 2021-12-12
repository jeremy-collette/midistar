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

#include "midistar/PracticeModeComponent.h"

namespace midistar {

PracticeModeComponent::PracticeModeComponent(
    std::unordered_set<SongNoteComponent*>* to_play)
        : CollisionHandlerComponent{ Component::PRACTICE_MODE }
        , to_play_{ to_play }
        , colliding_instrument_{ false } {
}

void PracticeModeComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , int
        , std::vector<GameObject*> colliding_with) {
    for (auto collider : colliding_with) {
        HandleCollision(g, o, collider);
    }
}

void PracticeModeComponent::HandleCollision(
        Game*
        , GameObject* o
        , GameObject* collider) {
    if (collider->HasComponent(Component::INSTRUMENT)) {
        auto song_note_component = o->GetComponent<SongNoteComponent>(
            Component::SONG_NOTE);
        to_play_->insert(song_note_component);

        if (collider->HasComponent(Component::COLLIDABLE)) {
            to_play_->erase(song_note_component);
        }
    }
}

void PracticeModeComponent::Update(
        Game* g
        , GameObject* o
        , int delta) {
    CollisionHandlerComponent::Update(g, o, delta);

    auto time_scale = to_play_->size() ? 0.0f : 1.0f;
    o->SetTimeScale(time_scale);
}

}  // End namespace midistar
