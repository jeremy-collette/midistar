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

#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

VerticalCollisionDetectorComponent::VerticalCollisionDetectorComponent()
        : Component{Component::VERTICAL_COLLISION_DETECTOR} {
}

const std::vector<GameObject*>& VerticalCollisionDetectorComponent::
        GetCollidingWith() {
    return colliding_with_;
}


bool VerticalCollisionDetectorComponent::GetIsColliding() {
    return GetCollidingWith().size();
}

void VerticalCollisionDetectorComponent::Update(Game* g, GameObject* o, int) {
    colliding_with_.clear();
    for (auto& other_obj : g->GetCurrentScene().GetGameObjects()) {
        if (other_obj == o ||
                !other_obj->HasComponent(Component::COLLIDABLE)) {
             continue;
        }

        double other_x, other_y, other_w, other_h;
        other_obj->GetPosition(&other_x, &other_y);
        other_obj->GetSize(&other_w, &other_h);
        if (!other_w || !other_h) {
            continue;
        }

        double x, y, w, h;
        o->GetPosition(&x, &y);
        o->GetSize(&w, &h);
        if (!w || !h) {
            continue;
        }

        if ((y >= other_y && y <= other_y + other_h)
                 || (y + h >= other_y && y + h <= other_y + other_h)
                 || (y <= other_y && y + h >= other_y + other_h)) {
            colliding_with_.push_back(other_obj);
        }
    }
}

}  // End namespace midistar
