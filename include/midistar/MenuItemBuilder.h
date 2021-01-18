/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#ifndef MIDISTAR_MENUITEMBUILDER_H_
#define MIDISTAR_MENUITEMBUILDER_H_

#include <functional>
#include <string>

#include "midistar/Game.h"
#include "midistar/GameObject.h"
#include "midistar/MenuItemComponent.h"
#include "midistar/TextFactory.h"

namespace midistar {

class MenuBuilder;

class MenuItemBuilder {
 public:
     MenuItemBuilder(
         const std::string text
         , const sf::Font& font);

     GameObject* GetGameObject() const;

     MenuItemBuilder& SetFontSize(const int size);

     MenuItemBuilder& SetOnSelect(const MenuBuilder& sub_menu);

     MenuItemBuilder& SetOnSelect(std::function<void(Game*, GameObject*, int)>
         on_select_func);

     void SetOwningMenu(GameObject* parent);

     void SetPosition(const double x_pos, const double y_pos);

 private:
     GameObject* game_object_;
     MenuItemComponent* menu_item_component_;
     GameObject* parent_menu_;
     TextFactory text_factory_;
};

}  // namespace midistar

#endif  // MIDISTAR_MENUITEMBUILDER_H_
