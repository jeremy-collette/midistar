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

#ifndef MIDISTAR_SCENEFACTORYMANAGER_H_
#define MIDISTAR_SCENEFACTORYMANAGER_H_

#include <string>
#include <vector>

#include "midistar/Scene.h"
#include "midistar/SceneFactory.h"

namespace midistar {

/**
 * The SceneFactoryManager class creates Scenes using SceneFactory instances.
 */
class SceneFactoryManager {
 public:
    /**
     * Constructor.
     *
	 * \param window The game window.
     * \param scene_factories Scene factories to create scenes.
     */
	 SceneFactoryManager(sf::Window& window, std::vector<SceneFactory> scene_factories);

    /**
     * Creates a new Scene.
	 *
	 * \param scene_factory_name The name of the SceneFactoy to use.
	 * \param output_scene[out] Holds the created Scene.
     *
     * \return True if the Scene was successfully created. False otherwise.
     */
    bool TryCreateScene(std::string scene_factory_name, Scene* output_scene)
		const;

 private:
	std::vector<SceneFactory&> scene_factories;  //!< Holds scene factories
};

}   // End namespace midistar

#endif  // MIDISTAR_SCENEFACTORYMANAGER_H_
