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

#ifndef MIDISTAR_SHRINKGROWCOMPONENT_H_
#define MIDISTAR_SHRINKGROWCOMPONENT_H_

#include <limits>

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The ShrinkGrowComponent transforms its owner to shrink or grow it.
 *
 * Each tick, the transformation will continue until it is complete.
 */
class ShrinkGrowComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param target_w The target width to shrink / grow to.
     * \param target_h The target height to shrink / grow to.
     */
     explicit ShrinkGrowComponent(double target_w, double target_h);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    constexpr static float EPSILON = std::numeric_limits<float>::epsilon();
    constexpr static float SPEED = 0.25f;

    double target_h_;
    double target_w_;
};

}   // namespace midistar

#endif  // MIDISTAR_SHRINKGROWCOMPONENT_H_
