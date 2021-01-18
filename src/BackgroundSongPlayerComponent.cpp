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

#include "midistar/BackgroundSongPlayerComponent.h"

#include <iostream>

#include "midistar/Game.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiNoteComponent.h"

namespace midistar {

BackgroundSongPlayerComponent::BackgroundSongPlayerComponent()
    : Component{ Component::BACKGROUND_SONG_PLAYER } {
}

void BackgroundSongPlayerComponent::Update(Game* g, GameObject*, int) {
    auto& current_scene = g->GetCurrentScene();

    auto game_objects = current_scene.GetGameObjectsByTag("MidiFile");
    if (game_objects.size()) {
        auto midi_file_game_object = game_objects[0];
        auto midi_file_in_component = midi_file_game_object->
            GetComponent<MidiFileInComponent>(Component::MIDI_FILE_IN);

        for (MidiMessage msg : midi_file_in_component->GetMessages()) {
            if (msg.IsNote()) {
                auto game_object = new GameObject{};
                game_object->SetComponent(
                    new MidiNoteComponent{
                        msg.IsNoteOn()
                        , msg.GetChannel()
                        , msg.GetKey()
                        , msg.GetVelocity()
                    });
                current_scene.AddGameObject(game_object);
            }
        }
    }
}

}  // End namespace midistar
