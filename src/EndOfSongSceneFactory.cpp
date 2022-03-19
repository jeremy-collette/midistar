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

#include "midistar/EndOfSongSceneFactory.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>

#include "midistar/Constants.h"
#include "midistar/EndOfSongSfmlEventsHandlerComponent.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/TextFactory.h"

namespace midistar {

bool EndOfSongSceneFactory::Create(
        Game* game
        , sf::RenderWindow* render_window
        , Scene** scene
        , int score) {

    // TODO(@jez): load fonts higher up and pass down where needed. Then clean-
    // up on exit.
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        std::cerr << "Could not load font \"" << MIDISTAR_FONT << "\"!\n";
        return false;
    }

    auto game_objects = std::vector<GameObject*>();

    auto song_complete_text_factory = TextFactory{ "Song complete!", *font };
    song_complete_text_factory.SetXPosition(TextFactory::CENTER);
    song_complete_text_factory.SetYPosition(TextFactory::CENTER);
    auto song_complete_game_object = song_complete_text_factory.GetGameObject();

    song_complete_game_object->SetComponent(new SfmlEventsComponent{ render_window });
    song_complete_game_object->AddTag("SfmlEvents");
    song_complete_game_object->SetComponent(
        new EndOfSongSongSfmlEventsHandlerComponent{});

    auto ss = std::stringstream();
    ss << "Score: " << score;
    auto score_text_factory = TextFactory{ ss.str(), *font };
    score_text_factory.SetXPosition(TextFactory::CENTER);
    score_text_factory.SetYPosition(TextFactory::CENTER, 30.0);
    auto score_game_object = score_text_factory.GetGameObject();

    auto press_enter_text_factory = TextFactory{ "Press enter to continue."
        , *font };
    press_enter_text_factory.SetXPosition(TextFactory::CENTER);
    press_enter_text_factory.SetYPosition(TextFactory::CENTER, 60.0);
    auto press_enter_game_object = press_enter_text_factory.GetGameObject();

    game_objects.push_back(song_complete_game_object);
    game_objects.push_back(score_game_object);
    game_objects.push_back(press_enter_game_object);
    *scene = new Scene{ game, render_window, game_objects};
    return true;
}

}   // End namespace midistar

