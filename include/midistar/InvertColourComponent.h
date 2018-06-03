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

#ifndef MIDISTAR_INVERTCOLOURCOMPONENT_H_
#define MIDISTAR_INVERTCOLOURCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"
#include "midistar/TransformComponent.h"

namespace midistar {

/*
 * The InvertColourComponent inverts the colour of the owner's 
 * GraphicsComponent. 
 */
class InvertColourComponent : public TransformComponent {
 public:
    /**
     * Constructor. 
     *
     * \param x The value to XOR with each RGB value for inversion.
     */
    InvertColourComponent(char x);

    /**
     * Default constructor.
     */
    InvertColourComponent();

 private:
    char xor_;  //!< Value used for inversion
};

}   // End namespace midistar

#endif  // MIDISTAR_INVERTCOLOURCOMPONENT_H_
