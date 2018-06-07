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

#include "midistar/GameObject.h"

namespace midistar {

GameObject::GameObject(double x_pos, double y_pos)
        : components_{0}
        , request_delete_{false}
        , to_delete_{}
        , x_pos_{x_pos}
        , y_pos_{y_pos} {
    for (int i=0; i < Component::NUM_COMPONENTS; ++i) {
        components_[i] = nullptr;
    }
}

void GameObject::DeleteComponent(ComponentType type) {
    if (!components_[type]) {
        return;
    }
    to_delete_.push_back(components_[type]);
    components_[type] = nullptr;
}

void GameObject::GetPosition(double* x, double* y) {
    *x = x_pos_;
    *y = y_pos_;
}

bool GameObject::GetRequestDelete() {
    return request_delete_;
}

bool GameObject::HasComponent(ComponentType type) {
    return components_[type];
}

void GameObject::SetComponent(Component* c) {
    DeleteComponent(c->GetType());
    components_[c->GetType()] = c;
}

void GameObject::SetPosition(double x, double y) {
    x_pos_ = x;
    y_pos_ = y;
}

void GameObject::SetRequestDelete(bool del) {
    request_delete_ = del;
}

void GameObject::Update(Game* g, int delta) {
    for (const auto& c : components_) {
        if (c) {
            c->Update(g, this, delta);
        }
    }

    for (const auto& c : to_delete_) {
        delete c;
    }
    to_delete_.clear();
}

}   // End namespace midistar
