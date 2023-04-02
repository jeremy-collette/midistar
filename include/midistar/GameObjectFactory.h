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

#ifndef MIDISTAR_GAMEOBJECTFACTORY_H_
#define MIDISTAR_GAMEOBJECTFACTORY_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "midistar/GameObject.h"

namespace midistar {

/**
 * The GameObjectFactory class provides an interface to create GameObject
 * instances. Deriving classes specify the 'look and feel' and behaviour of
 * GameObjects, allowing for different game themes and/or modes.
 */
class GameObjectFactory {
 public:
    /**
     * Constructor.
     */
    explicit GameObjectFactory(
            double note_speed
            , const sf::Color& backround_colour);

    /**
     * Destructor.
     */
    virtual ~GameObjectFactory() = default;

    /**
     * Creates a grinding effect to indicate a note is being played.
     *
     * \param o The GameObject to use to create the effect.
     *
     * \return A GameObject that represents a note play effect.
     */
    virtual GameObject* CreateNotePlayEffect(GameObject* o) = 0;

    /**
     * Creates the instrument to play.
     *
     * \return A collection of GameObjects representing an instrument.
     */
    virtual std::vector<GameObject*> CreateInstrument() = 0;

    /**
     * Creates a MIDI song note.
     *
     * \param track The MIDI track of the note.
     * \param chan MIDI channel.
     * \param note MIDI note.
     * \param vel MIDI velocity.
     * \param duration The duration of the note.
     *
     * \return A GameObject which is a song note.
     */
    virtual GameObject* CreateSongNote(
            int track
            , int chan
            , int note
            , int vel
            , double duration) = 0;

    /**
     * Gets the recommended background colour for the GameObjectFactory.
     *
     * \return Background colour.
     */
    const sf::Color& GetBackgroundColour();

    /**
     * Initialises the GameObjectFactory.
     *
     * \return true indicates success. false indicates failure.
     */
    virtual bool Init() = 0;

 protected:
    double GetNoteSpeed();  //!< Gets note speed

 private:
    const sf::Color background_colour_;  //!< Holds background colour
    double note_speed_;  //!< Holds note speed
};

}  // End namespace midistar

#endif  // MIDISTAR_GAMEOBJECTFACTORY_H_
