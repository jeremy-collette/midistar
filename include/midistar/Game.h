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

#ifndef MIDISTAR_GAME_H_
#define MIDISTAR_GAME_H_

#include <queue>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"
#include "midistar/MidiFileIn.h"
#include "midistar/MidiMessage.h"
#include "midistar/MidiOut.h"
#include "midistar/MidiInstrumentIn.h"
#include "midistar/Scene.h"
#include "midistar/SceneFactory.h"

// TODO(@jeremy): remove
#include "midistar/MidiFileInComponent.h"
#include "midistar/MidiInstrumentInComponent.h"

namespace midistar {

/**
 * The Game class is the class that drives Midistar.
 */
class Game {
 public:
    /**
     * Constructor.
     */
    Game();

    /**
     * Destructor.
     */
    ~Game();

    Scene& GetCurrentScene();

    /**
     * Gets MIDI input port messages for the last tick.
     *
     * \return MIDI messages.
     */
    const std::vector<MidiMessage>& GetMidiInMessages();

    /**
     * Gets the SFML window being used for rendering.
     *
     * \return SFML window.
     */
    sf::RenderWindow& GetWindow();

    /**
     * Initializes the game.
     *
     * \return true for success. false for failure.
     */
    bool Init();

    /**
     * Runs the game.
     */
    void Run();

	bool SetScene(std::string scene_name);

 private:
	Scene* current_scene_;  //!< Current scene
	Scene* next_scene_;  //!< The scene to swap to
    sf::RenderWindow window_;  //!< SFML window instance

    std::unordered_map<std::string, SceneFactory*> scene_factories_;
};

}   // End namespace midistar

#endif  // MIDISTAR_GAME_H_
