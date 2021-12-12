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

#ifndef MIDISTAR_COMPONENT_H_
#define MIDISTAR_COMPONENT_H_

namespace midistar {
class Game;
class GameObject;

/**
 * The ComponentType typedef is used in an enum to uniquely identify each
 * component slot.
 */
typedef int ComponentType;

/**
 * The Component class is the building block for GameObjects. Each GameObject
 * is made up of a collection of Components, that dictate its behaviour and
 * functionality.
 *
 * The Component class is an abstract base class, where deriving classes
 * implement component behvaiour.
 */
class Component {
 public:
    /**
     * Defines the different components derived from the Component base class.
     */
    enum : ComponentType {
        SONG_NOTE = 0
        , INSTRUMENT
        , BAR
        , COLLIDABLE
        , NOTE_INFO
        , INSTRUMENT_INPUT_HANDLER
        , INSTRUMENT_AUTO_PLAY
        , TRANSFORMATION
        , INVERT_COLOUR
        , MIDI_NOTE
        , PHYSICS
        , DELETE_OFFSCREEN
        , VERTICAL_COLLISION_DETECTOR
        , PIANO_NOTE_COLLISION_HANDLER
        , DRUM_NOTE_COLLISION_HANDLER
        , SHRINK_GROW
        , RESIZE
        , SPRITE_ANIMATOR
        , FADING_OUTLINE_EFFECT
        , DELAYED_COMPONENT
        , MENU
        , MENU_ITEM
        , MENU_INPUT_HANDLER
        , MIDI_FILE_IN
        , MIDI_INSTRUMENT_IN
        , SONG_NOTE_CREATOR
        , SFML_EVENTS
        , SFML_EVENTS_HANDLER
        , MIDI_OUTPUT
        , SONG_END_WATCHER
        , KEEP_ALIVE
        , BACKGROUND_SONG_PLAYER
        , SCORE
        , SCORE_MANAGER
        , PHANTOM_NOTE
        , INSTRUMENT_PRACTICE_MODE
        , SONG_NOTE_PRACTICE_MODE
        , PRACTICE_MODE_PLAYED
        , NUM_COMPONENTS
    };

    /**
     * Constructor.
     *
     * \param type The ComponentType of the dervied class.
     */
    explicit Component(ComponentType type);

    /**
     * Destructor.
     */
    virtual ~Component();

    /**
     * Gets the ComponentType of the derived class.
     *
     * \return The ComponentType of the derived class.
     */
    ComponentType GetType();

    /**
     * Updates the Component.
     *
     * \param[in,out] g The Game object in use.
     * \param[in,out] o The GameObject that owns the component.
     * \param delta Time since last game tick.
     */
    virtual void Update(Game* g, GameObject* o, int delta) = 0;

 private:
    ComponentType type_;  //!< Holds the type of the component.
};

}   // End namespace midistar

#endif  // MIDISTAR_COMPONENT_H_
