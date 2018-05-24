/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
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

#include "midistar/CollisionDetectorComponent.h"

#include "midistar/GraphicsComponent.h"

namespace midistar {

CollisionDetectorComponent::CollisionDetectorComponent()
        : Component{Component::COLLISION_DETECTOR} {
}

const std::vector<GameObject*>& CollisionDetectorComponent::GetCollidingWith() {
    return colliding_with_;
}


bool CollisionDetectorComponent::GetIsColliding() {
    return GetCollidingWith().size();
}

void CollisionDetectorComponent::Update(Game* g, GameObject* o) {
    auto graphics = o->GetComponent<GraphicsComponent>(Component::GRAPHICS);
    if (!graphics) {
        return;
    }

    colliding_with_.clear();

    for (auto& other_obj : g->GetGameObjects()) {
        if (other_obj == o) {
             continue;
        }

        auto other_graphics = other_obj->GetComponent<GraphicsComponent>(
                Component::GRAPHICS);
        if (!other_graphics) {
            continue;
        }

        if (graphics->GetShape().getGlobalBounds().intersects(
                    other_graphics->GetShape().getGlobalBounds())) {
            colliding_with_.push_back(other_obj);
        }
    }
}

}  // End namespace midistar
