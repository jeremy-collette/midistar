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

#ifndef MIDISTAR_DELAYEDCOMPONENTCOMPONENT_H_
#define MIDISTAR_DELAYEDCOMPONENTCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The DelayedComponentComponent class allows a component to be added to the
 * owner after a supplied delay.
 */
class DelayedComponentComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param component The component to add.
     * \param delay The delay in milliseconds before adding the component.
     */
    DelayedComponentComponent(Component* component, int delay);

    /**
     * Sets the remaining delay until component is added.
     *
     * \param delay New remaining delay.
     */
    void SetRemainingDelay(int delay);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    Component* component_;  //!< The component to add after the delay.
    int delay_;  //!< The delay before the component is added.
};

}   // End namespace midistar

#endif  // MIDISTAR_DELAYEDCOMPONENTCOMPONENT_H_
