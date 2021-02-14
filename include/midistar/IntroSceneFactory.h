/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#ifndef MIDISTAR_INTROSCENEFACTORY_H_
#define MIDISTAR_INTROSCENEFACTORY_H_

#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"
#include "midistar/Scene.h"

namespace midistar {

class IntroSceneFactory {
 public:
    bool Create(
        Game* game
        , sf::RenderWindow* render_window
        , Scene** scene
        , bool background_music = false);

 private:
     static constexpr const char* DRUM_MIDI_DIR = "songs/drums";
     static constexpr const char* PIANO_MIDI_DIR = "songs/piano";

     enum GameType {
         PIANO,
         DRUM
     };

     bool CreateBackgroundMusicPlayer(GameObject** game_object_out);
     GameObject* CreateCopyrightTextGameObject(const sf::Font& font);
     std::vector<GameObject*> CreateGameObjects(sf::RenderWindow* window
        , bool background_music);
     GameObject* CreateNoFilesFoundTextGameObject(
         const sf::Font& font);
     GameObject* CreateScanningTextGameObject(
         const sf::Font& font
        , std::string directory);
     GameObject* CreateVersionTextGameObject(const sf::Font& font);
};

}   // End namespace midistar

#endif  // MIDISTAR_INTROSCENEFACTORY_H_
