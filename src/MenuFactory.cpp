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
MenuFactory::MenuFactory(const sf::Font& font, sf::RenderWindow & window)
    : font_{ font }
    , window_{ window } {
}

MenuBuilder MenuFactory::CreateMenu(
        const std::string title
        , float menu_item_y_gap) {
    auto game_object = new GameObject{ (sf::Text*)nullptr, 0.0, 0.0, 0.0, 0.0 };
    return MenuBuilder{ title, menu_item_y_gap, game_object, font_, window_ };
}

MenuItemBuilder MenuFactory::CreateMenuItem(const std::string title) {
    auto game_object = new GameObject{ (sf::Text*)nullptr, 0.0, 0.0, 0.0, 0.0 };
    return MenuItemBuilder{ title, game_object, font_ };
}

}  // End namespace midistar
