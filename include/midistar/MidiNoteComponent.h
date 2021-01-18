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

#ifndef MIDISTAR_MIDINOTECOMPONENT_H_
#define MIDISTAR_MIDINOTECOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The MidiNoteComponent class holds MIDI note information.
 */
class MidiNoteComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param on True indicates MIDI note on. False indicates MIDI note off.
     * \param chan MIDI channel.
     * \param note MIDI note.
     * \param vel MIDI velocity.
     */
    MidiNoteComponent(bool on, int chan, int note, int vel);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    int chan_;  //!< Holds MIDI channel
    int note_;  //!< Holds MIDI note
    bool on_;  //!< Holds MIDI note on / off status
    int vel_;  //!< Holds MIDI velocity
};

}   // End namespace midistar

#endif  // MIDISTAR_MIDINOTECOMPONENT_H_
