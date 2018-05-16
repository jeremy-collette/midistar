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

#ifndef MIDISTAR_MIDIIN_H_
#define MIDISTAR_MIDIIN_H_

#include <midifile/MidiEvent.h>
#include <queue>

namespace midistar {

/**
 * The MidiIn class provides an interface for MIDI stream readers.
 */
class MidiIn {
 public:
    /**
     * Gets the next MIDI event.
     *
     * \param[out] mev Stores the MIDI event.
     *
     * \return True for success. False if an event is not available.
     */
    bool GetEvent(smf::MidiEvent* mev);

    /**
     * Reads the next available MIDI data in the stream.
     */
    virtual void Tick() = 0;

 protected:
    /**
     * Adds a MIDI event to the event queue.
     *
     * \param mev The event to add.
     */
    void AddEvent(smf::MidiEvent mev);

 private:
    std::queue<smf::MidiEvent> buffer_;  //!< MIDI event buffer
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIIN_H_
