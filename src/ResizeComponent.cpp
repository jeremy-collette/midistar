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

#include "midistar/ResizeComponent.h"

namespace midistar {

ResizeComponent::ResizeComponent(
    double new_width
    , double new_height
    , AnchorFlag anchor_flags)
        : Component{Component::RESIZE}
        , anchor_flags_{anchor_flags}
        , new_height_{new_height}
        , new_width_{new_width} {
}

ResizeComponent::ResizeComponent(double new_width, double new_height)
        : ResizeComponent{new_width, new_height, ResizeComponent::TOP_LEFT} {
}

void ResizeComponent::Update(Game*, GameObject* o, int) {
    double width, height;
    o->GetSize(&width, &height);
    o->SetSize(new_width_, new_height_);

    double anchor_x, anchor_y;
    CalculateAnchorPosition(&anchor_x, &anchor_y);

    // Move new shape depending on anchor
    double width_diff = new_width_ - width;
    double height_diff = new_height_ - height;
    double x, y;
    o->GetPosition(&x, &y);
    x -= anchor_x * width_diff;
    y -= anchor_y * height_diff;

    o->SetPosition(x, y);
    o->DeleteComponent(GetType());
}

void ResizeComponent::CalculateAnchorPosition(
        double* anchor_x
        , double* anchor_y) {
    *anchor_x = 0;
    *anchor_y = 0;
    int points = 0;

    if (anchor_flags_ & TOP_LEFT) {
        *anchor_x += 0;
        *anchor_y += 0;
        ++points;
    }

    if (anchor_flags_ & TOP_RIGHT) {
        *anchor_x += 1;
        *anchor_y += 0;
        ++points;
    }

    if (anchor_flags_ & BOT_LEFT) {
        *anchor_x += 0;
        *anchor_y += 1;
        ++points;
    }

    if (anchor_flags_ & BOT_RIGHT) {
        *anchor_x += 1;
        *anchor_y += 1;
        ++points;
    }

    *anchor_x /= points;
    *anchor_y /= points;
}

}  // End namespace midistar
