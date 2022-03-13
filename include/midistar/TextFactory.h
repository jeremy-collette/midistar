/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
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

#ifndef MIDISTAR_TEXTFACTORY_H_
#define MIDISTAR_TEXTFACTORY_H_

#include <string>

#include "midistar/GameObject.h"

namespace midistar {

class TextFactory {
 public:
    enum TextPosition {
        CENTER,
        MIN,
        MAX
    };

    TextFactory(
        const std::string content
        , const sf::Font& font);

    TextFactory& SetColour(const sf::Color color);

    TextFactory& SetFontSize(unsigned int size);

    TextFactory& SetXPosition(double pos);

    TextFactory& SetYPosition(double pos);

    TextFactory& SetXPosition(TextPosition pos, double offset = 0);

    TextFactory& SetYPosition(TextPosition pos, double offset = 0);

    GameObject* GetGameObject();

 private:
    const sf::Font& font_;
    GameObject* game_object_;
    sf::Text* text_;
};

}  // namespace midistar

#endif  // MIDISTAR_TEXTFACTORY_H_
