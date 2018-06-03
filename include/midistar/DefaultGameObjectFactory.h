/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
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

#ifndef MIDISTAR_DEFAULTGAMEOBJECTFACTORY_H_
#define MIDISTAR_DEFAULTGAMEOBJECTFACTORY_H_

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The DefaultGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class DefaultGameObjectFactory : public GameObjectFactory {
 public:
   /**
    * Constructor
    */
    explicit DefaultGameObjectFactory(double note_speed);

    /**
     * Creates the instrument bar.
     *
     * \return A GameObject which is the instrument bar.
     */
    virtual GameObject* CreateInstrumentBar();

    /**
     * Creates a MIDI instrument note.
     *
     * \param note The MIDI note of the instrument.
     *
     * \return A GameObject which is an instrument.
     */
    virtual GameObject* CreateInstrumentNote(int note);

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
            , double duration);

 private:
    double note_width_;  //!< Holds the width of song notes
};

}  // End namespace midistar

#endif  // MIDISTAR_DEFAULTGAMEOBJECTFACTORY_H_
