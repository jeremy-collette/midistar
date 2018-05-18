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

#include "midistar/MidiNoteEvent.h"

namespace midistar {

MidiNoteEvent::MidiNoteEvent() {
}

MidiNoteEvent::MidiNoteEvent(
    int channel
    , double duration
    , int key
    , bool on
    , double time
    , int track
    , int velocity)
        : channel{channel}
        , duration{duration}
        , key{key}
        , on{on}
        , time{time}
        , track{track}
        , velocity{velocity} {
}

}  // End namespace Midistar
