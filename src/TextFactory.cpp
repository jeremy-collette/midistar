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

#include "midistar/TextFactory.h"

#include "midistar/Config.h"
#include "midistar/KeepAliveComponent.h"

namespace midistar {

TextFactory::TextFactory(
    const std::string content
    , const sf::Font& font)
        : font_{ font }
        , game_object_{ nullptr }
        , text_{ nullptr }
{
    text_ = new sf::Text{ content, font, 25 };
    auto text_bounds = text_->getLocalBounds();
    game_object_ = new GameObject{ text_, 0, 0, text_bounds.width
        , text_bounds.height };
    game_object_->SetComponent(new KeepAliveComponent{ });
}

TextFactory& TextFactory::SetColour(const sf::Color color) {
    text_->setFillColor(color);
    return *this;
}

TextFactory& TextFactory::SetFontSize(unsigned int size) {
    text_->setCharacterSize(size);
    auto bounds = text_->getLocalBounds();
    game_object_->SetSize(bounds.width, bounds.height);
    return *this;
}

TextFactory& TextFactory::SetXPosition(double pos) {
    double cur_x, cur_y;
    game_object_->GetPosition(&cur_x, &cur_y);
    game_object_->SetPosition(pos, cur_y);
    return *this;
}

TextFactory& TextFactory::SetYPosition(double pos) {
    double cur_x, cur_y;
    game_object_->GetPosition(&cur_x, &cur_y);
    game_object_->SetPosition(cur_x, pos);
    return *this;
}

TextFactory& TextFactory::SetXPosition(TextPosition pos, double offset) {
    auto text_bounds = text_->getLocalBounds();
    if (pos == TextPosition::CENTER) {
        double x = (Config::GetInstance().GetScreenWidth() / 2.0f)
            - (text_bounds.width / 2.0f);
        x += offset;
        SetXPosition(x);
    } else if (pos == TextPosition::MAX) {
        double x = (Config::GetInstance().GetScreenWidth()) - text_bounds.width;
        x += offset;
        SetXPosition(x);
    } else if (pos == TextPosition::MIN) {
        SetXPosition(offset);
    } else {
        throw "TextPosition not supported.";
    }
    return *this;
}

TextFactory& TextFactory::SetYPosition(TextPosition pos, double offset) {
    auto text_bounds = text_->getLocalBounds();
    if (pos == TextPosition::CENTER) {
        double y = (Config::GetInstance().GetScreenHeight() / 2.0f)
            - (text_bounds.height / 2.0f);
        y += offset;
        SetYPosition(y);
    } else if (pos == TextPosition::MAX) {
        double y = (Config::GetInstance().GetScreenHeight())
            - text_bounds.height;
        y += offset;
        SetYPosition(y);
    } else if (pos == TextPosition::MIN) {
        SetYPosition(offset);
    } else {
        throw "TextPosition not supported.";
    }
    return *this;
}

GameObject* TextFactory::GetGameObject() {
    return game_object_;
}

}  // End namespace midistar
