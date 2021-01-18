/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#include "midistar/MidiFileInComponent.h"

namespace midistar {

MidiFileInComponent::MidiFileInComponent(MidiFileIn* midi_file_in)
    : Component{ Component::MIDI_FILE_IN }
        , midi_file_in_{ midi_file_in } {
}

MidiFileInComponent::~MidiFileInComponent() {
    delete midi_file_in_;
}

double MidiFileInComponent::GetMaximumNoteDuration() const {
    return midi_file_in_->GetMaximumNoteDuration();
}

const std::vector<MidiMessage>& MidiFileInComponent::GetMessages() const {
    return message_buffer_;
}

int MidiFileInComponent::GetTicksPerQuarterNote() const {
    return midi_file_in_->GetTicksPerQuarterNote();
}

std::vector<int> MidiFileInComponent::GetUniqueMidiNotes() const {
    return midi_file_in_->GetUniqueMidiNotes();
}

bool MidiFileInComponent::IsEof() const {
    return midi_file_in_->IsEof();
}

void MidiFileInComponent::Update(Game*, GameObject*, int delta) {
    midi_file_in_->Tick(delta);

    message_buffer_.clear();
    MidiMessage message;
    while (midi_file_in_->GetMessage(&message)) {
        message_buffer_.push_back(message);
    }
}

}   // End namespace midistar
