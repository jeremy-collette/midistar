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

#ifndef MIDISTAR_MENUBUILDER_H_
#define MIDISTAR_MENUBUILDER_H_

#include <string>

#include "midistar/GameObject.h"
#include "midistar/MenuItemBuilder.h"
#include "midistar/TextFactory.h"

namespace midistar {

class MenuBuilder {
 public:
    MenuBuilder(
        const std::string title
        , const int item_default_font_size
        , const sf::Font& font
        , sf::RenderWindow* window
        , const int item_padding);

    MenuBuilder& AddMenuItem(MenuItemBuilder menu_item);

    GameObject* GetGameObject() const;

    MenuBuilder& SetTitleColour(sf::Color colour);

    MenuBuilder& SetTitleFontSize(int size);

 private:
    const sf::Font& font_;
    GameObject* game_object_;
    const int item_default_font_size_;
    const int item_padding_;
    TextFactory title_text_factory_;
    float y_;
};

}  // namespace midistar

#endif  // MIDISTAR_MENUBUILDER_H_
