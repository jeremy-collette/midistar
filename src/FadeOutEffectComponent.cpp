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

#include "midistar/FadeOutEffectComponent.h"

#include "midistar/ResizeComponent.h"
#include "..\include\midistar\FadeOutEffectComponent.h"

namespace midistar {

const sf::Color FadeOutEffectComponent::OUTLINE_COLOUR = {255, 255, 255};

FadeOutEffectComponent::FadeOutEffectComponent()
        : time_remaining_{FadeOutEffectComponent::DURATION}
        , Component{ Component::SMOKE_RING_EFFECT} {
}

void FadeOutEffectComponent::Update(Game * g, GameObject * o, int delta) {
    auto circle = o->GetDrawformable<sf::CircleShape>();
    if (!circle) {
        return;
    }

    // Change the alpha of the circle, to dim the circle
    auto colour = circle->getFillColor();
    colour.a *= 0.95;
    circle->setFillColor(colour);

    // Increase size of circle, to give the circle a growing effect
    auto radius = circle->getRadius();
    auto new_radius = radius * FadeOutEffectComponent::SIZE_INCREASE;
    circle->setRadius(new_radius);

    // Re-centre circle
    auto pos_diff = new_radius - radius;
    double x, y;
    o->GetPosition(&x, &y);
    x -= pos_diff;
    y -= pos_diff;
    o->SetPosition(x, y);

    // If we're finished, delete the component
    time_remaining_ -= delta;
    if (time_remaining_ <= 0) {
        o->SetComponent(new ResizeComponent{0, 0});
        o->DeleteComponent(GetType());
    }
}

}  // End namespace midistar