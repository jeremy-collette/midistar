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

#include "midistar/PianoSceneFactory.h"

#include "midistar/Config.h"
#include "midistar/MidiFileGameObjectFactory.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiInstrumentGameObjectFactory.h"
#include "midistar/PianoGameObjectFactory.h"
#include "midistar/SongSceneSfmlEventsHandlerComponent.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/SongNoteCreatorComponent.h"


namespace midistar {

bool PianoSceneFactory::Create(
        Game* game
        , sf::RenderWindow& render_window
        , Scene** scene) {

    // Create MIDI instrument GameObject to read input from MIDI instrument
    auto midi_instrument_object_factory = MidiInstrumentGameObjectFactory{};
    GameObject* midi_instrument_game_object = nullptr;
    if (!midi_instrument_object_factory.Create(&midi_instrument_game_object)) {
        return false;
    }

    // Create MIDI file GameObject to read notes from MIDI file
    auto midi_file_object_factory = MidiFileGameObjectFactory{};
    GameObject* midi_file_game_object = nullptr;
    if (!midi_file_object_factory.Create(
        Config::GetInstance().GetMidiFileName(),
        &midi_file_game_object)) {
        return false;
    }
    auto midi_file_in_component = midi_file_game_object->GetComponent<
        MidiFileInComponent>(Component::MIDI_FILE_IN);

    // Create Drum mode GameObjects
    double note_speed = (midi_file_in_component->midi_file_in_->
        GetTicksPerQuarterNote() /
        Config::GetInstance().GetMidiFileTicksPerUnitOfSpeed()) *
        Config::GetInstance().GetFallSpeedMultiplier();

    auto max_note_duration = midi_file_in_component->midi_file_in_->
        GetMaximumNoteDuration();

    auto piano_scene_object_factory = new PianoGameObjectFactory(note_speed);
    if (!piano_scene_object_factory->Init()) {
        return false;
    }

    // Add component to create song notes from MIDI file
    midi_file_game_object->SetComponent(new SongNoteCreatorComponent{
        piano_scene_object_factory });

    // Create game object to handle SFML events
    auto rect = new sf::RectangleShape{ {0, 0} };
    auto sfml_event_object = new GameObject{ rect, 0, 0, 0, 0 };
    sfml_event_object->AddTag("SfmlEvents");
    sfml_event_object->SetComponent(new SfmlEventsComponent{ render_window });
    sfml_event_object->SetComponent(
        new SongSceneSfmlEventsHandlerComponent{ });

    // Get rest of game objects
    auto game_objects = piano_scene_object_factory->CreateInstrument();
    game_objects.push_back(midi_file_game_object);
    game_objects.push_back(midi_instrument_game_object);
    game_objects.push_back(sfml_event_object);
    *scene = new Scene{ game, render_window, game_objects };

    return true;
}

}   // End namespace midistar

