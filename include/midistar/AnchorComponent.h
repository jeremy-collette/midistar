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

#ifndef MIDISTAR_ANCHORCOMPONENT_H_
#define MIDISTAR_ANCHORCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

typedef char AnchorBehaviour;

/**
 * The AnchorComponent class 'anchors' a GameObject's position to an X/Y
 * coordinate on the screen.
 *
 * Each tick, the AnchorComponent uses a ResizeComponent to resize the owner's
 * GraphicsComponent so the X/Y position is at the provided coordinate on the
 * screen. This prevents the selected corner from moving from the coordinate.
 */
class AnchorComponent : public Component {
 public:
    /**
     * The AnchorBehaviour enum defines different behaviour options for the
     * AnchorComponent.
     *
     * DEFAULT will behave as expected, as described in the class overview.
     * FALLING will remove the AnchorComponent when the owner's position 
     * reaches the anchor point.
     */
    enum : AnchorBehaviour {
        DEFAULT = 0
        , FALLING
    };

    /**
     * Constructor.
     *
     * \param x_target The X coordinate to anchor to.
     * \param y_target The Y coordinate to anchor to.
     * \param behaviour Controls additional component behaviour.
     */
    AnchorComponent(
            double x_target
            , double y_target
            , AnchorBehaviour behaviour);

    /**
     * Constructor.
     *
     * \param x_target The X coordinate to anchor to.
     * \param y_target The Y coordinate to anchor to.
     */
    AnchorComponent(double x_target, double y_target);

    /**
     * Gets the point to anchor to.
     *
     * \param x_target The X coordinate to anchor to.
     * \param y_target The Y coordinate to anchor to.
     */
    void GetTarget(double* x_target, double* y_target);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o);

 private:
    AnchorBehaviour behaviour_;  //!< Additional behaviour setting
    double x_target_;  //!< The X coordinate
    double y_target_;  //!< The Y coordinate
};

}   // End namespace midistar

#endif  // MIDISTAR_ANCHORCOMPONENT_H_
