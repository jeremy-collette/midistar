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

#ifndef MIDISTAR_PHYSICSCOMPONENT_H_
#define MIDISTAR_PHYSICSCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The PhysicsComponent class provides velocity functionality to its owner.
 *
 * Each tick, the X and Y position of the owner are updated by the X velocity
 * and Y velocity respectively.
 */
class PhysicsComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param x_vel Default X velocity.
     * \param y_vel Default Y velocity.
     */
    PhysicsComponent(double x_vel, double y_vel);

    /**
     * Gets the velocity.
     *
     * \param[out] x_vel Stores X velocity.
     * \param[out] y_vel Stores Y velocity.
     */
    void GetVelocity(double* x_vel, double* y_vel);

    /**
     * Sets the velocity.
     *
     * \param x_vel X velocity.
     * \param y_vel Y velocity.
     */
    void SetVelocity(double x_vel, double y_vel);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    double x_vel_;  //!< Stores X velocity
    double y_vel_;  //!< Stores Y velocity
};

}   // namespace midistar

#endif  // MIDISTAR_PHYSICSCOMPONENT_H_
