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

#include "midistar/ShrinkGrowComponent.h"

#include <cmath>

#include "midistar/Config.h"
#include "midistar/ResizeComponent.h"

namespace midistar {

ShrinkGrowComponent::ShrinkGrowComponent(double target_w, double target_h)
        : Component{SHRINK_GROW}
        , target_h_{target_h}
        , target_w_{target_w} {
}

void ShrinkGrowComponent::Update(Game*, GameObject* o, int) {
    double w, h;
    o->GetSize(&w, &h);

    // Find how far we are from the target
    double w_diff, h_diff;
    w_diff = target_w_ - w;
    h_diff = target_h_ - h;

    // Interpolate this by the speed
    double new_w, new_h;
    new_w = w + (w_diff * SPEED);
    new_h = h + (h_diff * SPEED);

    // Resize
    o->SetComponent(new ResizeComponent{ new_w, new_h
        , ResizeComponent::CENTRE});

    // If we've reached our target, finish.
    if (std::fabs(w_diff) <= EPSILON && std::fabs(h_diff) <= EPSILON) {
        o->DeleteComponent(GetType());
    }
}

}  // End namespace midistar
