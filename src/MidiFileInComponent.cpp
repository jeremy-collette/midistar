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

#include "midistar/MidiFileInComponent.h"

namespace midistar {

MidiFileInComponent::MidiFileInComponent(MidiFileIn* midi_file_in)
		: Component{ Component::MIDI_FILE_IN }
		, midi_file_in_{ *midi_file_in } {
}

bool MidiFileInComponent::GetMessage(MidiMessage* message)
{
	return midi_file_in_.GetMessage(message);
}

void MidiFileInComponent::Update(Game * g, GameObject * o, int delta) {
	midi_file_in_.Tick(delta);
}

}   // End namespace midistar
