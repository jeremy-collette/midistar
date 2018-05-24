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

#ifndef MIDISTAR_SONGNOTECOLLISIONHANDLERCOMPONENT_H_
#define MIDISTAR_SONGNOTECOLLISIONHANDLERCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"

namespace midistar {

/**
 * The SongNoteCollisionHandlerComponent class handles collisions between song
 * notes and other GameObjects.
 */
class SongNoteCollisionHandlerComponent : public CollisionHandlerComponent {
 public:
     /**
      * Constructor.
      */
     SongNoteCollisionHandlerComponent();

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , std::vector<GameObject*> colliding_with);

 private:
     bool auto_playing_;  //!< Determines if we are currently auto playing a
                                                                    //!< note
};

}  // End namespace midistar

#endif  // MIDISTAR_SONGNOTECOLLISIONHANDLERCOMPONENT_H_
