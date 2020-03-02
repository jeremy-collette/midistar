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
#include "midistar/MenuBuilderHeapFactory.h"
#include "midistar/MenuItemComponent.h"

namespace midistar {

MenuItemBuilder::MenuItemBuilder(
    MenuBuilder& parent
    , sf::Font& font
    , const std::string item_text
    , double x_pos
    , double y_pos
    , GameObject* menu_game_object
    , MenuBuilderHeapFactory& menu_builder_factory)
        : font_{ font }
        , parent_{ parent }
        , menu_builder_factory_{ menu_builder_factory }
        , menu_game_object_{ menu_game_object }
        , menu_item_component_{ nullptr } {

    auto text = new sf::Text{ item_text, font, 30U };
    auto child_object = new GameObject{ text, x_pos, y_pos, 1, 1 };
    menu_item_component_ = new MenuItemComponent{ };
    child_object->SetComponent(menu_item_component_);
    menu_game_object->AddChild(child_object);
}

MenuItemBuilder& MenuItemBuilder::SetOnSelect(std::function<void(Game*
        , GameObject*, int)> on_select_func) {
    menu_item_component_->SetOnSelect(on_select_func);
    return *this;
}

MenuBuilder& MenuItemBuilder::CreateSubMenu() {
    auto& menu_builder = menu_builder_factory_.Create(*this, font_);
    auto sub_menu_game_object = menu_builder.Create();
    menu_item_component_->SetOnSelect(
        [sub_menu_game_object](Game* g, GameObject* o, int delta)
        {
            auto current_menu = g->GetCurrentScene().GetFirstGameObjectByTag("Menu");
            current_menu->SetRequestDelete(true);
            g->GetCurrentScene().AddGameObject(sub_menu_game_object);
        }
    );
    return menu_builder;
}

MenuBuilder& MenuItemBuilder::Done() {
    return parent_;
}

}  // End namespace midistar
