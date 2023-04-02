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

#include "midistar/DeleteOffscreenComponent.h"

#include "midistar/Config.h"

namespace midistar {

DeleteOffscreenComponent::DeleteOffscreenComponent()
        : Component{Component::DELETE_OFFSCREEN} {
}

void DeleteOffscreenComponent::Update(Game*, GameObject* o, int) {
    double width, height, x, y;
    o->GetSize(&width, &height);
    o->GetPosition(&x, &y);

    double max_x = Config::GetInstance().GetScreenWidth() + THRESHOLD;
    double max_y = Config::GetInstance().GetScreenHeight() + THRESHOLD;
    if ((x + width < -THRESHOLD || x > max_x)
            || (y + height < -THRESHOLD || y > max_y)) {
       o->SetRequestDelete(true);
    }
}

}   // End namespace midistar
