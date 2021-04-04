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

#ifndef MIDISTAR_PHANTOMNOTECOMPONENT_H_
#define MIDISTAR_PHANTOMNOTECOMPONENT_H_

#include "midistar/Component.h"

#include <set>

namespace midistar {

class PhantomNoteComponent : public Component {
 public:
    PhantomNoteComponent(std::set<int> midi_keys, int midi_channel);

    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    int midi_channel_;
    std::set<int> midi_keys_;
};

}  // End namespace midistar

#endif  // MIDISTAR_PHANTOMNOTECOMPONENT_H_
