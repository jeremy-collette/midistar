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

#include "midistar/SongNoteCreatorComponent.h"

#include <iostream>

#include "midistar/Game.h"
#include "midistar/MidiFileInComponent.h"

namespace midistar {

SongNoteCreatorComponent::SongNoteCreatorComponent(
    GameObjectFactory* game_object_factory)
        : Component{Component::SONG_NOTE_CREATOR}
        , game_object_factory_{ game_object_factory } {
}

void SongNoteCreatorComponent::Update(Game* g, GameObject*, int) {
    auto& current_scene = g->GetCurrentScene();

    auto game_objects = current_scene.GetGameObjectsByTag("MidiFile");
    if (game_objects.size()) {
        auto midi_file_game_object = game_objects[0];
        auto midi_file_in_component = midi_file_game_object->
            GetComponent<MidiFileInComponent>(Component::MIDI_FILE_IN);

        for (MidiMessage msg : midi_file_in_component->GetMessages()) {
            if (msg.IsNoteOn()) {
                current_scene.AddGameObject(game_object_factory_->
                    CreateSongNote(
                        msg.GetTrack()
                        , msg.GetChannel()
                        , msg.GetKey()
                        , msg.GetVelocity()
                        , msg.GetDuration()));
            }
        }
    }
}

}  // End namespace midistar
