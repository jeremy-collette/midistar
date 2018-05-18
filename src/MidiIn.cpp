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

#include "midistar/MidiIn.h"

namespace midistar {

bool MidiIn::GetNote(MidiNoteEvent* note) {
    if (buffer_.empty()) {
        return false;
    }

    *note = buffer_.front();
    buffer_.pop();
    return true;
}

void MidiIn::AddNote(MidiNoteEvent note) {
    buffer_.push(note);
}

}  // End namespace midistar
