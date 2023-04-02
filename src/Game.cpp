/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

namespace midistar {

Game::Game()
        : current_scene_{ nullptr }
        , next_scene_{ nullptr }
        , window_{sf::VideoMode(Config::GetInstance().GetScreenWidth()
                 , Config::GetInstance().GetScreenHeight())
                 , "midistar"
                 , Config::GetInstance().GetFullScreen() ?
                 sf::Style::Fullscreen : sf::Style::Default} {
}

Game::~Game() {
    if (current_scene_) {
        delete current_scene_;
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

    // Set SFML window icon
    sf::Image icon;
    auto icon_path = Config::GetInstance().GetIconPath();
    if (!icon.loadFromFile(icon_path)) {
        std::cout << "Warning: could not load icon from \"" << icon_path
            << "\"\n";
    } else {
        window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // If the song has finished, set scene to intro
    auto intro_scene_factory = IntroSceneFactory{};
    auto next_scene = new Scene{
        this,
        &GetWindow(),
        std::vector<GameObject*>{ }
    };

    auto background_music = true;
    if (!intro_scene_factory.Create(
        this
        , &GetWindow()
        , &next_scene
        , background_music)) {
        return false;
    }

    SetScene(next_scene);
    return true;
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
        window_.clear(sf::Color::Black);
        int delta = t == 0 ? 0 : clock.getElapsedTime().asMilliseconds();
        clock.restart();

        // Ignore massive deltas (to prevent music skipping etc). We see massive
        // deltas after main thread has been blocked.
        // (e.g. window was dragged or disk IO).
        auto frame_max_delta = Config::GetInstance().GetFrameMaxDelta();
        if (frame_max_delta != -1
                && delta >= frame_max_delta) {
            std::cout << "Warning: ignoring frame delta: " << delta << "\n";
            delta = 0;
        }

        // Handle updating
        current_scene_->Update(delta);
        current_scene_->Draw();
        window_.display();
        ++t;
    }
}

void Game::SetScene(Scene* next_scene) {
    next_scene_ = next_scene;
}

void Game::Exit() {
    window_.close();
}

}   // namespace midistar
