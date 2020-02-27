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
#include "midistar/DrumSceneFactory.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/IntroSceneFactory.h"

// TODO(@jeremy): remove
#include "midistar/PianoGameObjectFactory.h"

namespace midistar {

// TODO(@jeremy): Inject these dependencies
// TODO(@jeremy): Remove old code
Game::Game()
		: current_scene_{ nullptr }
		, current_scene_name_{ "" }
		, next_scene_{ nullptr }
        , scene_factories_{ }
        , window_{sf::VideoMode(Config::GetInstance().GetScreenWidth()
                 , Config::GetInstance().GetScreenHeight())
                 , "midistar"
                 , Config::GetInstance().GetFullScreen() ?
                 sf::Style::Fullscreen : sf::Style::Default} {
    scene_factories_["Intro"] = new IntroSceneFactory{};
    scene_factories_["Piano"] = new PianoSceneFactory{};
    scene_factories_["Drum"] = new DrumSceneFactory{};
}

Game::~Game() {
	if (current_scene_) {
		delete current_scene_;
	}

    for (auto& itr = scene_factories_.begin(); itr != scene_factories_.end();
            ++itr) {
        delete itr->second;
    }
}

void Game::AddGameObject(GameObject* obj) {
	current_scene_->AddNewGameObject(obj);
}

Scene& Game::GetCurrentScene() {
    return *current_scene_;
}

GameObjectFactory& Game::GetGameObjectFactory() {
    return PianoGameObjectFactory{ 20.0 };
}

const std::vector<MidiMessage>& Game::GetMidiInMessages() {
    auto game_objects = current_scene_->GetGameObjectsByTag("MidiInstrument");
    auto midi_instrument_game_object = game_objects[0];
    auto midi_instrument_in_component = midi_instrument_game_object->
        GetComponent<MidiInstrumentInComponent>(Component::MIDI_INSTRUMENT_IN);
    return midi_instrument_in_component->GetMessages();
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

            if (!current_scene_->Init()) {
                throw "Error initializing scene!";
            }
		}

        // Clean up from last tick
		// TODO(@jeremy): move this to scene
        window_.clear(sf::Color::Black);
        int delta = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        // Handle updating
		current_scene_->Update(delta);
		current_scene_->Draw();
        window_.display();

        // Handle MIDI file events
		// TODO(@jeremy): This should be done inside a GameObject
        bool midi_file_is_eof = false;
        auto game_objects = current_scene_->GetGameObjectsByTag("MidiFile");
        if (game_objects.size())
        {
            auto midi_file_game_object = game_objects[0];
            auto midi_file_in_component = midi_file_game_object->
                GetComponent<MidiFileInComponent>(Component::MIDI_FILE_IN);

            midi_file_is_eof = midi_file_in_component->midi_file_in_->IsEof();
        }


        // Handle MIDI port input events
		// TODO(@jeremy): This should be done inside a GameObject
        game_objects = current_scene_->GetGameObjectsByTag("MidiInstrument");
        if (game_objects.size()) {
            auto midi_file_game_object = game_objects[0];
            auto midi_instrument_in_component_ = midi_file_game_object->
                GetComponent<MidiInstrumentInComponent>(
                    Component::MIDI_INSTRUMENT_IN);

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
        if (midi_file_is_eof && !CheckSongNotes()) {
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
    current_scene_name_ = scene_name;
	if (scene_name == "Exit") {
		window_.close();
		return true;
	}

    if (scene_factories_.count(scene_name) == 0) {
        return false;
    }
    return scene_factories_[scene_name]->Create(this, window_, &next_scene_);
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
