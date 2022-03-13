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

#include "midistar/ScoreManagerFactory.h"

#include <iostream>

#include "midistar/Constants.h"
#include "midistar/TextFactory.h"
#include "midistar/ScoreManagerComponent.h"

namespace midistar {

bool ScoreManagerFactory::CreateScoreManager(GameObject** game_object_out) {
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        std::cerr << "Could not load font \"" << MIDISTAR_FONT << "\"!\n";
        return false;
    }

    const auto text = std::string{ "Score: 0" };
    auto text_factory = TextFactory{ text, *font };

    text_factory
        .SetXPosition(0)
        .SetYPosition(0)
        .SetColour(sf::Color::White);

    auto game_object = text_factory.GetGameObject();
    game_object->AddTag("ScoreManager");
    auto score_manager = new ScoreManagerComponent{};
    game_object->SetComponent(score_manager);

    *game_object_out = text_factory.GetGameObject();
    return true;
}

}   // End namespace midistar
