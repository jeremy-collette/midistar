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

#include "midistar/MovingOutlineEffectComponent.h"

#ifdef DEBUG
#include <iostream>
#endif

#include "midistar/ResizeComponent.h"

namespace midistar {

const sf::Color MovingOutlineEffectComponent::INNER_COLOUR = sf::Color::Transparent;

const sf::Color MovingOutlineEffectComponent::OUTLINE_COLOUR = {255, 255, 255};

MovingOutlineEffectComponent::MovingOutlineEffectComponent()
        : time_remaining_{MovingOutlineEffectComponent::DURATION}
        , Component{ Component::SMOKE_RING_EFFECT} {
}

void MovingOutlineEffectComponent::Update(Game * g, GameObject * o, int delta) {
    auto circle = o->GetDrawformable<sf::CircleShape>();
    if (!circle) {
        return;
    }

    // Set constants
    if (time_remaining_ == MovingOutlineEffectComponent::DURATION) {
        original_colour_ = circle->getFillColor();
        original_outline_thickness_ = circle->getOutlineThickness();
        original_outline_colour_ = circle->getOutlineColor();

        circle->setFillColor(MovingOutlineEffectComponent::INNER_COLOUR);
        circle->setOutlineThickness(MovingOutlineEffectComponent::OUTLINE_THICKNESS);
        circle->setOutlineColor(MovingOutlineEffectComponent::OUTLINE_COLOUR);
    }

    // Increase the thickness of the outline
    auto thickness = circle->getOutlineThickness();
    thickness *= MovingOutlineEffectComponent::OUTLINE_INCREASE;
    circle->setOutlineThickness(thickness);

    // If we're finished, delete the component
    time_remaining_ -= delta;
    if (time_remaining_ <= 0) {
        circle->setFillColor(original_colour_);
        circle->setOutlineThickness(original_outline_thickness_);
        circle->setOutlineColor(original_outline_colour_);
        o->DeleteComponent(GetType());
    }
}

}  // End namespace midistar