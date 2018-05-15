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

#ifndef MIDISTAR_COLLISIONDETECTORCOMPONENT_H_
#define MIDISTAR_COLLISIONDETECTORCOMPONENT_H_

#include <vector>

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace Midistar {

/**
 * The CollisionDetectorComponent class detects collisions between the
 * GraphicsComponent of its owner and the GraphicsComponent of other
 * GameObjects.
 */
class CollisionDetectorComponent : public Component {
 public:
     /**
      * Constructor. 
      */
     CollisionDetectorComponent();

     /**
      * Finds GameObjects that are colliding with the owner. 
      *
      * \return Colliding GameObjects.
      */
     const std::vector<GameObject*>& GetCollidingWith();

     /**
      * Determines whether or not the owner is currently colliding with another
      * GameObject.
      *
      * \return True if a collision is occuring. False otherwise.
      */
     bool GetIsColliding();

     /**
      * \copydoc Component::Update()
      */
     virtual void Update(Game* g, GameObject* o);

 private:
     std::vector<GameObject*> colliding_with_;  //!< Holds colliding objects
};

}   // End namespace Midistar

#endif  // MIDISTAR_COLLISIONDETECTORCOMPONENT_H_
