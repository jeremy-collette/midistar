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

#ifndef MIDISTAR_FADEOUTEFFECTCOMPONENT_H_
#define MIDISTAR_FADEOUTEFFECTCOMPONENT_H_

#include <limits>

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The FadeOutEffectComponent transforms its owner to create a 'fade out'
 * effect.
 *
 * Each tick, the transformation will continue until it is complete.
 */
class FadeOutEffectComponent : public Component {
 public:
    /**
     * Constructor.
     */
     FadeOutEffectComponent();

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    constexpr static float ALPHA_MULTIPLIER = 0.85f;
    constexpr static float EPSILON = std::numeric_limits<float>::epsilon();
};

}   // namespace midistar

#endif  // MIDISTAR_FADEOUTEFFECTCOMPONENT_H_
