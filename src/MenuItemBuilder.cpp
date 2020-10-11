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

#include "midistar/MenuBuilder.h"
#include "midistar/MenuItemBuilder.h"
#include "midistar/MenuComponent.h"

namespace midistar {
MenuItemBuilder::MenuItemBuilder(
    const std::string text
    , GameObject* game_object
    , const sf::Font& font)
        : game_object_{ game_object }
        , parent_menu_{ nullptr } {
    menu_item_component_ = new MenuItemComponent{ };
    game_object_->SetComponent(menu_item_component_);
    game_object_->SetDrawformable(new sf::Text{ text, font, 50U });
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(MenuBuilder& sub_menu) {
    auto new_submenu_object = sub_menu.GetGameObject();

    menu_item_component_->SetOnSelect(
        [this, new_submenu_object](Game* g, GameObject* o, int delta) {
            // Remove existing menu
            auto menu_item = o->GetComponent<MenuItemComponent>(
                Component::MENU_ITEM);

            // Here we remove the current menu
            // TODO(@jez): can we do this somewhere else?
            auto owning_menu = menu_item->GetOwningMenu();
            g->GetCurrentScene().RemoveObject(owning_menu);

            // Set new menu and tell it the current menu so it can go back
            auto new_submenu = new_submenu_object->GetComponent<
                MenuComponent>(Component::MENU);
            new_submenu->SetPreviousMenu(owning_menu);
            g->GetCurrentScene().AddGameObject(new_submenu_object);
        });
    return *this;
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(
        std::function<void(Game*, GameObject*, int)> on_select_func) {
    menu_item_component_->SetOnSelect(on_select_func);
    return *this;
}

void MenuItemBuilder::SetOwningMenu(GameObject* parent) {
    menu_item_component_->SetOwningMenu(parent);
}

void MenuItemBuilder::SetPosition(const double x_pos, const double y_pos) {
    game_object_->SetPosition(x_pos, y_pos);
}

GameObject* MenuItemBuilder::GetGameObject() {
    return game_object_;
}

MenuItemBuilder& MenuItemBuilder::SetFontSize(const int size) {
    game_object_->GetDrawformable<sf::Text>()->setCharacterSize(size);
    return *this;
}

}  // End namespace midistar
