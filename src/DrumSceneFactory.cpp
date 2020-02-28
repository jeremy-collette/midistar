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

#include "midistar/DrumSceneFactory.h"

#include "midistar/Config.h"
#include "midistar/DrumGameObjectFactory.h"
#include "midistar/MidiFileGameObjectFactory.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiInstrumentGameObjectFactory.h"
#include "midistar/SongNoteCreatorComponent.h"

namespace midistar {

bool DrumSceneFactory::Create(
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

    auto unique_notes = midi_file_in_component->midi_file_in_->
        GetUniqueMidiNotes();

#ifdef DEBUG
    std::cout << "MIDI file unique notes: \n";
    for (const auto& n : unique_notes) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
#endif

    auto max_note_duration = midi_file_in_component->midi_file_in_->
        GetMaximumNoteDuration();

    auto drum_scene_object_factory = new DrumGameObjectFactory(
        note_speed
        , unique_notes
        , max_note_duration);

    if (!drum_scene_object_factory->Init()) {
        return false;
    }

    // Add component to create song notes from MIDI file
    midi_file_game_object->SetComponent(new SongNoteCreatorComponent{
        drum_scene_object_factory });

    auto game_objects = drum_scene_object_factory->CreateInstrument();
    game_objects.push_back(midi_file_game_object);
    game_objects.push_back(midi_instrument_game_object);
    *scene = new Scene{ game, render_window, game_objects };

    return true;
}

}   // End namespace midistar

