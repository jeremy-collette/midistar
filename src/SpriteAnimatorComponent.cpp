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

#include "midistar/SpriteAnimatorComponent.h"

namespace midistar {

SpriteAnimatorComponent::SpriteAnimatorComponent(
    int sprite_size
    , int row
    , int col
    , int fps)
        : Component{Component::SPRITE_ANIMATOR}
        , col_{col}
        , last_frame_delta_{0}
        , ms_per_frame_{1000 / fps}
        , row_{row}
        , sprite_size_{sprite_size} {
}

void SpriteAnimatorComponent::Update(Game*, GameObject* o, int delta) {
    // We only update X frames per second
    last_frame_delta_ += delta;
    if (last_frame_delta_ < ms_per_frame_) {
        return;
    }
    last_frame_delta_ = 0;

    // We can only operate on GameObjects that actually have a sprite
    auto sprite = o->GetDrawformable<sf::Sprite>();
    if (!sprite) {
        return;
    }

    // Set out position in the spritesheet to select a specific sprite
    sprite->setTextureRect({col_ * sprite_size_, row_ * sprite_size_
            , sprite_size_, sprite_size_});
    ++col_;

    // Wrap-around to first sprite
    if (col_ * sprite_size_ + sprite_size_ >
            static_cast<int>(sprite->getTexture()->getSize().x)) {
        col_ = 0;
    }
}

}   // End namespace midistar
