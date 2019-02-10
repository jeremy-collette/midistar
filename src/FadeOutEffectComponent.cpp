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

namespace midistar {

FadeOutEffectComponent::FadeOutEffectComponent()
        : Component{ Component::FADING_OUTLINE_EFFECT} {
}

void FadeOutEffectComponent::Update(Game * g, GameObject * o, int delta) {
    auto circle = o->GetDrawformable<sf::CircleShape>();
    if (!circle) {
        return;
    }

    // Change the alpha of the circle, to dim the circle
    auto colour = circle->getFillColor();
    colour.a *= FadeOutEffectComponent::ALPHA_MULTIPLIER;
    circle->setFillColor(colour);

    // If we're finished, delete the component
    if (colour.a <= EPSILON) {
        o->SetComponent(new ResizeComponent{0, 0});
        o->DeleteComponent(GetType());
    }
}

}  // End namespace midistar