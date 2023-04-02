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

#include "midistar/MenuBuilder.h"
#include "midistar/MenuItemBuilder.h"
#include "midistar/MenuComponent.h"

namespace midistar {
MenuItemBuilder::MenuItemBuilder(
    const std::string text
    , const sf::Font& font)
        : game_object_{ nullptr }
        , parent_menu_{ nullptr }
        , text_factory_{ text, font } {
    menu_item_component_ = new MenuItemComponent{ };
    text_factory_.SetFontSize(25);
    game_object_ = text_factory_.GetGameObject();
    game_object_->SetComponent(menu_item_component_);
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(
        const MenuBuilder& sub_menu) {
    auto new_submenu_object = sub_menu.GetGameObject();
    // Disable the sub menu until we're ready to show it
    new_submenu_object->SetEnabled(false);

    menu_item_component_->SetOnSelect(
        [this, new_submenu_object](
                Game* g
                , GameObject* o
                , int d) {

            // Remove existing menu
            auto menu_item = o->GetComponent<MenuItemComponent>(
                Component::MENU_ITEM);

            // Here we remove the current menu
            auto parent_menu = menu_item->GetParentMenuGameObject();
            parent_menu->SetEnabled(false);

            // Set new menu and enable it
            auto new_submenu = new_submenu_object->GetComponent<
                MenuComponent>(Component::MENU);
            new_submenu->SetPreviousMenu(parent_menu);
            new_submenu_object->SetEnabled(true);
        });
    return *this;
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(
        std::function<void(Game*, GameObject*, int)> on_select_func) {
    menu_item_component_->SetOnSelect(on_select_func);
    return *this;
}

void MenuItemBuilder::SetOwningMenu(GameObject* parent) {
    menu_item_component_->SetParentMenuGameObject(parent);
}

void MenuItemBuilder::SetPosition(const double x_pos, const double y_pos) {
    text_factory_.SetXPosition(x_pos);
    text_factory_.SetYPosition(y_pos);
}

GameObject* MenuItemBuilder::GetGameObject() const {
    return game_object_;
}

MenuItemBuilder& MenuItemBuilder::SetFontSize(const int size) {
    text_factory_.SetFontSize(size);
    return *this;
}

}  // End namespace midistar
