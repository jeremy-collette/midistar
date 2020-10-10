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

#include "midistar/MenuItemComponent.h"

#include <iostream>

#include "midistar/Game.h"

namespace midistar {

MenuItemComponent::MenuItemComponent(
    std::function<void(Game*, GameObject*, int)> on_select)
        : Component{ Component::MENU_ITEM }
        , has_focus_{ false }
        , on_select_{ on_select }
        , selected_{ false } {
}

MenuItemComponent::MenuItemComponent()
        : MenuItemComponent([](Game*, GameObject*, int) {}) {
}

void MenuItemComponent::OnSelect()
{
    // TODO(@jeremy): remove
    //std::cout << "Selected menu item: " << text_ << std::endl;
    selected_ = true;
}

void MenuItemComponent::SetFocus(bool has_focus)
{
    // TODO(@jeremy): remove
    //std::cout << "Menu item: " << text_ << " focus: " << has_focus << std::endl;
    has_focus_ = has_focus;
}

void MenuItemComponent::SetOnSelect(
        std::function<void(Game*, GameObject*, int)> on_select) {
    on_select_ = on_select;
}

void MenuItemComponent::Update(Game* g, GameObject* o, int delta)
{
    auto text = o->GetDrawformable<sf::Text>();
    auto color = has_focus_ ? sf::Color::White : sf::Color::Red;
    text->setFillColor(color);

    if (selected_) {
        selected_ = false;
        on_select_(g, o, delta);
    }
}

GameObject* MenuItemComponent::GetOwningMenu() {
    return parent_;
}

void MenuItemComponent::SetOwningMenu(GameObject* parent) {
    parent_ = parent;
}

}  // End namespace midistar
