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

#include <cassert>

#include "midistar/GameObject.h"

namespace midistar {

template <typename T>
GameObject<T>::GameObject(T* drawable, double x_pos, double y_pos)
        : components_{0}
        , drawable_{drawable}     
        , request_delete_{false}
        , to_delete_{}
        , x_pos_{x_pos}
        , y_pos_{y_pos} {
    for (int i=0; i < Component::NUM_COMPONENTS; ++i) {
        components_[i] = nullptr;
    }
}

template <typename T>
template <typename U>
GameObject<T>::GameObject(GameObject<U>&& move) 
        : GameObject{static_cast<T*>(move.drawable_), move.x_pos_
            , move.y_pos_} {
    for (int i=0; i < Component::NUM_COMPONENTS; ++i) {
        components_[i] = move.components_[i];
        move.components_[i] = nullptr;
    }
    assert(drawable_);
    move.drawable_ = nullptr;
}

template <typename T>
GameObject<T>::~GameObject() {
    delete drawable_;

    for (Component* c : components_) {
        delete c;
    }
}

template <typename T>
void GameObject<T>::DeleteComponent(ComponentType type) {
    if (!components_[type]) {
        return;
    }
    to_delete_.push_back(components_[type]);
    components_[type] = nullptr;
}

template <typename T>
T& GameObject<T>::GetDrawableObject() {
    return *drawable_;
}

template <typename T>
void GameObject<T>::GetPosition(double* x, double* y) {
    *x = x_pos_;
    *y = y_pos_;
}

template <typename T>
bool GameObject<T>::GetRequestDelete() {
    return request_delete_;
}

template <typename T>
bool GameObject<T>::HasComponent(ComponentType type) {
    return components_[type];
}

template <typename T>
void GameObject<T>::SetComponent(Component* c) {
    DeleteComponent(c->GetType());
    components_[c->GetType()] = c;
}

template <typename T>
void GameObject<T>::SetPosition(double x, double y) {
    x_pos_ = x;
    y_pos_ = y;
}

template <typename T>
void GameObject<T>::SetRequestDelete(bool del) {
    request_delete_ = del;
}

template <typename T>
void GameObject<T>::Update(Game* g, int delta) {
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
