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

#ifndef MIDISTAR_GAMEOBJECT_TPP_
#define MIDISTAR_GAMEOBJECT_TPP_

namespace midistar {

template<typename T>
GameObject::GameObject(
    T* drawformable
    , double x_pos
    , double y_pos
    , double width
    , double height)
        : components_{0}
        , drawable_{*dynamic_cast<sf::Drawable*>(drawformable)}
        , original_height_{height}
        , original_width_{width}
        , request_delete_{false}
        , to_delete_{}
        , transformable_{*dynamic_cast<sf::Transformable*>(drawformable)}
        , x_pos_{x_pos}
        , y_pos_{y_pos} {    
    transformable_.setPosition(x_pos, y_pos);
    for (int i=0; i < Component::NUM_COMPONENTS; ++i) {
        components_[i] = nullptr;
    }
}

template <typename T> 
T* GameObject::GetComponent(ComponentType type) {
    return static_cast<T*>(components_[type]);
}

template <typename T>
T* GameObject::GetDrawformable() {
    // We can use drawable_ or transformable_ interchangeably here, as they
    // both point to the same object.
    return dynamic_cast<T*>(&drawable_);
}

}  // End namespace midistar

#endif  // MIDISTAR_GAMEOBJECT_TPP_
