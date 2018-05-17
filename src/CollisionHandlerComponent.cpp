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

#include "midistar/CollisionHandlerComponent.h"

#include "midistar/CollisionDetectorComponent.h"

namespace midistar {

CollisionHandlerComponent::CollisionHandlerComponent(ComponentType type)
        : Component{type} {
}

void CollisionHandlerComponent::Update(Game* g, GameObject* o) {
    auto detector = o->GetComponent<CollisionDetectorComponent>(
            Component::COLLISION_DETECTOR_COMPONENT);
    if (!detector) {
        return;
    }

    for (auto& other_obj : detector->GetCollidingWith()) {
        HandleCollision(g, o, other_obj);
    }
}

}  // End namespace midistar
