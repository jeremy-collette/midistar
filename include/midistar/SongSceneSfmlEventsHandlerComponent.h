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

#ifndef MIDISTAR_SONGSCENESFMLEVENTSHANDLERCOMPONENT_H_
#define MIDISTAR_SONGSCENESFMLEVENTSHANDLERCOMPONENT_H_

#include "midistar/SfmlEventsHandlerComponent.h"

namespace midistar {

class SongSceneSfmlEventsHandlerComponent : public SfmlEventsHandlerComponent {
 public:
     virtual void HandleEvent(Game* g, GameObject* o, int delta, sf::Event evt);
};

}   // End namespace midistar

#endif  // MIDISTAR_SONGSCENESFMLEVENTSHANDLERCOMPONENT_H_
