/*
 * midistar
 * Copyright (C) 2018-2019 Jeremy Collette.
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

#ifndef MIDISTAR_PIANOSONGNOTECOLLISIONHANDLERCOMPONENT_H_
#define MIDISTAR_PIANOSONGNOTECOLLISIONHANDLERCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The PianoSongNoteCollisionHandlerComponent class handles collisions between
 * song notes and other GameObjects.
 */
class PianoSongNoteCollisionHandlerComponent : public CollisionHandlerComponent{
 public:
     /**
      * Constructor.
      */
     PianoSongNoteCollisionHandlerComponent(
        GameObjectFactory* game_object_factory);

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , int delta
             , std::vector<GameObject*> colliding_with);

 private:
    static const char NOTE_COLLISION_CUTOFF = 20;  //!< Notes must be within
        //!< this many pixels from the top of the instrument to be completely
        //!< played.

    bool HandleCollision(Game* g, GameObject* o, GameObject* collider);
               //!< Handles a collision returns true if it's a valid collision

    GameObjectFactory* game_object_factory_;
    GameObject* grinding_;  //!< Holds GameObject display metal grinding effect
};

}  // End namespace midistar

#endif  // MIDISTAR_PIANOSONGNOTECOLLISIONHANDLERCOMPONENT_H_
