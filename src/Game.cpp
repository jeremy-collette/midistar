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

#include "midistar/Game.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/Config.h"
#include "midistar/DefaultGameObjectFactory.h"
#include "midistar/DrumGameObjectFactory.h"
#include "midistar/PianoGameObjectFactory.h"
#include "midistar/IntroSceneGameObjectFactory.h"
#include "midistar/NoteInfoComponent.h"

// TODO(@jeremy): remove
#include "midistar/MidiFileGameObjectFactory.h"
#include "midistar/MidiInstrumentGameObjectFactory.h"

namespace midistar {

// TODO(@jeremy): Inject these dependencies
// TODO(@jeremy): Remove old code
Game::Game()
		: current_scene_{ nullptr }
		, current_scene_name_{ "" }
        , midi_file_in_component_{ nullptr }
        , midi_instrument_in_component_ { nullptr }
		, next_scene_{ nullptr }
		, object_factory_{ nullptr }
		, play_notes_{ false }
        , window_{sf::VideoMode(Config::GetInstance().GetScreenWidth()
                 , Config::GetInstance().GetScreenHeight())
                 , "midistar"
                 , Config::GetInstance().GetFullScreen() ?
                 sf::Style::Fullscreen : sf::Style::Default} {
}

Game::~Game() {
    if (object_factory_) {
        delete object_factory_;
    }

	if (current_scene_) {
		delete current_scene_;
	}
}

void Game::AddGameObject(GameObject* obj) {
	current_scene_->AddNewGameObject(obj);
}

GameObjectFactory& Game::GetGameObjectFactory() {
    return *object_factory_;
}

const std::vector<MidiMessage>& Game::GetMidiInMessages() {
    return midi_instrument_in_component_->GetMessages();
}

const std::vector<GameObject*>& Game::GetGameObjects() {
	return current_scene_->GetGameObjects();
}

const std::vector<sf::Event>& Game::GetSfEvents() {
    return sf_events_;
}

sf::RenderWindow& Game::GetWindow() {
    return window_;
}

bool Game::Init() {
    // Setup SFML window
    window_.setFramerateLimit(Config::GetInstance().
            GetMaximumFramesPerSecond());
    window_.setKeyRepeatEnabled(false);

    if (!midi_out_.Init()) {
        return false;
    }

	return SetScene("Intro");
}

void Game::Run() {
    unsigned int t = 0;
    sf::Clock clock;
    while (window_.isOpen()) {
		// If we're changing scenes, do it now
		if (next_scene_) {
			if (current_scene_) {
				delete current_scene_;
			}
			current_scene_ = next_scene_;
			next_scene_ = nullptr;
		}

        // Clean up from last tick
		// TODO(@jeremy): move this to scene
        window_.clear(object_factory_->GetBackgroundColour());
        int delta = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        // Handle updating
		current_scene_->Update(delta);
		current_scene_->Draw();
        window_.display();

        // Handle MIDI file events
		// TODO(@jeremy): This should be done inside a GameObject
        for (MidiMessage msg : midi_file_in_component_->GetMessages()) {
            if (msg.IsNoteOn()) {
                current_scene_->AddNewGameObject(object_factory_->
                        CreateSongNote(
                            msg.GetTrack()
                            , msg.GetChannel()
                            , msg.GetKey()
                            , msg.GetVelocity()
                            , msg.GetDuration()));
            }
        }

        // Handle MIDI port input events
		// TODO(@jeremy): This should be done inside a GameObject
        if (midi_instrument_in_component_) {
            for (MidiMessage msg : midi_instrument_in_component_->GetMessages()) {
#ifdef DEBUG
                if (msg.IsNoteOn()) {
                    std::cout << "Played: " << msg.GetKey() << '\n';
                }
#endif
            }
        }

        // Handle SFML events
	    // TODO(@jeremy): This should be done inside a GameObject
        sf_events_.clear();
        sf::Event event;
        while (window_.pollEvent(event)) {
            sf_events_.push_back(event);
            if (event.type == sf::Event::Closed
                || (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Escape)) {
				if (current_scene_name_ == "Intro") {
					window_.close();
					continue;
				} else {
					SetScene("Intro");
				}
            }
        }

        // Clean up!
		// TODO(@jeremy): move this inside scene
        CleanUpObjects();

        // If we're done playing the file and have no song notes to be played,
        // we're done!
        if (midi_file_in_component_->midi_file_in_->IsEof() && !CheckSongNotes()) {
            window_.close();
        }
        ++t;
    }
}

void Game::TurnMidiNoteOff(int chan, int note) {
    midi_out_.SendNoteOff(note, chan);
}

void Game::TurnMidiNoteOn(int chan, int note, int vel) {
    midi_out_.SendNoteOn(note, chan, vel);
}

bool Game::SetScene(std::string scene_name) {
	if (scene_name.find("Exit") != std::string::npos) {
		current_scene_name_ = "Exit";
		window_.close();
		return true;
	}

    auto midi_file_object_factory = MidiFileGameObjectFactory{};
    GameObject* midi_file_game_object = nullptr;
    if (!midi_file_object_factory.Create(
            Config::GetInstance().GetMidiFileName(),
            &midi_file_game_object)) {
        return false;
    }
    midi_file_in_component_ = midi_file_game_object->GetComponent<MidiFileInComponent>(Component::MIDI_FILE_IN);
    assert(midi_file_in_component_);

	// Setup GameObject factory and create GameObjects
	double note_speed = (midi_file_in_component_->midi_file_in_->GetTicksPerQuarterNote() /
		Config::GetInstance().GetMidiFileTicksPerUnitOfSpeed()) *
		Config::GetInstance().GetFallSpeedMultiplier();

	auto mode = Config::GetInstance().GetGameMode();
	auto unique_notes = midi_file_in_component_->midi_file_in_->GetUniqueMidiNotes();

#ifdef DEBUG
	std::cout << "MIDI file unique notes: \n";
	for (const auto& n : unique_notes) {
		std::cout << n << ' ';
	}
	std::cout << '\n';
#endif

	// TODO(@jeremy): clean up
	object_factory_ = new DefaultGameObjectFactory(note_speed);
	if (scene_name.find("Intro") != std::string::npos) {
		// Setup initial scene
		current_scene_name_ = "Intro";
		auto intro_scene_object_factory = new IntroSceneGameObjectFactory{};
		auto game_objects = intro_scene_object_factory->CreateGameObjects();
		next_scene_ = new Scene{ this, window_, game_objects };
		play_notes_ = false;

        midi_instrument_in_component_ = nullptr;
	}
	else
	{
		play_notes_ = true;

        auto midi_instrument_object_factory = MidiInstrumentGameObjectFactory{};
        GameObject* midi_instrument_in_game_object;
        if (!midi_instrument_object_factory.Create(&midi_instrument_in_game_object)) {
            return false;
        }
        midi_instrument_in_component_ = midi_instrument_in_game_object->GetComponent<MidiInstrumentInComponent>(Component::MIDI_INSTRUMENT_IN);
        assert(midi_instrument_in_component_);

		if (scene_name.find("Piano") != std::string::npos) {
			current_scene_name_ = "Piano";
			object_factory_ = new PianoGameObjectFactory(note_speed);
		}
		else if (scene_name.find("Drum") != std::string::npos) {
			current_scene_name_ = "Drum";
			auto max_note_duration = midi_file_in_component_->midi_file_in_->GetMaximumNoteDuration();
			object_factory_ = new DrumGameObjectFactory(note_speed, unique_notes
				, max_note_duration);
		}

		if (!object_factory_->Init()) {
			return false;
		}

		auto scene_objects = object_factory_->CreateInstrument();
        scene_objects.push_back(midi_file_game_object);
        scene_objects.push_back(midi_instrument_in_game_object);
		next_scene_ = new Scene{ this, window_, scene_objects};
	}

	if (!next_scene_->Init())
	{
		std::cerr << "Error initializing scene: " << scene_name << std::endl;
		return false;
	}

	return true;
}

bool Game::CheckSongNotes() {
	for (const auto& obj : current_scene_->GetGameObjects()) {
		if (obj->HasComponent(Component::SONG_NOTE)) {
			return true;
		}
	}
	return false;
}

// TODO(@jeremy): remove
void Game::CleanUpObjects() {
	current_scene_->CleanUpObjects();
}

// TODO(@jeremy): remove
void Game::DeleteObject(GameObject* o) {
	current_scene_->DeleteObject(o);
}

}   // namespace midistar
