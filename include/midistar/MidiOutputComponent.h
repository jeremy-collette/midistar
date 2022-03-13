/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
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

#ifndef MIDISTAR_MIDIOUTPUTCOMPONENT_H_
#define MIDISTAR_MIDIOUTPUTCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

#include "midistar/MidiOut.h"

namespace midistar {

class MidiOutputComponent : public Component {
 public:
     explicit MidiOutputComponent(MidiOut* midi_out);

     ~MidiOutputComponent();

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

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    MidiOut* midi_out_;
};

}   // End namespace midistar

#endif  // MIDISTAR_MIDIOUTPUTCOMPONENT_H_
