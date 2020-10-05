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

#include "midistar/IntroSceneSfmlEventsHandlerComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/TextFactory.h"

namespace midistar {

MenuBuilder::MenuBuilder(
    const std::string title,
    const float menu_item_y_gap,
    GameObject* game_object,
    const sf::Font& font,
    sf::RenderWindow& window)
        : menu_item_y_gap_{ menu_item_y_gap }
        , game_object_{ game_object }
        , font_{ font }
        , y_{ 0 } {
    game_object_->SetDrawformable(new sf::Text(title, font_, 100));

    game_object_->AddTag("Menu");
    game_object_->SetPosition(0, y_);
    y_ += 150;
    game_object_->SetComponent(new MenuComponent{ });
    game_object_->SetComponent(new MenuInputHandlerComponent{ });

    game_object_->AddTag("SfmlEvents");
    game_object_->SetComponent(new SfmlEventsComponent{ window });
}

MenuBuilder& MenuBuilder::AddMenuItem(MenuItemBuilder& menu_item) {
    menu_item.SetOwningMenu(game_object_);
    game_object_->AddChild(menu_item.GetGameObject());
    menu_item.SetPosition(50.0, y_);
    y_ += menu_item_y_gap_;
    return *this;
}

GameObject* MenuBuilder::GetGameObject() {
    return game_object_;
}

MenuBuilder& MenuBuilder::SetTitleColour(sf::Color colour) {
    game_object_->GetDrawformable<sf::Text>()->setFillColor(colour);
    return *this;
}

MenuBuilder& MenuBuilder::SetTitleFontSize(int size) {
    game_object_->GetDrawformable<sf::Text>()->setCharacterSize(size);
    return *this;
}

}  // End namespace midistar
