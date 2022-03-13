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

#ifndef MIDISTAR_INSTRUMENTPRACTICEMODECOMPONENT_H_
#define MIDISTAR_INSTRUMENTPRACTICEMODECOMPONENT_H_

#include <memory>
#include <unordered_set>

#include "midistar/CollisionHandlerComponent.h"
#include "midistar/SongNoteComponent.h"

namespace midistar {

/**
  * The InstrumentPracticeModeComponent class enables Practice Mode, where all
  * notes will stop moving when any note is colliding with the instrument
  * without being played.
  */
class InstrumentPracticeModeComponent : public CollisionHandlerComponent {
 public:
     InstrumentPracticeModeComponent();

     virtual void HandleCollisions(
             Game* g
             , GameObject* o
             , int delta
             , std::vector<GameObject*> colliding_with);

     bool GetInstrumentIsCollidingWithNote();

 private:
    bool colliding_with_note_;
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTPRACTICEMODECOMPONENT_H_
