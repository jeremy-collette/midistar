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

#ifndef MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_
#define MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/GraphicsComponent.h"

namespace midistar {

/**
 * The InstrumentInputHandlerComponent handles input for instruments.
 *
 * More specifically, it polls keyboard and MIDI input port events and
 * activates the instrument when applicable. While active, the instrument is
 * visible and plays a MIDI note.
 */
class InstrumentInputHandlerComponent : public Component {
 public:
     /**
      * Constructor.
      */
     InstrumentInputHandlerComponent();

     /**
      * Allows other components to activate instrument.
      *
      * \param active True activates instrument. False leaves instrument
      * unchanged.
      */
     void SetActive(bool active);

     /**
      * \copydoc Component::Update()
      */
     virtual void Update(Game* g, GameObject* o, int delta);


 private:
     sf::Keyboard::Key key_;  //!< Holds the key that was pressed to activate
                                                            //!< the instrument
     bool key_down_;  //!< Determines if the instrument is currently activated
     bool set_active_;  //!< Determines if the instrument has been activated 
                                                                //!< externally
};

}  // End namespace midistar

#endif  // MIDISTAR_INSTRUMENTINPUTHANDLERCOMPONENT_H_
