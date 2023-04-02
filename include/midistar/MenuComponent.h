/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

#ifndef MIDISTAR_MENUCOMPONENT_H_
#define MIDISTAR_MENUCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"
#include "midistar/MenuItemComponent.h"

namespace midistar {

/**
 * The MenuComponent class creates a text menu.
 */
class MenuComponent : public Component {
 public:
    /**
     * Constructor.
     */
    MenuComponent();

    void OnNextFocus();

    void OnPreviousFocus();

    void OnSelect();

    void OnBack(Game* g, GameObject* o, int delta);

    void SetPreviousMenu(GameObject* parent);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
     MenuItemComponent* GetChildMenuItemComponent(GameObject* o);  //!< Gets
       //!< menu item component from child GameObject at index

     MenuItemComponent* current_item_;  //!< Currently focused item
     int index_;  //!< Menu index
     GameObject* previous_menu_;  //!< Menu that brought us here
};

}  // namespace midistar

#endif  // MIDISTAR_MENUCOMPONENT_H_
