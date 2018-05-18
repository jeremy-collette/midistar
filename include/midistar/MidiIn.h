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

#include "midistar/MidiNoteEvent.h"

namespace midistar {

/**
 * The MidiIn class provides an interface for MIDI stream readers.
 */
class MidiIn {
 public:
    /**
     * Gets the next MIDI note.
     *
     * \param[out] mev Stores the MIDI note.
     *
     * \return True for success. False if an event is not available.
     */
    bool GetNote(MidiNoteEvent* note);

    /**
     * Reads the next available MIDI data in the stream.
     */
    virtual void Tick() = 0;

 protected:
    /**
     * Adds a MIDI note to the note queue.
     *
     * \param note The note to add.
     */
    void AddNote(MidiNoteEvent note);

 private:
    std::queue<MidiNoteEvent> buffer_;  //!< MIDI note buffer
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIIN_H_
