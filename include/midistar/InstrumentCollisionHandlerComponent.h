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

#ifndef MIDISTAR_INSTRUMENTCOLLISIONHANDLERCOMPONENT_H_
#define MIDISTAR_INSTRUMENTCOLLISIONHANDLERCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"

namespace midistar {

/**
 * The InstrumentCollisionHandlerComponent class handles collisions between song
 * notes and other GameObjects.
 */
class InstrumentCollisionHandlerComponent : public CollisionHandlerComponent {
 public:
     /**
      * Constructor.
      */
     InstrumentCollisionHandlerComponent();

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject<sf::Transformable>* o
             , std::vector<GameObject<sf::Transformable>*> colliding_with);

 private:
    void HandleCollision(Game* g, GameObject<sf::Transformable>* o, GameObject<sf::Transformable>* collider);
                                                     //!< Handles a collision

    GameObject<sf::Transformable>* colliding_note_;  //!< Holds the note we are colliding with. We
                     //!< need to keep track of this to play overlapping notes.
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTCOLLISIONHANDLERCOMPONENT_H_
