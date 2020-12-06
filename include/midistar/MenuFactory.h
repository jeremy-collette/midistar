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

#ifndef MIDISTAR_MENUFACTORY_H_
#define MIDISTAR_MENUFACTORY_H_

#include <string>
#include <SFML/Graphics.hpp>

#include "midistar/MenuBuilder.h"
#include "midistar/MenuItemBuilder.h"

namespace midistar {

/**
 * The MenuFactory class allows client to create a menu using a MenuBuilder and
 * MenuItemBuilders.
 */
class MenuFactory {
 public:
    /**
     * Constructor.
     *
     * \param font The font to use for the menu.
     * \param window The game window in use.
     */
    MenuFactory(
        const sf::Font& font
        , sf::RenderWindow* window);

    /**
     * Creates a MenuBuilder which creates a menu.
     *
     * \param title The title of the menu to create.
     * \param menu_item_default_size The font size of each item in the menu.
     *
     * \return A MenuBuilder which creates a menu.
     */
    MenuBuilder CreateMenu(
        const std::string title
        , int item_default_font_size = 20);

    /**
     * Creates a MenuItem which can be added to a menu.
     *
     * \param title The title of the menu item to create.
     *
     * \return A MenuItem which creates a menu item.
     */
    MenuItemBuilder CreateMenuItem(
        const std::string title);

 private:
    const int MENU_ITEM_PADDING = 10;

    const sf::Font& font_;
    sf::RenderWindow* window_;
};

}  // namespace midistar

#endif  // MIDISTAR_MENUFACTORY_H_
