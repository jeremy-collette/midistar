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

#ifndef MIDISTAR_MIDIPORTIN_H_
#define MIDISTAR_MIDIPORTIN_H_

#include <rtmidi/RtMidi.h>

#include "midistar/MidiIn.h"

namespace Midistar {

/**
 * The MidiPortIn class provides an interface for reading from a MIDI in port.
 */
class MidiPortIn : public MidiIn {
 public:
    /*
     * Constructor.
     */
    MidiPortIn();

    /**
     * Initialises the instance.
     *
     * \return 0 for success. Non-zero indicates failure.
     */
    int Init();

    /**
     * Checks the MIDI port for events and reads them.
     */
    virtual void Tick();

 private:
    RtMidiIn* midi_in_;  //!< MIDI port instance
};

}  // End namespace Midistar

#endif  // MIDISTAR_MIDIPORTIN_H_
