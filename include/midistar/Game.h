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

    /**
     * Adds a new object to the game.
     *
     * \param obj The object to add.
     */
    void AddGameObject(GameObject* obj);

    Scene& GetCurrentScene();

    /**
     * Gets the GameObjectFactory instance in use.
     *
     * \return GameObjectFactory instance.
     */
    GameObjectFactory& GetGameObjectFactory();

    /**
     * Gets all GameObjects.
     *
     * \return All GameObjects.
     */
    const std::vector<GameObject*>& GetGameObjects();

    /**
     * Gets MIDI input port messages for the last tick.
     *
     * \return MIDI messages.
     */
    const std::vector<MidiMessage>& GetMidiInMessages();

    /**
     * Gets SFML events for the last tick.
     *
     * \return SFML events.
     */
    const std::vector<sf::Event>& GetSfEvents();

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

    /**
     * Turns off a MIDI note on the MIDI out port.
     *
     * \param chan MIDI channel.
     * \param note MIDI note.
     */
    void TurnMidiNoteOff(int chan, int note);

    /**
     * Turns on a MIDI note on the MIDI out port.
     *
     * \param chan MIDI channel.
     * \param note MIDI note.
     * \param vel MIDI velocity.
     */
    void TurnMidiNoteOn(int chan, int note, int vel);

	bool SetScene(std::string scene_name);

 private:
    bool CheckSongNotes();  //!< Determines if the Game has valid song notes
    void CleanUpObjects();  //!< Deletes all GameObjects and their components
    void DeleteObject(GameObject* o);  //!< Deletes a GameObject

	Scene* current_scene_;  //!< Current scene
	std::string current_scene_name_;  //!< Current scene name
    MidiOut midi_out_;  //!< MIDI port out instance
	Scene* next_scene_;  //!< The scene to swap to
    std::vector<sf::Event> sf_events_;  //!< SFML events buffer
    sf::RenderWindow window_;  //!< SFML window instance

    std::unordered_map<std::string, SceneFactory*> scene_factories_;
};

}   // End namespace midistar

#endif  // MIDISTAR_GAME_H_
