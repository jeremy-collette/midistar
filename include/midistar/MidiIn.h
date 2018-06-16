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

#include <queue>

#include "midistar/MidiMessage.h"

namespace midistar {

/**
 * The MidiIn class provides an interface for MIDI stream readers.
 */
class MidiIn {
 public:
    /**
     * Gets the next MIDI message.
     *
     * \param[out] message Stores the MIDI message.
     *
     * \return True for success. False if an event is not available.
     */
    bool GetMessage(MidiMessage* message);

 protected:
    /**
     * Adds a MIDI message to the message queue.
     *
     * \param message The message to add.
     */
    void AddMessage(MidiMessage message);

 private:
    std::queue<MidiMessage> buffer_;  //!< MIDI message buffer
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIIN_H_
