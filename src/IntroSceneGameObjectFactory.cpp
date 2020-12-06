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

#include "midistar/Constants.h"
#include "midistar/DrumSceneFactory.h"
#include "midistar/Game.h"
#include "midistar/KeepAliveComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuFactory.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/MenuItemComponent.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/TextFactory.h"
#include "midistar/Version.h"

namespace fs = std::experimental::filesystem;

namespace midistar {

IntroSceneGameObjectFactory::IntroSceneGameObjectFactory() {
}

std::vector<GameObject*> IntroSceneGameObjectFactory::CreateGameObjects(
        sf::RenderWindow* window) {
    // Create menu
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        throw "Could not load font!";
    }

    auto factory = MenuFactory{ *font, window };
    auto item_default_font_size = 25;
    auto piano_menu = factory.CreateMenu("Song selection", item_default_font_size)
        .SetTitleFontSize(35);
    auto drum_menu = factory.CreateMenu("Song selection", item_default_font_size)
        .SetTitleFontSize(35);

    piano_menu.GetGameObject()->AddChild(
        CreateScanningTextGameObject(*font));
    drum_menu.GetGameObject()->AddChild(
        CreateScanningTextGameObject(*font));

    // Add menu items
    auto menu_item_text = std::vector<std::string*>{ };
    std::string path = ".";
    auto song_found = false;
    for (const auto & entry : fs::directory_iterator(path)) {
        auto path_string = entry.path().string();
        if (path_string.find(".mid") != std::string::npos) {
            song_found = true;
            piano_menu.AddMenuItem(
                factory.CreateMenuItem(path_string)
                    .SetOnSelect(([path_string](Game* g, GameObject*, int) {
                        Scene* new_scene = nullptr;
                        auto piano_scene_factory = PianoSceneFactory{
                            path_string };
                        if (!piano_scene_factory.Create(
                            g
                            , &g->GetWindow()
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
                    auto drum_scene_factory = DrumSceneFactory{ path_string };
                    if (!drum_scene_factory.Create(
                        g
                        , &g->GetWindow()
                        , &new_scene)) {
                        throw "Scene creation failed";
                    }
                    g->SetScene(new_scene);
                }))
                .SetFontSize(20));
        }
    }

    if (!song_found) {
        piano_menu.GetGameObject()->AddChild(
            CreateNoFilesFoundTextGameObject(*font));
        drum_menu.GetGameObject()->AddChild(
            CreateNoFilesFoundTextGameObject(*font));
    }

    item_default_font_size = 35;
    auto main_menu =
        factory.CreateMenu("midistar", item_default_font_size)
        .SetTitleColour(sf::Color::Green)
        .AddMenuItem(factory.CreateMenuItem("1. Piano")
            .SetOnSelect(piano_menu))
        .AddMenuItem(factory.CreateMenuItem("2. Drums")
            .SetOnSelect(drum_menu))
        .AddMenuItem(factory.CreateMenuItem("0. Exit")
            .SetOnSelect([](Game* g, GameObject*, int) {
                g->Exit();
            }))
        .SetTitleFontSize(50);

    auto copyright = CreateCopyrightTextGameObject(*font);
    main_menu.GetGameObject()->AddChild(copyright);

    auto version = CreateVersionTextGameObject(*font);
    main_menu.GetGameObject()->AddChild(version);

    auto game_objects = std::vector<GameObject*>{
        main_menu.GetGameObject()
        , piano_menu.GetGameObject()
        , drum_menu.GetGameObject() };
    return game_objects;
}

GameObject* IntroSceneGameObjectFactory::CreateCopyrightTextGameObject(
    const sf::Font& font) {
    auto copyright_string = new std::string{
        "Copyright (c) Jeremy Collette 2018-2020" };
    TextFactory text_builder{ *copyright_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::CENTER);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneGameObjectFactory::CreateNoFilesFoundTextGameObject(
    const sf::Font& font) {
    auto message = new std::string{ "No .mid files found!" };
    TextFactory text_builder{ *message, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::Red);
    text_builder.SetXPosition(TextFactory::MIN, 50);
    text_builder.SetYPosition(TextFactory::MIN, 150);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneGameObjectFactory::CreateScanningTextGameObject(
        const sf::Font& font) {
    auto subtitle_string = new std::string{ "Scanning directory "
        + fs::current_path().string() };
    TextFactory text_builder{ *subtitle_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::MIN);
    text_builder.SetYPosition(TextFactory::MIN, 80);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneGameObjectFactory::CreateVersionTextGameObject(
        const sf::Font& font) {
    auto version_string = new std::string{ MIDISTAR_VERSION };
    TextFactory text_builder{ *version_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::MAX);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

}  // End namespace midistar
