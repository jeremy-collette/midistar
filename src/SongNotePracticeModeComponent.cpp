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

#include "midistar/SongNotePracticeModeComponent.h"

#include "midistar/InstrumentPracticeModeComponent.h"

namespace midistar {

SongNotePracticeModeComponent::SongNotePracticeModeComponent()
        : Component{ Component::SONG_NOTE_PRACTICE_MODE } {
}

void SongNotePracticeModeComponent::Update(
        Game* g
        , GameObject* o
        , int delta) {

    if (g->GetCurrentScene().GetGameObjectsByTag("PauseGame").size()) {
        return;
    }

    auto instrument_notes = g->GetCurrentScene().GetGameObjectsByTag(
        "InstrumentNote");
    bool pause_game = false;
    for (auto inst_note : instrument_notes) {
        auto inst_practice_mode =
            inst_note->GetComponent<InstrumentPracticeModeComponent>(
                Component::INSTRUMENT_PRACTICE_MODE);
        if (inst_practice_mode->GetInstrumentIsCollidingWithNote()) {
            pause_game = true;
        }
    }

    auto time_scale = pause_game ? 0.0f : 1.0f;
    o->SetTimeScale(time_scale);
}

}  // End namespace midistar
