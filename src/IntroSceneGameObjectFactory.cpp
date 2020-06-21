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

#include "midistar/IntroSceneGameObjectFactory.h"

#include <filesystem>
#include <string>

#include "midistar/DrumSceneFactory.h"
#include "midistar/Game.h"
#include "midistar/KeepAliveComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuFactory.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/MenuItemComponent.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/Version.h"

namespace fs = std::experimental::filesystem;

namespace midistar {

// TODO(@jeremy): this should be in the scene factory
IntroSceneGameObjectFactory::IntroSceneGameObjectFactory() {
}

std::vector<GameObject*> IntroSceneGameObjectFactory::CreateGameObjects(sf::RenderWindow& window) {
    // TODO(@jeremy): add font to project
    // TODO(@jeremy): resize based on screen size

    // Create menu
    auto font = new sf::Font();
    if (!font->loadFromFile("PixelMiners-KKal.otf")) {
        throw "Could not load font!";
    }

    auto factory = MenuFactory{ *font, window };
    auto piano_menu = factory.CreateMenu("Song selection", 25.0f)
        .SetTitleFontSize(50);
    auto drum_menu = factory.CreateMenu("Song selection", 25.0f)
        .SetTitleFontSize(50);

    // TODO(@jeremy): add subtitle functionality to menu builder
    auto subtitle = new sf::Text("Scanning directory " + fs::current_path()
        .string(), *font, 20);
    subtitle->setFillColor(sf::Color::White);
    auto subtitle_game_object = new GameObject{ subtitle, 0, 80, 20, 20 };
    subtitle_game_object->SetComponent(new KeepAliveComponent{ });
    piano_menu.GetGameObject()->AddChild(subtitle_game_object);
    drum_menu.GetGameObject()->AddChild(subtitle_game_object);

    // Add menu items
    auto menu_item_text = std::vector<std::string*>{ };
    std::string path = ".";
    for (const auto & entry : fs::directory_iterator(path)) {
        auto path_string = entry.path().string();
        if (path_string.find(".mid") != std::string::npos) {
            piano_menu.AddMenuItem(
                factory.CreateMenuItem(path_string)
                    .SetOnSelect(([path_string](Game* g, GameObject*, int) {
                        Scene* new_scene = nullptr;
                        auto piano_scene_factory = PianoSceneFactory{};
                        if (!piano_scene_factory.Create(
                            g
                            , g->GetWindow()
                            , path_string
                            , &new_scene)) {
                            throw "Scene creation failed";
                        }
                        g->SetScene(new_scene);
                    }))
                    .SetFontSize(20));

            drum_menu.AddMenuItem(
                factory.CreateMenuItem(path_string)
                .SetOnSelect(([path_string](Game* g, GameObject*, int) {
                    Scene* new_scene = nullptr;
                    auto drum_scene_factory = DrumSceneFactory{};
                    if (!drum_scene_factory.Create(
                        g
                        , g->GetWindow()
                        , path_string
                        , &new_scene)) {
                        throw "Scene creation failed";
                    }
                    g->SetScene(new_scene);
                }))
                .SetFontSize(20));
        }
    }

    auto main_menu =
        factory.CreateMenu("midistar")
        .SetTitleColour(sf::Color::Green)
        .AddMenuItem(factory.CreateMenuItem("1. Piano")
            .SetOnSelect(piano_menu))
        .AddMenuItem(factory.CreateMenuItem("2. Drums")
            .SetOnSelect(drum_menu))
        .AddMenuItem(factory.CreateMenuItem("0. Exit")
            .SetOnSelect([](Game* g, GameObject*, int) {
                g->Exit();
            }));

    auto copyright_string = new std::string{
        "Copyright (c) Jeremy Collette 2018-2020" };
    auto copyright_text = new sf::Text(*copyright_string, *font, 25);
    copyright_text->setFillColor(sf::Color::White);
    auto copyright = new GameObject{ copyright_text, 150, 650, 20, 20 };
    copyright->SetComponent(new KeepAliveComponent{ });
    main_menu.GetGameObject()->AddChild(copyright);

    auto version_string = new std::string{ MIDISTAR_VERSION };
    auto version_text = new sf::Text(*version_string, *font, 25);
    auto version = new GameObject{ version_text, 900, 720, 20, 20 };
    version->SetComponent(new KeepAliveComponent{ });
    main_menu.GetGameObject()->AddChild(version);

    auto game_objects = std::vector<GameObject*>{ main_menu.GetGameObject() };
    return game_objects;
}

}  // End namespace midistar
