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

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/Config.h"
#include "midistar/DefaultGameObjectFactory.h"
#include "midistar/DrumGameObjectFactory.h"
#include "midistar/PianoGameObjectFactory.h"
#include "midistar/IntroSceneGameObjectFactory.h"
#include "midistar/NoteInfoComponent.h"

namespace midistar {

// TODO(@jeremy): Inject these dependencies
// TODO(@jeremy): Remove old code
Game::Game()
		: current_scene_{ nullptr }
		, object_factory_{ nullptr }
		, scene_changed_{ false }
        , window_{sf::VideoMode(Config::GetInstance().GetScreenWidth()
                 , Config::GetInstance().GetScreenHeight())
                 , "midistar"
                 , Config::GetInstance().GetFullScreen() ?
                 sf::Style::Fullscreen : sf::Style::Default} {
}

Game::~Game() {
#ifndef SCENE_TEST
    for (auto& o : objects_) {
        delete o;
    }
#endif
    if (object_factory_) {
        delete object_factory_;
    }
}

void Game::AddGameObject(GameObject* obj) {
#ifdef SCENE_TEST
	current_scene_->AddNewGameObject(obj);
#else
	new_objects_.push(obj);
#endif
}

GameObjectFactory& Game::GetGameObjectFactory() {
    return *object_factory_;
}

const std::vector<MidiMessage>& Game::GetMidiInMessages() {
    return midi_in_buf_;
}

const std::vector<GameObject*>& Game::GetGameObjects() {
#ifdef SCENE_TEST
	return current_scene_->GetGameObjects();
#else
    return objects_;
#endif
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

    // Setup MIDI input / outputs
    midi_instrument_in_.Init();  // It is okay if this fails (player can be
                                                    // using computer keyboard)
    if (!midi_file_in_.Init(Config::GetInstance().GetMidiFileName())) {
        return false;
    }
    if (!midi_out_.Init()) {
        return false;
    }

    // Setup GameObject factory and create GameObjects
    double note_speed = (midi_file_in_.GetTicksPerQuarterNote() /
        Config::GetInstance().GetMidiFileTicksPerUnitOfSpeed()) *
        Config::GetInstance().GetFallSpeedMultiplier();

    auto mode = Config::GetInstance().GetGameMode();
    auto unique_notes = midi_file_in_.GetUniqueMidiNotes();

#ifdef DEBUG
    std::cout << "MIDI file unique notes: \n";
    for (const auto& n : unique_notes) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
#endif

    if (mode == "drum") {
        auto max_note_duration = midi_file_in_.GetMaximumNoteDuration();
        object_factory_ = new DrumGameObjectFactory(note_speed, unique_notes
            , max_note_duration);
    } else if (mode == "piano") {
        object_factory_ = new PianoGameObjectFactory(note_speed);
    } else {
        object_factory_ = new DefaultGameObjectFactory(note_speed);
    }

    if (!object_factory_->Init()) {
        return false;
    }

    auto instrument = object_factory_->CreateInstrument();
    objects_.insert(objects_.end(), instrument.begin(), instrument.end());

#ifdef SCENE_TEST
	auto intro_scene_object_factory = new IntroSceneGameObjectFactory{};
	auto game_objects = intro_scene_object_factory->CreateGameObjects();
	current_scene_ = new Scene{ this, window_, game_objects };

	//if (scene_factory_manager_.TryCreateScene("TestScene", current_scene_)
	//	== false)
	//{
	//	std::cerr << "Error creating scene \"TestScene\"!" << std::endl;
	//	return false;
	//}

	if (!current_scene_->Init())
	{
		std::cerr << "Error initializing scene!" << std::endl;
		return false;
	}
#endif

	return true;
}

void Game::Run() {
    unsigned int t = 0;
    sf::Clock clock;
    while (window_.isOpen()) {
        // Clean up from last tick
#ifndef SCENE_TEST
        FlushNewObjectQueue();
#endif
        window_.clear(object_factory_->GetBackgroundColour());
        int delta = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        // Handle updating

#ifdef SCENE_TEST
		current_scene_->Update(delta);
		current_scene_->Draw();
#else
        unsigned num_objects;
        unsigned i = 0;
        do {
            num_objects = objects_.size();
            while (i < objects_.size()) {
                objects_[i++]->Update(this, delta);
            }
            FlushNewObjectQueue();
        // If we've added new objects during updating, we will update them now.
        // NOTE: This could cause an infinite loop if new objects create new
        // objects.
        } while (num_objects != objects_.size());

        // Handle drawing
        for (auto obj : objects_) {
            obj->Draw(&window_);
        }
#endif
        window_.display();

        // Handle MIDI file events
#ifdef SCENE_TEST
        MidiMessage msg;
        while (midi_file_in_.GetMessage(&msg)) {
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
#else
		MidiMessage msg;
		while (midi_file_in_.GetMessage(&msg)) {
			if (msg.IsNoteOn()) {
				objects_.push_back(object_factory_->
					CreateSongNote(
						msg.GetTrack()
						, msg.GetChannel()
						, msg.GetKey()
						, msg.GetVelocity()
						, msg.GetDuration()));
			}
		}
#endif

        // Handle MIDI port input events
        midi_in_buf_.clear();
        while (midi_instrument_in_.GetMessage(&msg)) {
#ifdef DEBUG
            if (msg.IsNoteOn()) {
                std::cout << "Played: " << msg.GetKey() << '\n';
            }
#endif

            midi_in_buf_.push_back(msg);
        }

        // Handle SFML events
        sf_events_.clear();
        sf::Event event;
        while (window_.pollEvent(event)) {
            sf_events_.push_back(event);
            if (event.type == sf::Event::Closed
                || (event.type == sf::Event::KeyPressed &&
                        event.key.code == sf::Keyboard::Escape)) {
                window_.close();
            }
        }

        // Update MIDI file and port
#ifdef SCENE_TEST
		if (scene_changed_) {
#endif
		midi_file_in_.Tick(delta);
		midi_instrument_in_.Tick();
#ifdef SCENE_TEST
		}
#endif

        // Clean up!
		// TODO(@jeremy): move this inside scene
        CleanUpObjects();

        // If we're done playing the file and have no song notes to be played,
        // we're done!
        if (midi_file_in_.IsEof() && !CheckSongNotes()) {
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
	// TODO(@jeremy): Use Scene name

	// TODO(@jeremy): clean-up old Scene
	current_scene_ = new Scene{ this, window_, objects_ };

	if (!current_scene_->Init())
	{
		std::cerr << "Error initializing scene!" << std::endl;
		return false;
	}

	scene_changed_ = true;
	return true;
}

bool Game::CheckSongNotes() {
#ifdef SCENE_TEST
	for (const auto& obj : current_scene_->GetGameObjects()) {
		if (obj->HasComponent(Component::SONG_NOTE)) {
			return true;
		}
}
	return false;
#else
    for (const auto& obj : objects_) {
        if (obj->HasComponent(Component::SONG_NOTE)) {
            return true;
        }
    }
	return false;
#endif
}

void Game::CleanUpObjects() {
#ifdef SCENE_TEST
	current_scene_->CleanUpObjects();
#else
    auto objects_copy {objects_};
	for (auto& o : objects_copy) {
		if (o->GetRequestDelete()) {
			DeleteObject(o);
		}
	}
#endif
}

void Game::DeleteObject(GameObject* o) {
#ifdef SCENE_TEST
	current_scene_->DeleteObject(o);
#else
    auto itr = std::find(objects_.begin(), objects_.end(), o);
    if (itr != objects_.end()) {
        objects_.erase(itr);
    }
    delete o;
#endif
}

#ifndef SCENE_TEST
void Game::FlushNewObjectQueue() {
    while (!new_objects_.empty()) {
        objects_.push_back(new_objects_.front());
        new_objects_.pop();
    }
}
#endif

}   // namespace midistar
