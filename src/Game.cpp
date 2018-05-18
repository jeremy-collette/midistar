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

#include "midistar/Game.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObjectFactory.h"
#include "midistar/Config.h"
#include "midistar/NoteInfoComponent.h"

namespace midistar {

Game::Game()
        : window_{sf::VideoMode(Config::GetInstance().GetScreenWidth()
                 , Config::GetInstance().GetScreenHeight()), "midistar"} {
    window_.setFramerateLimit(Config::GetInstance().GetFramesPerSecond());
    objects_.push_back(GameObjectFactory::CreateInstrumentBar());
    if (!Config::GetInstance().GetAutomaticallyPlay()) {
        for (int note = Config::GetInstance().GetMinimumMidiNote();
                note <= Config::GetInstance().GetMaximumMidiNote(); ++note) {
            objects_.push_back(GameObjectFactory::CreateInstrumentNote(note));
        }
    }
}

Game::~Game() {
    for (auto& o : objects_) {
        delete o;
    }
}

void Game::AddGameObject(GameObject* obj) {
    new_objects_.push(obj);
}

const std::vector<MidiNote>& Game::GetMidiInNotes() {
    return midi_in_buf_;
}

const std::vector<GameObject*>& Game::GetGameObjects() {
    return objects_;
}

const std::vector<sf::Event>& Game::GetSfEvents() {
    return sf_events_;
}

sf::RenderWindow& Game::GetWindow() {
    return window_;
}

int Game::Init() {
    window_.setKeyRepeatEnabled(false);
    midi_port_in_.Init();  // It is okay if this fails (player can be using
                                                        // computer keyboard)
    return midi_file_in_.Init(Config::GetInstance().GetMidiFileName())
        || midi_out_.Init();
}

int Game::Run() {
    unsigned int t = 0;
    while (window_.isOpen()) {
        FlushNewObjectQueue();

        window_.clear();
        unsigned num_objects;
        unsigned i = 0;
        do {
            num_objects = objects_.size();
            while (i < objects_.size()) {
                objects_[i++]->Update(this);
            }
            FlushNewObjectQueue();
        // If we've added new objects during updating, we will update them now.
        // NOTE: This could cause an infinite loop if new objects create new
        // objects.
        } while (num_objects != objects_.size());
        window_.display();

        MidiNote note;
        while (midi_file_in_.GetNote(&note)) {
            std::cout << "duration: " << note.duration << "\n";
            objects_.push_back(GameObjectFactory::CreateSongNote(
                        note.track
                        , note.on
                        , note.channel
                        , note.key
                        , note.velocity));
        }

        midi_in_buf_.clear();
        while (midi_port_in_.GetNote(&note)) {
            midi_in_buf_.push_back(note);
        }

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

        midi_file_in_.Tick();
        midi_port_in_.Tick();
        CleanUpObjects();

        // If we're done playing the file and have no song notes to be played,
        // we're done!
        if (midi_file_in_.IsEof() && !CheckSongNotes()) {
            window_.close();
        }
        ++t;
    }

    return 0;
}

void Game::TurnMidiNoteOff(int chan, int note) {
    midi_out_.SendNoteOff(note, chan);
}

void Game::TurnMidiNoteOn(int chan, int note, int vel) {
    midi_out_.SendNoteOn(note, chan, vel);
}

bool Game::CheckSongNotes() {
    for (const auto& obj : objects_) {
        if (obj->HasComponent(Component::SONG_NOTE_COMPONENT)) {
            // If there's no anchor we know it's a valid note
            if (!obj->HasComponent(Component::ANCHOR_COMPONENT)) {
                return true;
            }

            // We can still have an anchor if we're anchored to the bar
            double x, y;
            obj->GetPosition(&x, &y);
            if (y > 0) {
                return true;
            }

            auto note = obj->GetComponent<NoteInfoComponent>(
                    Component::NOTE_INFO_COMPONENT);
            if (!note) {
                continue;
            }
            std::cerr << "Warning: could not find MIDI note off event for"
                << " key " << note->GetKey() << ". Track: "
                << note->GetTrack() << ". Channel: " << note->GetChannel()
                << ".\n";
        }
    }
    return false;
}

void Game::CleanUpObjects() {
    auto objects_copy {objects_};
    for (auto& o : objects_copy) {
        if (o->GetRequestDelete()) {
            DeleteObject(o);
        }
    }
}

void Game::DeleteObject(GameObject* o) {
    auto itr = std::find(objects_.begin(), objects_.end(), o);
    if (itr != objects_.end()) {
        objects_.erase(itr);
    }
    delete o;
}

void Game::FlushNewObjectQueue() {
    while (!new_objects_.empty()) {
        objects_.push_back(new_objects_.front());
        new_objects_.pop();
    }
}

}   // namespace midistar
