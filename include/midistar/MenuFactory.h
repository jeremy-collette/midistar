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

class MenuFactory {
 public:
    MenuFactory(
        const sf::Font& font
        , sf::RenderWindow* window);

    MenuBuilder CreateMenu(
        const std::string title
        , float menu_item_size = 20.0f);

    MenuItemBuilder CreateMenuItem(
        const std::string title);

 private:
    const float MENU_ITEM_PADDING = 10.0f;

    const sf::Font& font_;
    sf::RenderWindow* window_;
};

}  // namespace midistar

#endif  // MIDISTAR_MENUFACTORY_H_
