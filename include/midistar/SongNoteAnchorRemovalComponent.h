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

#ifndef MIDISTAR_SONGNOTEANCHORREMOVALCOMPONENT_H_
#define MIDISTAR_SONGNOTEANCHORREMOVALCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace Midistar {

/**
 * The SongNoteAnchorRemovalComponent is used by MIDI off notes to stop the
 * note expansion of MIDI on notes that have the same MIDI key (note).
 */
class SongNoteAnchorRemovalComponent : public Component {
 public:
    /**
     * Constructor.
     */
    SongNoteAnchorRemovalComponent();

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o);
};

}   // End namespace Midistar

#endif  // MIDISTAR_SONGNOTEANCHORREMOVALCOMPONENT_H_
