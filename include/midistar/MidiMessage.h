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

#ifndef MIDISTAR_MIDIMESSAGE_H_
#define MIDISTAR_MIDIMESSAGE_H_

#include <vector>

namespace midistar {

/**
 * The MidiMessage class represents MIDI messages.
 */
class MidiMessage {
 public:
    /**
     * Constructor. Leaves object in an empty state.
     */
    MidiMessage();

    /**
     * Constructor for MIDI messages from a MIDI file that represent a MIDI note-
     * on command and have an associated duration.
     *
     * \param data The underlying MIDI message data.
     * \param duration The duration of the note.
     * \param time Timestamp of the message.
     * \param track The MIDI track of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double duration
            , double time
            , int track);

    /**
     * Constructor for MIDI messages from a MIDI file.
     *
     * \param data The underlying MIDI message data.
     * \param time Timestamp of the message.
     * \param track The MIDI track of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double time
            , int track);

    /**
     * Constructor for MIDI messages from a MIDI stream.
     *
     * \param data The underlying MIDI message data.
     * \param time Timestamp of the message.
     */
    MidiMessage(
            std::vector<unsigned char> data
            , double time);

    /**
     * Constructor for general MIDI messages.
     *
     * \param data The underlying MIDI message data.
     */
    explicit MidiMessage(std::vector<unsigned char> data);

    int GetChannel() const;
    const std::vector<unsigned char>& GetData() const;
    double GetDuration() const;
    int GetKey() const;
    int GetTrack() const;
    int GetVelocity() const;

    bool IsNote() const;
    bool IsNoteOff() const;
    bool IsNoteOn() const;

 private:
    static const unsigned char CHANNEL_MASK = 0x0f;  //!< Mask for channel
    static const unsigned char COMMAND_MASK = 0xf0;  //!< Mask for command
    static const unsigned char NOTE_OFF_COMMAND = 0x80;  //!< MIDI note off
    static const unsigned char NOTE_ON_COMMAND = 0x90;  //!< MIDI note on

    std::vector<unsigned char> data_;  //!< MIDI data
    double duration_;  //!< Holds duration for MIDI note on messages
    double time_;  //!< Message timestamp for messages from MIDI file
    int track_;  //!< Message track for messages from MIDI file
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIMESSAGE_H_
