/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
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

#include <algorithm>
#include <SFML/Graphics.hpp>

namespace midistar {

// We have to do some magic here and cast the nullptr to get the compiler to
// call the delegate constructor
GameObject::GameObject()
    : GameObject{
        static_cast<sf::RectangleShape*>(nullptr)
        , 0.0
        , 0.0
        , 0.0
        , 0.0 } {
}

GameObject::~GameObject() {
    for (auto c : components_) {
        delete c;
    }

    if (drawable_) {
        delete drawable_;
    }

    for (auto child : children_) {
        delete child;
    }
}

void GameObject::AddChild(GameObject* const game_object) {
    this->children_.push_back(game_object);
}

void GameObject::AddTag(std::string tag) {
    tags_.push_back(tag);
}

void GameObject::DeleteComponent(ComponentType type) {
    if (!components_[type]) {
        return;
    }
    to_delete_.push_back(components_[type]);
    components_[type] = nullptr;
}

void GameObject::Draw(sf::RenderWindow* window) {
    if (!enabled_ || !drawable_) {
        return;
    }

    window->draw(*drawable_);

    for (const auto& child : children_) {
        child->Draw(window);
    }
}

std::vector<GameObject*>& GameObject::GetChildren() {
    return children_;
}

bool GameObject::GetEnabled() {
    return enabled_;
}

void GameObject::GetPosition(double* x, double* y) {
    if (!transformable_) {
        *x = 0;
        *y = 0;
        return;
    }

    auto pos = transformable_->getPosition();
    *x = pos.x;
    *y = pos.y;
}

void GameObject::GetSize(double* w, double* h) {
    // We use RectangleShape::setSize() in the SetSize() method, so we have to
    // use RectangleShape::getSize() here.
    auto* rect = GetDrawformable<sf::RectangleShape>();
    if (rect) {
        auto size = rect->getSize();
        *w = size.x;
        *h = size.y;
    } else {
        if (!transformable_) {
            *w = 0;
            *h = 0;
            return;
        }

        auto scale = transformable_->getScale();
        *w = original_width_ * scale.x;
        *h = original_height_ * scale.y;
    }
}

bool GameObject::GetRequestDelete() {
    return request_delete_;
}

bool GameObject::HasComponent(ComponentType type) {
    return components_[type];
}

bool GameObject::HasTag(const std::string& tag) const {
    return std::find(tags_.begin(), tags_.end(), tag) != tags_.end();
}

void GameObject::SetComponent(Component* c) {
    DeleteComponent(c->GetType());
    components_[c->GetType()] = c;
}

void GameObject::SetEnabled(bool enabled) {
    enabled_ = enabled;
}

void GameObject::SetPosition(double x, double y) {
    if (transformable_) {
        transformable_->setPosition(static_cast<float>(x)
            , static_cast<float>(y));
    }
}

void GameObject::SetRequestDelete(bool del) {
    request_delete_ = del;
}

void GameObject::SetSize(double w, double h) {
    // We use RectangleShape::setSize to stop the outline being stretched.
    auto* rect = GetDrawformable<sf::RectangleShape>();
    if (rect) {
        rect->setSize({static_cast<float>(w), static_cast<float>(h)});
    } else if (transformable_) {
        transformable_->setScale(static_cast<float>(w / original_width_)
            , static_cast<float>(h / original_height_));
    }
}

void GameObject::SetTimeScale(float time_scale) {
    time_scale_ = time_scale;
}

void GameObject::Update(Game* g, int delta) {
    if (!enabled_) {
        return;
    }

    auto scaled_delta = static_cast<int>(delta * time_scale_);
    auto has_component = false;
    for (const auto& c : components_) {
        if (c) {
            c->Update(g, this, scaled_delta);
            has_component = true;
        }
    }

    // Cleanup children
    auto children_to_delete = std::vector<GameObject*>{ };
    for (const auto& child : children_) {
        child->Update(g, scaled_delta);
        if (child->GetRequestDelete()) {
            children_to_delete.push_back(child);
        } else {
            has_component = true;
        }
    }
    for (const auto& child : children_to_delete) {
        children_.erase(std::remove(children_.begin(), children_.end(), child),
            children_.end());
        delete child;
    }

    // If we don't have any components, delete the GameObject
    if (!has_component) {
        SetRequestDelete(true);
    }

    for (const auto& c : to_delete_) {
        delete c;
    }
    to_delete_.clear();
}

float GameObject::GetTimeScale() {
    return time_scale_;
}

}   // End namespace midistar
