/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

#ifndef MIDISTAR_DRUMSONGNOTECOLLISIONHANDLERCOMPONENT_H_
#define MIDISTAR_DRUMSONGNOTECOLLISIONHANDLERCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The DrumSongNoteCollisionHandlerComponent class handles collisions between
 * drum song notes and other GameObjects.
 */
class DrumSongNoteCollisionHandlerComponent : public CollisionHandlerComponent {
 public:
     /**
      * Constructor.
      */
     DrumSongNoteCollisionHandlerComponent(
         GameObjectFactory* game_object_factory);

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , int delta
             , std::vector<GameObject*> colliding_with);

     /**
      * Tells the collision handler whether or not it should not collide.
      *
      * \param dont_collide If set to 'true', stops handler from handling
      * collisions.
      */
     void SetDoNotCollide(bool dont_collide);

 private:
    bool HandleCollision(Game* g, GameObject* o, GameObject* collider);
               //!< Handles a collision returns true if it's a valid collision

    GameObjectFactory* game_object_factory_;
    bool dont_collide_;
};

}  // End namespace midistar

#endif  // MIDISTAR_DRUMSONGNOTECOLLISIONHANDLERCOMPONENT_H_
