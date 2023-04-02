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

#include "midistar/OutlineEffectComponent.h"

#include "midistar/ResizeComponent.h"

namespace midistar {

const sf::Color OutlineEffectComponent::OUTLINE_COLOUR = {255, 255, 255};

OutlineEffectComponent::OutlineEffectComponent()
        : Component{ Component::FADING_OUTLINE_EFFECT}
        , time_remaining_{OutlineEffectComponent::DURATION} {
}

void OutlineEffectComponent::Update(Game*, GameObject * o, int delta) {
    auto circle = o->GetDrawformable<sf::CircleShape>();
    if (!circle) {
        return;
    }

    // Set constants
    if (time_remaining_ == OutlineEffectComponent::DURATION) {
        circle->setOutlineThickness(OutlineEffectComponent::OUTLINE_THICKNESS);
        circle->setOutlineColor(OutlineEffectComponent::OUTLINE_COLOUR);
    }

    // Increase the thickness of the outline
    auto thickness = circle->getOutlineThickness();
    thickness *= OutlineEffectComponent::OUTLINE_INCREASE;
    circle->setOutlineThickness(thickness);

    // If we're finished, delete the component
    time_remaining_ -= delta;
    if (time_remaining_ <= 0) {
        o->DeleteComponent(GetType());
    }
}

}  // End namespace midistar
