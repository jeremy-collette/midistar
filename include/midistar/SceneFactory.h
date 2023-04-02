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

#ifndef MIDISTAR_SCENEFACTORY_H_
#define MIDISTAR_SCENEFACTORY_H_

#include "midistar/Scene.h"

namespace midistar {

class SceneFactory {
 public:
    virtual bool Create(
        Game* game
        , sf::RenderWindow* render_window
        , Scene** scene) = 0;
};

}   // End namespace midistar

#endif  // MIDISTAR_SCENEFACTORY_H_
