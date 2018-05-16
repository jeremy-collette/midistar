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

#ifndef MIDISTAR_NOTEINFOCOMPONENT_H_
#define MIDISTAR_NOTEINFOCOMPONENT_H_

#include "midistar/Component.h"

namespace Midistar {

/**
 * The NoteInfoComponent class holds MIDI note information.
 */
class NoteInfoComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param on True indicates MIDI note on. False indicates MIDI note off.
     * \param chan MIDI channel.
     * \param note MIDI note.
     * \param vel MIDI velocity.
     */
    NoteInfoComponent(bool on, int chan, int note, int vel);

    /**
     * Gets MIDI channel.
     *
     * \return MIDI channel.
     */
    int GetChannel();

    /**
     * Gets whether a note is on or off.
     *
     * \return True indicates on. False indicates off.
     */
    bool GetIsOn();

    /**
     * Gets MIDI note.
     *
     * \return MIDI note.
     */
    int GetKey();

    /**
     * Gets MIDI velocity.
     *
     * \return MIDI velocity.
     */
    int GetVelocity();

    /**
     * \copydoc Component::Update()
     */
    void Update(Game* g, GameObject* o);

 private:
    int chan_;  //!< Holds MIDI channel
    int note_;  //!< Holds MIDI note
    bool on_;  //!< Holds MIDI note on / off status
    int vel_;  //!< Holds MIDI velocity
};

}   // End namespace Midistar

#endif  // MIDISTAR_NOTEINFOCOMPONENT_H_
