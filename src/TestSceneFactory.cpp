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

#include "midistar/TestSceneFactory.h"

#include "midistar/IntroSceneSfmlEventsHandlerComponent.h"
#include "midistar/MenuBuilder.h"
#include "midistar/MenuBuilderHeapFactory.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/MenuFactory.h"

namespace midistar {

bool TestSceneFactory::Create(
        Game* game
        , sf::RenderWindow& render_window
        , Scene** scene) {

    auto font = new sf::Font();
    if (!font->loadFromFile("PixelMiners-KKal.otf")) {
        throw "Could not load font!";
    }

    auto factory = MenuFactory{ *font, render_window };
    auto menu_context =
        factory.CreateMenu("Test Menu")
        .SetTitleColour(sf::Color::Green)
        .AddMenuItem(factory.CreateMenuItem("Birbs")
            .SetOnSelect(factory.CreateMenu("Birbs Menu")
                .AddMenuItem(factory.CreateMenuItem("Cockatoo"))
                .AddMenuItem(factory.CreateMenuItem("Gallah")
                    .SetOnSelect(factory.CreateMenu("Rosella")
                        .AddMenuItem(factory.CreateMenuItem("Eastern Rosella"))
                        .AddMenuItem(factory.CreateMenuItem("Crimson Rosella"))))))
        .AddMenuItem(factory.CreateMenuItem("Start Game")
            .SetOnSelect([](Game* g, GameObject*, int) {
                g->SetScene("Intro");
            }))
        .AddMenuItem(factory.CreateMenuItem("Exit")
            .SetOnSelect([](Game* g, GameObject*, int) {
                g->Exit();
            }));

    auto game_objects = std::vector<GameObject*>{ menu_context.GetGameObject() };
    *scene = new Scene{ game, render_window, game_objects };
    return true;
}

}   // End namespace midistar

