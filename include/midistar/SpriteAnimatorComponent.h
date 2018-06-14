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

#ifndef MIDISTAR_SPRITEANIMATORCOMPONENT_H_
#define MIDISTAR_SPRITEANIMATORCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The SpriteAnimatorComponent class animates GameObjects that contain an
 * sf::Sprite instance which uses a spritesheet.
 */
class SpriteAnimatorComponent : public Component {
 public:
    /**
     * Constructor
     */
    SpriteAnimatorComponent(int sprite_size, int row, int col, int fps);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    int col_;  //!< The column in the sprite sheet
    int last_frame_delta_;  //!< The time since last frame
    const int ms_per_frame_;  //!< Milliseconds per frame
    int row_;  //!< The row in the sprite sheet
    const int sprite_size_;  //!< The size of each sprite
};

}   // End namespace midistar

#endif  // MIDISTAR_SPRITEANIMATORCOMPONENT_H_
