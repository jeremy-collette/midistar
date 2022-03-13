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

#ifndef MIDISTAR_MIDIINSTRUMENTGAMEOBJECTFACTORY_H_
#define MIDISTAR_MIDIINSTRUMENTGAMEOBJECTFACTORY_H_

#include "midistar/GameObject.h"

namespace midistar {

class MidiInstrumentGameObjectFactory {
 public:
    bool Create(int midi_port, GameObject** game_object_out);
};

}  // End namespace midistar

#endif  // MIDISTAR_MIDIINSTRUMENTGAMEOBJECTFACTORY_H_
