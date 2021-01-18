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

#ifndef MIDISTAR_SCENE_H_
#define MIDISTAR_SCENE_H_

#include <queue>
#include <string>
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
        , sf::RenderWindow* render_window
        , std::vector<GameObject*> game_objects);

     /**
      * Destructor.
      */
     ~Scene();

     /**
      * Copy constructor (deleted).
      */
     Scene(const Scene& other) = delete;

     /**
      * Move constructor (deleted).
      */
     Scene(const Scene&& other) = delete;

     /**
      * Adds a GameObject to the scene.
      *
      * \param new_game_object The GameObject to add.
      */
     void AddGameObject(GameObject* new_game_object);

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

     /**
      * Removes a GameObject from the scene.
      *
      * \param new_game_object The GameObject to add.
      */
     void RemoveObject(GameObject* o);

     /**
      * Gets the first GameObject that has the specified tag.
      *
      * \param tag The tag to check for.
      *
      * \returns The first GameObject with the specified tag.
      */
     GameObject* GetFirstGameObjectByTag(std::string tag);

     /**
      * Gets all GameObjects in the Scene.
      *
      * \returns All GameObjects in the Scene.
      */
     std::vector<GameObject*>& GetGameObjects();

     /**
      * Gets all GameObjects in the Scene that have a specific tag.
      *
      * \returns All GameObjects in the Scene that have a specific tag.
      */
     std::vector<GameObject*> GetGameObjectsByTag(std::string tag);

 private:
    void CleanUpObjects();
    void FlushNewObjectQueue();

    Game* game_;
    std::vector<GameObject*> game_objects_;
    sf::RenderWindow* render_window_;
    std::queue<GameObject*> new_game_objects_;
};

}   // End namespace midistar

#endif  // MIDISTAR_SCENE_H_
