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

#include "midistar/GraphicsComponent.h"

#include "midistar/Game.h"

namespace midistar {

GraphicsComponent::GraphicsComponent(sf::RectangleShape* rect)
        : Component{Component::GRAPHICS_COMPONENT}
        , rect_{rect} {
}

GraphicsComponent::~GraphicsComponent() {
    delete rect_;
}

sf::RectangleShape& GraphicsComponent::GetShape() {
    return *rect_;
}

void GraphicsComponent::GetSize(double* x, double* y) {
    auto size = rect_->getSize();
    *x = size.x;
    *y = size.y;
}

void GraphicsComponent::SetSize(double x, double y) {
    rect_->setSize({static_cast<float>(x), static_cast<float>(y)});
}

void GraphicsComponent::Update(Game* g, GameObject* o) {
    double x, y;
    o->GetPosition(&x, &y);
    rect_->setPosition({static_cast<float>(x), static_cast<float>(y)});
    g->GetWindow().draw(*rect_);
}

}   // End namespace midistar
