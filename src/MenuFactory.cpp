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

#include "midistar/MenuFactory.h"

namespace midistar {
MenuFactory::MenuFactory(
    const sf::Font& font
    , sf::RenderWindow* window)
        : font_{ font }
        , window_{ window } {
}

MenuBuilder MenuFactory::CreateMenu(
        const std::string title
        , float item_default_font_size) {
    return MenuBuilder{
        title
        , item_default_font_size
        , font_
        , window_
        , MENU_ITEM_PADDING };
}

MenuItemBuilder MenuFactory::CreateMenuItem(const std::string title) {
    return MenuItemBuilder{ title, font_ };
}

}  // End namespace midistar
