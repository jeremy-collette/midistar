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

#include "midistar/MidiFileIn.h"

#include <iostream>

#include "midistar/Config.h"

namespace midistar {

MidiFileIn::MidiFileIn()
        : index_{0}
        , player_channel_{Config::GetInstance().GetMidiChannel()}
        , player_track_{Config::GetInstance().GetMidiTrack()}
        , time_{0} {
}

MidiFileIn::~MidiFileIn() {
}

int MidiFileIn::Init(const std::string& file_name) {
    file_.read(file_name);
    bool success = file_.status();
    file_.joinTracks();
    file_.linkNotePairs();
    if (!success) {
        std::cerr << "Error! Could not load MIDI file \"" << file_name << "\""
        << ".\n";
    }
    return !success;
}

bool MidiFileIn::IsEof() {
    return index_ >= file_[0].size();
}

void MidiFileIn::Tick() {
    smf::MidiEvent* mev;
    while (!IsEof() && file_.getTimeInSeconds((mev = &file_[0][index_])->tick)
                <= time_) {
        if ((player_channel_ == -1 || mev->getChannel() == player_channel_)
            && (player_track_ == -1 || mev->track == player_track_)
            && (mev->isNoteOn() || mev->isNoteOff())) {
            MidiMessage msg( 
                *mev
                , mev->getDurationInSeconds()
                , mev->tick
                , mev->track );            
            AddMessage(msg);
        }
        ++index_;
    }
    time_ += 1.0 / Config::GetInstance().GetFramesPerSecond();

    // If MIDI file repeat is enabled, reset index when we encounter EOF
    if (IsEof() && Config::GetInstance().GetMidiFileRepeat()) {
        index_ = 0;
        time_ = 0;
    }
}

}  // End namespace midistar
