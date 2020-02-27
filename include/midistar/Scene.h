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

#ifndef MIDISTAR_SCENE_H_
#define MIDISTAR_SCENE_H_

#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"

// Forward declaration to prevent circular dependency
class Game;

namespace midistar {

/**
 * The Scene class holds GameObjects for a scene.
 */
class Scene {
 public:
    /**
     * Constructor.
	 *
	 * \param game  The game
	 * \param render_window The game window
	 * \param game_objects The GameObjects of the scene
     */
	 Scene(
		 Game* game
		 , sf::RenderWindow& render_window
		 , std::vector<GameObject*> game_objects);

	 ~Scene();

	 /**
	  * Initializes the Scene.
	  *
	  * \return True indicates success. False indicates failure.
	  */
	 bool Init();

	 /**
	  * Updates the Scene.
	  *
	  * \param delta Time since last game tick.
	  *
	  * \return True indicates success. False indicates failure.
	  */
	 bool Update(int delta);

	 /**
	  * Draws the Scene.
	  *
	  * \return True indicates success. False indicates failure.
	  */
	 bool Draw();

	 void AddNewGameObject(GameObject* new_game_object);

	 void FlushNewObjectQueue();

	 void DeleteObject(GameObject* o);

	 std::vector<GameObject*>& GetGameObjects();

     std::vector<GameObject*> GetGameObjectsByTag(std::string tag);

	 void CleanUpObjects();

 private:
	 Game* game_;
	 std::vector<GameObject*> game_objects_;
	 sf::RenderWindow& render_window_;
	 std::queue<GameObject*> new_game_objects_;

};

}   // End namespace midistar

#endif  // MIDISTAR_SCENE_H_
