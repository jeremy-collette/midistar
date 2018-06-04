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

#include "midistar/TransformComponent.h"

namespace midistar {

TransformComponent::TransformComponent(
    std::function<void(Game*, GameObject*, int)> func)
        : Component{Component::TRANSFORM}
        , func_{func} {
}

void TransformComponent::Update(Game* g, GameObject* o, int delta) {
    func_(g, o, delta);
    o->DeleteComponent(GetType());
}

}   // End namespace midistar