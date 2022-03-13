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

#include "midistar/MidiPortIn.h"

#include <unordered_map>
#include <vector>

namespace midistar {

MidiPortIn::MidiPortIn(
    bool extend_same_tick_notes
    , int midi_port)
        : extend_same_tick_notes_{extend_same_tick_notes}
        , midi_port_{ midi_port }
        , midi_in_{nullptr} {
}

MidiPortIn::MidiPortIn(int midi_port)
        : MidiPortIn(true, midi_port) {
}

MidiPortIn::~MidiPortIn() {
    if (midi_in_) {
        delete midi_in_;
    }
}

bool MidiPortIn::Init() {
    midi_in_ = new RtMidiIn();

    try {
        midi_in_->openPort(midi_port_, "midistar Input");
    } catch (...) {
        std::cerr << "Warning: error opening MIDI input port " << midi_port_
            << ". MIDI input disabled.\n";
    }
    midi_in_->ignoreTypes(false, false, false);
    return midi_in_;
}

void MidiPortIn::Tick() {
    if (!midi_in_) {
        return;
    }

    // Here we go handle the cached note on/off events from last tick (see
    // below)
    std::unordered_map<int, MidiMessage> this_tick;
    auto count = same_tick_buffer_.size();

    while (count--) {
        auto midi_message = same_tick_buffer_.front();
        same_tick_buffer_.pop();
        if (this_tick.count(midi_message.GetKey())) {
            same_tick_buffer_.emplace(midi_message);
        } else {
            this_tick[midi_message.GetKey()] = midi_message;
            AddMessage(midi_message);
        }
    }

    std::vector<unsigned char> data;
    while (true) {
        double stamp = midi_in_->getMessage(&data);
        if (data.size() == 0) {
            break;
        }

        // Here we check if we've already had a note event with the same key
        // for this tick. If we have, and the extend_same_tick_notes option
        // is enabled, we cache the note for next tick. This stops a note play
        // from being totally ignored because it happened faster than a tick.
        MidiMessage midi_message{ data, stamp };
        if (extend_same_tick_notes_ && midi_message.IsNote()
                && this_tick.count(midi_message.GetKey())) {
            same_tick_buffer_.emplace(midi_message);
        } else {
            this_tick[midi_message.GetKey()] = midi_message;
            AddMessage(midi_message);
        }
    }
}

}  // End namespace midistar
