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

// Remove
#include <iostream>

#include "midistar/MenuBuilder.h"
#include "midistar/MenuItemBuilder.h"

namespace midistar {
MenuItemBuilder::MenuItemBuilder(
    const std::string text
    , GameObject* game_object
    , const sf::Font& font)
        : game_object_{ game_object } {
    menu_item_component_ = new MenuItemComponent{ };
    game_object_->SetComponent(menu_item_component_);
    game_object_->SetDrawformable(new sf::Text{ text, font, 30U });
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(MenuBuilder& sub_menu) {
    auto sub_menu_object = sub_menu.GetGameObject();

    menu_item_component_->SetOnSelect(
        [this, sub_menu_object](Game* g, GameObject* o, int delta)
        {
            // TODO(@jez): How do we get back?
            auto current_menu = g->GetCurrentScene().GetFirstGameObjectByTag("Menu");
            current_menu->SetRequestDelete(true);

            //game_object_->SetRequestDelete(true);
            //auto text = game_object_->GetDrawformable<sf::Text>();
            //text->setCharacterSize(0);

            g->GetCurrentScene().AddGameObject(sub_menu_object);
        }
    );
    return *this;
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(
        std::function<void(Game*, GameObject*, int)> on_select_func) {
    menu_item_component_->SetOnSelect(on_select_func);
    return *this;
}

MenuItemBuilder& MenuItemBuilder::SetYPosition(const double y_pos) {
    double x, y;
    game_object_->GetPosition(&x, &y);
    y = y_pos;
    game_object_->SetPosition(x, y);
    return *this;
}

GameObject* MenuItemBuilder::GetGameObject() {
    return game_object_;
}

}  // End namespace midistar
