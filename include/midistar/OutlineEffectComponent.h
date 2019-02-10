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

#ifndef MIDISTAR_OUTLINEEFFECTCOMPONENT_H_
#define MIDISTAR_OUTLINEEFFECTCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The OutlineEffectComponent transforms its owner to create an outline.
 *
 * Each tick, the transformation will continue until it is complete.
 */
class OutlineEffectComponent : public Component {
 public:
    /**
     * Constructor.
     */
     explicit OutlineEffectComponent();

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    const static int DURATION = 100;
    const static sf::Color OUTLINE_COLOUR;
    constexpr static float OUTLINE_INCREASE = 1.05f;
    constexpr static float OUTLINE_THICKNESS = 5.0f;

    int time_remaining_;
};

}   // namespace midistar

#endif  // MIDISTAR_OUTLINEEFFECTCOMPONENT_H_
