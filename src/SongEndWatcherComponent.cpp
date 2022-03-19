/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
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

#include "midistar/SongEndWatcherComponent.h"

#include "midistar/EndOfSongSceneFactory.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/ScoreManagerComponent.h"

namespace midistar {

SongEndWatcherComponent::SongEndWatcherComponent()
        : Component{ Component::SONG_END_WATCHER } {
}

void SongEndWatcherComponent::Update(Game* g, GameObject* o, int) {
    auto midi_file_component = o->GetComponent<
        MidiFileInComponent>(Component::MIDI_FILE_IN);

    auto midi_file_eof = !midi_file_component || midi_file_component->IsEof();

    auto has_song_notes = g->GetCurrentScene().GetGameObjectsByTag("SongNote")
        .size();

    if (!midi_file_eof || has_song_notes) {
        return;
    }

    // If the song has finished, set scene to intro
    auto intro_scene_factory = EndOfSongSceneFactory{};
    auto next_scene = new Scene{
        g,
        &g->GetWindow(),
        std::vector<GameObject*>{ }
    };

    auto score_object = g->GetCurrentScene().GetFirstGameObjectByTag(
        "ScoreManager");
    auto score_manager_component = score_object->GetComponent<
        ScoreManagerComponent>(Component::SCORE_MANAGER);
    auto score = score_manager_component->GetScore();

    if (!intro_scene_factory.Create(
        g
        , &g->GetWindow()
        , &next_scene
        , score)) {
        throw "Could not create Intro scene.";
    }

    g->SetScene(next_scene);
}

}  // End namespace midistar

