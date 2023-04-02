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

#ifndef MIDISTAR_SCOREDELTAPROVIDER_H_
#define MIDISTAR_SCOREDELTAPROVIDER_H_

#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

class ScoreDeltaProvider {
 public:
    virtual int GetScoreDelta(
        Game* g
        , GameObject* o
        , int delta
        , bool is_colliding) = 0;
};

}   // End namespace midistar

#endif  // MIDISTAR_SCOREDELTAPROVIDER_H_
