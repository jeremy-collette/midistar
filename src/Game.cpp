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
#include <SFML/Graphics.hpp>
#include <vector>

#include "midistar/Config.h"
#include "midistar/DrumSceneFactory.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/IntroSceneFactory.h"

// TODO(@jeremy): remove
#include "midistar/TestSceneFactory.h"

namespace midistar {

Game::Game()
		: current_scene_{ nullptr }
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
    scene_factories_["Test"] = new TestSceneFactory{};
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

Scene& Game::GetCurrentScene() {
    return *current_scene_;
}

sf::RenderWindow& Game::GetWindow() {
    return window_;
}

bool Game::Init() {
    // Setup SFML window
    window_.setFramerateLimit(Config::GetInstance().
            GetMaximumFramesPerSecond());
    window_.setKeyRepeatEnabled(false);

    // TODO(@jeremy): remove
    return SetScene("Test");

	//return SetScene("Intro");
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
        ++t;
    }
}

bool Game::SetScene(std::string scene_name) {
    if (scene_factories_.count(scene_name) == 0) {
        return false;
    }
    return scene_factories_[scene_name]->Create(this, window_, &next_scene_);
}

void Game::SetScene(Scene * next_scene) {
    next_scene_ = next_scene;
}

}   // namespace midistar
