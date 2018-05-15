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

#include "midistar/ArrowsInputComponent.h"

#include "midistar/PhysicsComponent.h"

namespace Midistar {

ArrowsInputComponent::ArrowsInputComponent()
        : Component(Component::TEST_INPUT_COMPONENT) {
}

void ArrowsInputComponent::Update(Game*, GameObject* o) {
    auto physics = o->GetComponent<PhysicsComponent>(
            Component::PHYSICS_COMPONENT);
    if (!physics) {
        return;
    }

    double vel_x, vel_y;
    physics->GetVelocity(&vel_x, &vel_y);
    vel_x = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * -1
        + sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * 1;
    vel_y = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) * -1
        + sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * 1;

    physics->SetVelocity(vel_x, vel_y);
}

}  // End namespace Midistar
