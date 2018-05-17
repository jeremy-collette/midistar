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

#include "midistar/AnchorComponent.h"

#include <cmath>

#include "midistar/GraphicsComponent.h"
#include "midistar/ResizeComponent.h"

namespace midistar {

AnchorComponent::AnchorComponent(
    double x_target
    , double y_target
    , AnchorBehaviour behaviour)
        : Component{Component::ANCHOR_COMPONENT}
        , behaviour_{behaviour}
        , x_target_{x_target}
        , y_target_{y_target} {
}


AnchorComponent::AnchorComponent(double x_target, double y_target)
        : AnchorComponent{x_target, y_target, AnchorComponent::DEFAULT} {
}

void AnchorComponent::GetTarget(double* x_target, double* y_target) {
    *x_target = x_target_;
    *y_target = y_target_;
}

void AnchorComponent::Update(Game*, GameObject* o) {
    double x, y;
    o->GetPosition(&x, &y);

    // If we're in FALLING mode and we've fallen to our target, we've done
    // our job!
    if (behaviour_ == FALLING && x >= x_target_ && y >= y_target_) {
        o->SetComponent(new ResizeComponent{0, 0});
        o->RemoveComponent(GetType());
        return;
    }

    auto graphics = o->GetComponent<GraphicsComponent>(
            Component::GRAPHICS_COMPONENT);
    if (!graphics) {
        return;
    }

    double width, height;
    graphics->GetSize(&width, &height);

    // We 'anchor' to a point by stretching the closest edge on either axis to
    // meet the point.
    //
    // Handle Y axis
    AnchorFlag flags = 0;
    double new_height = height;
    double top_dist = y - y_target_;
    double bottom_dist = (y + height) - y_target_;

    if (bottom_dist && fabs(bottom_dist) < fabs(top_dist)) {
        new_height = height - bottom_dist;
        flags = ResizeComponent::TOP_LEFT | ResizeComponent::TOP_RIGHT;
    } else if (top_dist && fabs(top_dist) < fabs(bottom_dist)) {
        new_height = height + top_dist;
        flags = ResizeComponent::BOT_LEFT | ResizeComponent::BOT_RIGHT;
    }

    // Handle X axis
    double new_width = width;
    double left_dist = x - x_target_;
    double right_dist = (x + width) - x_target_;
    if (right_dist && fabs(right_dist) < fabs(left_dist)) {
        new_width = width - right_dist;
        flags |= ResizeComponent::TOP_LEFT | ResizeComponent::BOT_LEFT;
    } else if (left_dist && fabs(left_dist) < fabs(right_dist)) {
        new_width = width + left_dist;
        flags |= ResizeComponent::TOP_RIGHT | ResizeComponent::BOT_RIGHT;
    }

    // If both axes are on the target, the flags will be invalid
    if (!flags) {
        flags = ResizeComponent::TOP_LEFT;
    }

    // Resize our owner so that our position is back on the target.
    // Use AnchorFlags to anchor our edge(s) that are furthrest away from the
    // target, thus stretching closest edge(s) towards / away from target.
    o->SetComponent(new ResizeComponent{
            fabs(new_width)
            , fabs(new_height)
            , flags});
}

}  // End namespace midistar
