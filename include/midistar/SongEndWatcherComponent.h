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

#ifndef MIDISTAR_SONGENDWATCHERCOMPONENT_H_
#define MIDISTAR_SONGENDWATCHERCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

class SongEndWatcherComponent : public Component {
 public:
    SongEndWatcherComponent();

    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    GameObjectFactory* game_object_factory_;
};

}   // End namespace midistar

#endif  // MIDISTAR_SONGENDWATCHERCOMPONENT_H_
