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

#include "midistar/MenuItemBuilder.h"

#include "midistar/Game.h"
#include "midistar/MenuBuilder.h"
#include "midistar/MenuItemComponent.h"

namespace midistar {

MenuItemBuilder::MenuItemBuilder(
    sf::Font& font
    , const std::string item_text
    , double x_pos
    , double y_pos
    , MenuBuilder& menu_builder
    , GameObject* menu_game_object)
        : font_{ font }
        , menu_builder_{ menu_builder }
        , menu_game_object_{ menu_game_object }
        , result_{ nullptr } {

    auto text = new sf::Text{ item_text, font, 30U };
    auto child_object = new GameObject{ text, x_pos, y_pos, 1, 1 };
    result_ = new MenuItemComponent{ };
    child_object->SetComponent(result_);
    menu_game_object->AddChild(child_object);
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(std::function<void(Game*
        , GameObject*, int)> on_select_func) {
    result_->SetOnSelect(on_select_func);
    return *this;
}

MenuBuilder& MenuItemBuilder::Create() {
    return menu_builder_;
}

}  // End namespace midistar
