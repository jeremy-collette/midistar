/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#ifndef MIDISTAR_SONGNOTEPRACTICEMODECOMPONENT_H_
#define MIDISTAR_SONGNOTEPRACTICEMODECOMPONENT_H_

#include "midistar/CollisionHandlerComponent.h"
#include "midistar/SongNoteComponent.h"

namespace midistar {

/**
  * The SongNotePracticeModeComponent  class enables Practice Mode, where all
  * notes will stop moving when any note is colliding with the instrument
  * without played being.
  */
class SongNotePracticeModeComponent : public Component {
 public:
     SongNotePracticeModeComponent();

     virtual void Update(Game* g, GameObject* o, int delta) override;
};

}  // End namespace midistar

#endif  // MIDISTAR_SONGNOTEPRACTICEMODECOMPONENT_H_
