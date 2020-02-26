/*
 * midistar
 * Copyright (C) 2018-2019 Jeremy Collette.
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

#include "midistar/MidiInstrumentInComponent.h"

namespace midistar {

MidiInstrumentInComponent::MidiInstrumentInComponent(
    MidiInstrumentIn* midi_instrument_in)
        : Component{ Component::MIDI_INSTRUMENT_IN }
        , midi_instrument_in_{ midi_instrument_in } {
}

MidiInstrumentInComponent::~MidiInstrumentInComponent() {
    delete midi_instrument_in_;
}

std::vector<MidiMessage>& MidiInstrumentInComponent::GetMessages()
{
    return message_buffer_;
}

void MidiInstrumentInComponent::Update(Game* g, GameObject* o, int delta)
{
    midi_instrument_in_->Tick();

    message_buffer_.clear();
    MidiMessage message;
    while (midi_instrument_in_->GetMessage(&message)) {
        message_buffer_.push_back(message);
    }
}

}   // End namespace midistar
