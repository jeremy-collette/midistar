/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

#include "midistar/MidiInstrumentGameObjectFactory.h"

#include "midistar/MidiInstrumentIn.h"
#include "midistar/MidiInstrumentInComponent.h"

namespace midistar {

bool MidiInstrumentGameObjectFactory::Create(
        int midi_port
        , GameObject** game_object_out) {
    auto midi_instrument_in = new MidiInstrumentIn{ midi_port };
    if (!midi_instrument_in->Init()) {
        return false;
    }

    auto midi_instrument_in_component = new MidiInstrumentInComponent{
        midi_instrument_in };

    auto rect = new sf::RectangleShape{ { 0, 0 } };
    *game_object_out = new GameObject{ rect, 0, 0, 0, 0 };
    (*game_object_out)->AddTag("MidiInstrument");
    (*game_object_out)->SetComponent(midi_instrument_in_component);

    return true;
}

}  // namespace midistar
