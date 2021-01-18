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

#include "midistar/PhysicsComponent.h"

namespace midistar {
PhysicsComponent::PhysicsComponent(double x_vel, double y_vel)
        : Component{Component::PHYSICS}
        , x_vel_{x_vel}
        , y_vel_{y_vel} {
}

void PhysicsComponent::GetVelocity(double* x_vel, double* y_vel) {
    *x_vel = x_vel_;
    *y_vel = y_vel_;
}

void PhysicsComponent::SetVelocity(double x_vel, double y_vel) {
    x_vel_ = x_vel;
    y_vel_ = y_vel;
}

void PhysicsComponent::Update(Game*, GameObject* o, int delta) {
    double x, y;
    o->GetPosition(&x, &y);
    x += x_vel_ * delta;
    y += y_vel_ * delta;
    o->SetPosition(x, y);
}

}   // namespace midistar
