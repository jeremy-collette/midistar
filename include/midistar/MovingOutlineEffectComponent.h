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

#ifndef MIDISTAR_SMOKERINGEFFECTCOMPONENT_H_
#define MIDISTAR_SMOKERINGEFFECTCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The SmokeRingEffectComponent transforms its owner to create a 'smoke ring'
 * effect.
 *
 * Each tick, the transformation will continue until it is complete.
 */
class MovingOutlineEffectComponent : public Component {
 public:
    /**
     * Constructor.
     */
     explicit MovingOutlineEffectComponent();

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    const static int DURATION = 100;
    const static sf::Color INNER_COLOUR;
    const static sf::Color OUTLINE_COLOUR;
    constexpr static float OUTLINE_INCREASE = 1.025f;
    constexpr static float OUTLINE_THICKNESS = 5.0f;

    sf::Color original_colour_;
    sf::Color original_outline_colour_;
    float original_outline_thickness_;
    int time_remaining_;
};

}   // namespace midistar

#endif  // MIDISTAR_SMOKERINGEFFECTCOMPONENT_H_
