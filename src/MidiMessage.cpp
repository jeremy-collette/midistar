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

#include "midistar/MidiMessage.h"

namespace midistar {

MidiMessage::MidiMessage() {
}

MidiMessage::MidiMessage(
    std::vector<unsigned char> data
    , double duration
    , double time
    , int track)
        : data_{data}, duration_{duration}, time_{time}, track_{track} {
}

MidiMessage::MidiMessage(
    std::vector<unsigned char> data
    , double time
    , int track)
        : MidiMessage{data, -1.0, time, track} {
}

MidiMessage::MidiMessage(
    std::vector<unsigned char> data
    , double time)
        : MidiMessage{data, time, -1} {
} 


MidiMessage::MidiMessage(std::vector<unsigned char> data)
        : MidiMessage{data, -1.0} {
}

int MidiMessage::GetChannel() const {
    if (!data_.size()) {
        return -1;
    }
    return data_[0] & CHANNEL_MASK;
}

const std::vector<unsigned char>& MidiMessage::GetData() const {
    return data_;
}

double MidiMessage::GetDuration() const {
    return duration_;
}

int MidiMessage::GetKey() const {
    if (!IsNote()) {
        return -1;
    }
    return data_[1];
}

int MidiMessage::GetTrack() const {
    return track_;
}

int MidiMessage::GetVelocity() const {
    if (!IsNote()) {
        return -1;
    }
    return data_[2];
}

bool MidiMessage::IsNote() const {
    return IsNoteOn() || IsNoteOff();
}

bool MidiMessage::IsNoteOff() const {
    if (!data_.size()) {
        return false;
    }
    return ((data_[0] & COMMAND_MASK) == NOTE_OFF_COMMAND)
       || (IsNoteOn() && GetVelocity() == 0); 
}

bool MidiMessage::IsNoteOn() const {
    if (!data_.size()) {
        return false;
    }
    return (data_[0] & COMMAND_MASK) == NOTE_ON_COMMAND;
}

}  // End namespace Midistar
