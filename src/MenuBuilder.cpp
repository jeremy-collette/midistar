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

#include "midistar/IntroSceneSfmlEventsHandlerComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/SfmlEventsComponent.h"

namespace midistar {

MenuBuilder::MenuBuilder(
    const std::string title,
    const int item_default_font_size,
    const sf::Font& font,
    sf::RenderWindow* window,
    const int item_padding)
        : font_{ font }
        , game_object_{ nullptr }
        , item_default_font_size_{ item_default_font_size }
        , item_padding_{ item_padding }
        , title_text_factory_{ title, font }
        , y_{ 0 } {
    title_text_factory_.SetFontSize(50);
    title_text_factory_.SetColour(sf::Color::White);
    title_text_factory_.SetXPosition(TextFactory::MIN);
    title_text_factory_.SetYPosition(y_);
    y_ += 150;

    game_object_ = title_text_factory_.GetGameObject();
    game_object_->AddTag("Menu");
    game_object_->SetComponent(new MenuComponent{ });
    game_object_->SetComponent(new MenuInputHandlerComponent{ });
    game_object_->AddTag("SfmlEvents");
    game_object_->SetComponent(new SfmlEventsComponent{ window });
}

MenuBuilder& MenuBuilder::AddMenuItem(MenuItemBuilder menu_item) {
    menu_item.SetOwningMenu(game_object_);
    auto menu_item_game_object = menu_item.GetGameObject();
    game_object_->AddChild(menu_item_game_object);
    menu_item.SetPosition(50.0, y_);
    menu_item.SetFontSize(item_default_font_size_);
    auto menu_item_y_size = menu_item_game_object->GetDrawformable<sf::Text>()
        ->getGlobalBounds().height;
    y_ += menu_item_y_size + item_padding_;
    return *this;
}

GameObject* MenuBuilder::GetGameObject() const {
    return game_object_;
}

MenuBuilder& MenuBuilder::SetTitleColour(sf::Color colour) {
    title_text_factory_.SetColour(colour);
    return *this;
}

MenuBuilder& MenuBuilder::SetTitleFontSize(int size) {
    title_text_factory_.SetFontSize(size);
    return *this;
}

}  // End namespace midistar
