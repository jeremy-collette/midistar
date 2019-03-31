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

#ifndef MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_
#define MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_

#include <vector>

#include "midistar/CollisionHandlerComponent.h"

namespace midistar {

/**
 * The InstrumentAutoPlayComponent class adds auto play functionality to
 * instruments.
 */
class InstrumentAutoPlayComponent : public CollisionHandlerComponent {
 public:
     /**
      * Determines the criteria for a collision to be detected.
      */
     enum class CollisionCriteria {
         NONE = 0,  //!< Any collision will be detected
         CENTRE = 1  //!< Only collisions where both objects overlap in the
                                                    //!< centre will be detected
     };

     /**
      * Constructor.
      *
      * \param criteria The collision criteria that must be met to start auto
      * playing a note.
      */
     explicit InstrumentAutoPlayComponent(CollisionCriteria criteria);

     /**
     * Default constructor.
     */
     InstrumentAutoPlayComponent();

     /**
      * \copydoc CollisionHandlerComponent::HandleCollisions()
      */
     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , int delta
             , std::vector<GameObject*> colliding_with);

 private:
    static constexpr double DEFAULT_CENTRE_THRESHOLD = 10.0;  //!< Determines
     //!< how close the centre of two objects should be to be considered centred
                                         //!< by default (if they're not moving)

    void HandleCollision(Game* g, GameObject* o, GameObject* collider);
                                                     //!< Handles a collision
    bool IsInCentre(GameObject* o, GameObject* collider, int delta);  //!<
                                //!< Checks if a collision is in the centre of o

    CollisionCriteria collision_criteria_;  //!< Indicates collision criteria to
      //!< that needs to be met before auto play will begin for a specific note.
    GameObject* colliding_note_;  //!< Holds the note we are colliding with. We
                     //!< need to keep track of this to play overlapping notes.
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTAUTOPLAYCOMPONENT_H_
