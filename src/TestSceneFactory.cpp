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

namespace midistar {

bool TestSceneFactory::Create(
        Game* game
        , sf::RenderWindow& render_window
        , Scene** scene) {

    auto font = new sf::Font();
    if (!font->loadFromFile("PixelMiners-KKal.otf")) {
        throw "Could not load font!";
    }

    auto menu_builder_factory = MenuBuilderHeapFactory{ render_window };
    auto menu_builder = menu_builder_factory.Create(*font);

    auto menu = menu_builder
        .SetTitle("Test Menu")
        .AddItem("Test Item")
            .Done()
        .AddItem("Test Item 2")
        .SetOnSelect([](Game* g, GameObject*, int) {
            g->SetScene("Intro");
        })
            .Done()
        .AddItem("Test Item 3")
            .CreateSubMenu()
            .SetTitle("Sub menu!")
            .AddItem("Hello")
                .Done()
            .AddItem("Workd")
                .SetOnSelect([](Game* g, GameObject*, int) {
                    g->SetScene("Test");
                })
                .Done()
            .Done()
        .Done()
        .Create();

    auto game_objects = std::vector<GameObject*>{ menu };
    *scene = new Scene{ game, render_window, game_objects };
    return true;
}

}   // End namespace midistar

