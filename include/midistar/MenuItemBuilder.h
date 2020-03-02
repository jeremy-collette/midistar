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

#ifndef MIDISTAR_MENUITEMBUILDER_H_
#define MIDISTAR_MENUITEMBUILDER_H_

#include <functional>

#include "midistar/GameObject.h"
#include "midistar/MenuItemComponent.h"

namespace midistar {

// Forward declaration to prevent circular dependency
class MenuBuilder;
class MenuBuilderHeapFactory;

class MenuItemBuilder {
 public:
     MenuItemBuilder(
         MenuBuilder& parent
         , sf::Font& font
         , const std::string item_text
         , double x_pos
         , double y_pos
         , GameObject* menu_game_object
         , MenuBuilderHeapFactory& menu_builder_factory);

     MenuItemBuilder& SetOnSelect(std::function<void(Game*, GameObject*, int)>
        on_select_func);

     MenuBuilder& CreateSubMenu();

     MenuBuilder& Done();

 private:
     sf::Font& font_;
     MenuBuilderHeapFactory& menu_builder_factory_;
     GameObject* menu_game_object_;
     MenuBuilder& parent_;
     MenuItemComponent* menu_item_component_;
};

}  // namespace midistar

#endif  // MIDISTAR_MENUCOMPONENT_H_
