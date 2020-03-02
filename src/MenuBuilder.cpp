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

#include "midistar/SfmlEventsComponent.h"
#include "midistar/IntroSceneSfmlEventsHandlerComponent.h"

namespace midistar {

MenuBuilder::MenuBuilder(MenuItemBuilder* parent, sf::Font& font, MenuBuilderHeapFactory& factory, sf::RenderWindow& window)
        : factory_{factory}
        , font_{ font }
        , parent_{ *parent }
        , title_text_{ nullptr }
        , game_object_{ new GameObject{ } }
        , y_{ 0 } {
    game_object_->AddTag("Menu");
    game_object_->SetPosition(0, y_);
    y_ += 150;
    game_object_->SetComponent(new MenuComponent{});
    game_object_->SetComponent(new MenuInputHandlerComponent{});
    game_object_->AddTag("SfmlEvents");

    game_object_->SetComponent(new SfmlEventsComponent{ window });
    game_object_->SetComponent(new IntroSceneSfmlEventsHandlerComponent{ });
}

MenuBuilder& MenuBuilder::SetTitle(const std::string title) {
    game_object_->SetDrawformable(new sf::Text(title, font_, 100));
    return *this;
}

MenuItemBuilder MenuBuilder::AddItem(const std::string item_text) {
    auto result = MenuItemBuilder{ *this, font_, item_text, 0.0, y_, game_object_, factory_};
    y_ += 50;
    return result;
}

MenuItemBuilder& MenuBuilder::Done() {
    return parent_;
}

GameObject* MenuBuilder::Create() {
    return game_object_;
}

}  // End namespace midistar
