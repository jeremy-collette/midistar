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

#ifndef MIDISTAR_MIDINOTE_H_
#define MIDISTAR_MIDINOTE_H_

namespace midistar {

/**
 * The MidiNoteEvent class represents MIDI note on / off events.
 */
struct MidiNoteEvent {
    /**
     * Constructor.
     */
    MidiNoteEvent();


    /**
     * Constructor. 
     *
     * \param channel The MIDI channel of the event.
     * \param duration The duration of the note (if it is a MIDI note on event).
     * \param key The MIDI key of the event.
     * \param on Determines if it is a note on or off event.
     * \param time Timestamp of the event.
     * \param track The MIDI track of the event.
     * \param velocity The MIDI velocity (if it is a MIDI note on event).
     */
    MidiNoteEvent(
            int channel
            , double duration
            , int key
            , bool on
            , double time
            , int track
            , int velocity);

    int channel;  //!< MIDI channel
    double duration;  //!< Duration of the note
    int key;  //!< MIDI key
    bool on;  //!< Determines if this is a MIDI note on or off event
    double time;  //!< Event timestamp
    int track;  //!< Event track
    int velocity;  //!< Note velocity
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDINOTE_H_
