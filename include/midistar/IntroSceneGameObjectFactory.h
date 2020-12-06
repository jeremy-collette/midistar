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

#ifndef MIDISTAR_INTROSCENEGAMEOBJECTFACTORY_H_
#define MIDISTAR_INTROSCENEGAMEOBJECTFACTORY_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/Game.h"
#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The IntroSceneGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class IntroSceneGameObjectFactory {
 public:
    /**
    * Constructor
    */
    IntroSceneGameObjectFactory();

    std::vector<GameObject*> CreateGameObjects(sf::RenderWindow* window);

 private:
    enum GameType {
        PIANO,
        DRUM
    };

    GameObject* CreateCopyrightTextGameObject(const sf::Font& font);
    GameObject* CreateNoFilesFoundTextGameObject(
        const sf::Font& font);
    GameObject* CreateScanningTextGameObject(const sf::Font& font);
    GameObject* CreateVersionTextGameObject(const sf::Font& font);
};

}  // End namespace midistar

#endif  // MIDISTAR_INTROSCENEGAMEOBJECTFACTORY_H_
