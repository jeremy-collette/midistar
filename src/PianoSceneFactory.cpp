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

#include "midistar/PianoSceneFactory.h"

#include "midistar/Config.h"
#include "midistar/MidiFileGameObjectFactory.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiInstrumentGameObjectFactory.h"
#include "midistar/MidiOutputComponent.h"
#include "midistar/PianoGameObjectFactory.h"
#include "midistar/PauseSongGameObjectFactory.h"
#include "midistar/ScoreManagerFactory.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/SongEndWatcherComponent.h"
#include "midistar/SongSceneSfmlEventsHandlerComponent.h"
#include "midistar/SongNoteCreatorComponent.h"

namespace midistar {

PianoSceneFactory::PianoSceneFactory(
    const std::string midi_file_name)
        : midi_file_name_{ midi_file_name } {
}

bool PianoSceneFactory::Create(
        Game* game
        , sf::RenderWindow* render_window
        , Scene** scene) {
    // Create MIDI instrument GameObject to read input from MIDI instrument
    auto midi_instrument_object_factory = MidiInstrumentGameObjectFactory{};
    auto midi_port = Config::GetInstance().GetMidiInputPort();
    GameObject* midi_instrument_game_object = nullptr;
    if (!midi_instrument_object_factory.Create(
        midi_port
        , &midi_instrument_game_object)) {
        return false;
    }

    // Create MIDI file GameObject to read notes from MIDI file
    auto midi_file_object_factory = MidiFileGameObjectFactory{};
    GameObject* midi_file_game_object = nullptr;
    if (!midi_file_object_factory.Create(
        midi_file_name_,
        &midi_file_game_object)) {
        return false;
    }
    auto midi_file_in_component = midi_file_game_object->GetComponent<
        MidiFileInComponent>(Component::MIDI_FILE_IN);

    // Create Drum mode GameObjects
    double note_speed = (midi_file_in_component->
        GetTicksPerQuarterNote() /
        Config::GetInstance().GetMidiFileTicksPerUnitOfSpeed()) *
        Config::GetInstance().GetFallSpeedMultiplier();

    auto piano_scene_object_factory = new PianoGameObjectFactory(note_speed);
    if (!piano_scene_object_factory->Init()) {
        return false;
    }
    auto game_objects = piano_scene_object_factory->CreateInstrument();
    game_objects.push_back(midi_instrument_game_object);

    // Add component to create song notes from MIDI file
    midi_file_game_object->SetComponent(new SongNoteCreatorComponent{
        piano_scene_object_factory });
    midi_file_game_object->SetComponent(new SongEndWatcherComponent{});
    game_objects.push_back(midi_file_game_object);

    // Create game object to handle SFML events
    auto rect = new sf::RectangleShape{ {0, 0} };
    auto sfml_event_object = new GameObject{ rect, 0, 0, 0, 0 };
    sfml_event_object->AddTag("SfmlEvents");
    sfml_event_object->SetComponent(new SfmlEventsComponent{ render_window });
    sfml_event_object->SetComponent(
        new SongSceneSfmlEventsHandlerComponent{ });
    game_objects.push_back(sfml_event_object);

    // Create game object for MIDI out
    rect = new sf::RectangleShape{ {0, 0} };
    auto midi_out_game_object = new GameObject{ rect, 0, 0, 0, 0 };
    sfml_event_object->AddTag("MidiOut");
    auto midi_out = new MidiOut{ };
    if (!midi_out->Init()) {
        return false;
    }
    sfml_event_object->SetComponent(new MidiOutputComponent{ midi_out });
    game_objects.push_back(midi_out_game_object);

    // Create score renderer
    auto score_manager_factory = ScoreManagerFactory{};
    GameObject* score_renderer_game_object;
    if (!score_manager_factory.CreateScoreManager(&score_renderer_game_object)){
        return false;
    }
    game_objects.push_back(score_renderer_game_object);

    // Create pause song object
    auto pause_factory = PauseSongGameObjectFactory{ };
    GameObject* pause_game_object;
    if (!pause_factory.CreatePauseSongGameObject(
        midi_file_game_object
        , game_objects
        , &pause_game_object)) {
        return false;
    }
    game_objects.push_back(pause_game_object);

    // Create Scene
    *scene = new Scene{ game, render_window, game_objects };
    return true;
}

}   // End namespace midistar

