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

#ifndef MIDISTAR_MIDIFILEIN_H_
#define MIDISTAR_MIDIFILEIN_H_

#include <midifile/MidiFile.h>
#include <string>

#include "midistar/MidiIn.h"

namespace Midistar {

/**
 * The MidiFileIn reads events from a MIDI file in a real-time fashion.
 */
class MidiFileIn : public MidiIn {
 public:
    /**
     * Constructor.
     */
    MidiFileIn();

    /**
     * Destructor.
     */
    ~MidiFileIn();

    /**
     * Initialises the class.
     *
     * \param file_name MIDI file to open.
     *
     * \return 0 for success. Non-zero indicates failure.
     */
    int Init(const std::string& file_name);

    /**
     * Determines whether or not the reader is at the end of the MIDI file. 
     *
     * \return True if the reader is at EOF. False otherwise.
     */
    bool IsEof();

    /**
     * Advances the reader at the speed equivalent to one tick of midistar.
     */
    virtual void Tick();

 private:
    smf::MidiFile file_;  //!< Underlying MIDI file instance
    int index_;  //!< Index of event in track
    double time_;  //!< Real-time position in MIDI file
};

}  // End namespace Midistar

#endif  // MIDISTAR_MIDIFILEIN_H_
