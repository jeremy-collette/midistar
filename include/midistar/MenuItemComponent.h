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

#ifndef MIDISTAR_MENUITEMCOMPONENT_H_
#define MIDISTAR_MENUITEMCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The MenuComponent class creates a text menu.
 */
class MenuItemComponent : public Component {
 public:
    /**
     * Constructor.
	 *
	 * \param text The text to display.
     */
	MenuItemComponent(std::string text);

	void OnSelect();

	void SetFocus(bool has_focus);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
	 bool has_focus_;  //!< Indicates if this menu item currently has focus
	 bool selected_;  //!< Indicates this item was selected
	 std::string text_;  //!< Holds menu item text
};

}  // namespace midistar

#endif  // MIDISTAR_MENUCOMPONENT_H_
