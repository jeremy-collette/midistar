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

#ifndef MIDISTAR_COLLISIONHANDLERCOMPONENT_H_
#define MIDISTAR_COLLISIONHANDLERCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The CollisionHandlerComponent class polls the owner's 
 * CollisionDetectorComponent and handles collisions when they occur. 
 */
class CollisionHandlerComponent : public Component {
 public:
    /**
     * Constructor. 
     *
     * \param type The ComponetType of the derived class.
     */
    explicit CollisionHandlerComponent(ComponentType type);

    /**
     * Handles most recent collisions.
     *
     * \param[in,out] g The Game being played.
     * \param[in,out] o The owner of the component.
     * \param[in,out] colliding_with The objects colliding with the owner.
     */
    virtual void HandleCollisions(
            Game* g
            , GameObject* o
            , const std::vector<GameObject*> colliding_with) = 0;

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o);
};

}   // End namespace midistar

#endif  // MIDISTAR_COLLISIONHANDLERCOMPONENT_H_
