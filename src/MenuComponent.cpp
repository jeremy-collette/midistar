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

#include "midistar/MenuComponent.h"

#include <cassert>

#include "midistar/MenuItemComponent.h"

namespace midistar {

MenuComponent::MenuComponent()
        : Component{ Component::MENU }
        , current_item_{ nullptr }
        , index_{ 0 }
        , previous_menu_{ nullptr } {
}

void MenuComponent::OnNextFocus() {
    ++index_;
}

void MenuComponent::OnPreviousFocus() {
    --index_;
}

void MenuComponent::OnSelect() {
    if (current_item_) {
        current_item_->OnSelect();
    }
}

void MenuComponent::OnBack(Game* g, GameObject* o, int delta) {
    if (!this->previous_menu_) {
        g->Exit();
        return;
    }

    // Remove existing menu
    o->SetEnabled(false);

    // Restore parent
    previous_menu_->SetEnabled(true);
}

void MenuComponent::SetPreviousMenu(GameObject* previous_menu) {
    previous_menu_ = previous_menu;
}

void MenuComponent::Update(Game* g, GameObject* o, int delta) {
    auto focused_item = GetChildMenuItemComponent(o);

    // If the focused item has changed, update focus
    if (current_item_ != focused_item) {
        if (current_item_) {
            current_item_->SetFocus(false);
        }

        if (focused_item) {
            focused_item->SetFocus(true);
        }
    }

    // Update focused item
    current_item_ = focused_item;
}

MenuItemComponent* MenuComponent::GetChildMenuItemComponent(GameObject* o) {
    // Get children with MenuItem components
    auto has_menu_item = std::vector<GameObject*>{ };

    for (const auto& child : o->GetChildren()) {
        if (child->HasComponent(Component::MENU_ITEM)) {
            has_menu_item.push_back(child);
        }
    }

    index_ = (index_ + has_menu_item.size()) % has_menu_item.size();
    auto menu_item_component = has_menu_item[index_]->GetComponent<
        MenuItemComponent>(Component::MENU_ITEM);

    assert(menu_item_component);
    return menu_item_component;
}

}  // End namespace midistar
