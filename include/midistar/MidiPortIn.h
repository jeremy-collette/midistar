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

#ifndef MIDISTAR_MIDIPORTIN_H_
#define MIDISTAR_MIDIPORTIN_H_

#include <rtmidi/RtMidi.h>

#include <queue>

#include "midistar/MidiIn.h"

namespace midistar {

/**
 * The MidiPortIn class provides an interface for reading from a MIDI input
 * port.
 */
class MidiPortIn : public MidiIn {
 public:
    /**
     * Constructor.
     *
     * \param extend_same_tick_notes Determines whether or not notes that start
     * and finish in the same tick should be extended to finish in the next
     * tick.
     * \param midi_port The index/ID of the MIDI port to connect to, as
     * identified by the operating system.
     */
    MidiPortIn(
        bool extend_same_tick_notes
        , int midi_port);

    /**
     * Constructor.
     *
     * \param midi_port The index/ID of the MIDI port to connect to, as
     * identified by the operating system.
     */
    explicit MidiPortIn(
        int midi_port);

    ~MidiPortIn();

    /**
     * Initialises class.
     *
     * \return true for success. false indicates failure.
     */
    bool Init();

    /**
     * Checks the MIDI port for events and reads them.
     */
    void Tick();

 private:
     bool extend_same_tick_notes_;  //!< Extends notes that start / finish in
                                                              //!< the same tick
     RtMidiIn* midi_in_;  //!< MIDI port instance
     int midi_port_;  //!< MIDI port ID to connect to
     std::queue<MidiMessage> same_tick_buffer_;  //!< Holds note end events that
                           //!< occured in the same tick as the note start
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIPORTIN_H_
