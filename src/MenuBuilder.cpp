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
#include "midistar/MenuComponent.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/MenuItemBuilder.h"

namespace midistar {

MenuBuilder::MenuBuilder(sf::Font& font)
        : font_{ font }
        , title_text_{ nullptr }
        , result_{ new GameObject{ } }
        , y_{ 0 } {
    result_->SetPosition(0, y_);
    y_ += 150;
    result_->SetComponent(new MenuComponent{});
    result_->SetComponent(new MenuInputHandlerComponent{});
}

MenuBuilder& MenuBuilder::SetTitle(const std::string title) {
    result_->SetDrawformable(new sf::Text(title, font_, 100));
    return *this;
}

MenuItemBuilder MenuBuilder::AddItem(const std::string item_text) {
    auto result = MenuItemBuilder{ font_, item_text, 0.0, y_, *this, result_ };
    y_ += 50;
    return result;
}

GameObject* MenuBuilder::Create() {
    return result_;
}

}  // End namespace midistar
