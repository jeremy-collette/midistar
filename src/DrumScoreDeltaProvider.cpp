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

#include "midistar/DrumScoreDeltaProvider.h"

namespace midistar {

DrumScoreDeltaProvider::DrumScoreDeltaProvider()
    : already_scored_{ false } {
}

int DrumScoreDeltaProvider::GetScoreDelta(
    Game* g
    , GameObject* o
    , int delta
    , bool is_colliding) {

    if (!is_colliding || already_scored_) {
        return 0;
    }
    already_scored_ = true;

    return DEFAULT_DRUM_SCORE;
}

}  // End namespace midistar