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

#include "midistar/IntroSceneFactory.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "midistar/BackgroundSongPlayerComponent.h"
#include "midistar/Config.h"
#include "midistar/Constants.h"
#include "midistar/DrumSceneFactory.h"
#include "midistar/Game.h"
#include "midistar/KeepAliveComponent.h"
#include "midistar/IntroSceneSfmlEventsHandlerComponent.h"
#include "midistar/MenuComponent.h"
#include "midistar/MenuFactory.h"
#include "midistar/MenuInputHandlerComponent.h"
#include "midistar/MenuItemComponent.h"
#include "midistar/MidiOut.h"
#include "midistar/MidiOutputComponent.h"
#include "midistar/MidiFileGameObjectFactory.h"
#include "midistar/PianoSceneFactory.h"
#include "midistar/Scene.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/TextFactory.h"
#include "midistar/Version.h"

namespace fs = std::experimental::filesystem;

namespace midistar {

// These are defined in the header but we have to re-define here due to
// constexpr weirdness.
constexpr const char* IntroSceneFactory::DRUM_MIDI_DIR;

constexpr const char* IntroSceneFactory::PIANO_MIDI_DIR;

bool IntroSceneFactory::Create(
        Game* game
        , sf::RenderWindow* render_window
        , Scene** scene
        , bool background_music) {
    auto game_objects = CreateGameObjects(render_window, background_music);

    *scene = new Scene{ game, render_window, game_objects };
    return true;
}

std::vector<GameObject*> IntroSceneFactory::CreateGameObjects(
    sf::RenderWindow* window
    , bool background_music) {
    // Create menu
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        std::cerr << "Could not load font \"" << MIDISTAR_FONT << "\"!\n";
        throw "Could not load font!";
    }

    auto factory = MenuFactory{ *font, window };
    auto item_default_font_size = 25;
    auto piano_menu_normal = factory.CreateMenu("Song selection"
        , item_default_font_size)
        .SetTitleFontSize(35);
    auto piano_menu_practice = factory.CreateMenu("Song selection"
        , item_default_font_size)
        .SetTitleFontSize(35);
    auto drum_menu = factory.CreateMenu("Song selection"
        , item_default_font_size)
        .SetTitleFontSize(35);

    auto midistar_dir = fs::current_path();
    auto piano_dir = midistar_dir;
    // The '/=' operator appends paths in the correct native format.
    // Don't ask me why.
    piano_dir /= PIANO_MIDI_DIR;
    piano_menu_normal.GetGameObject()->AddChild(
        CreateScanningTextGameObject(
            *font
            , piano_dir.string()));
    piano_menu_practice.GetGameObject()->AddChild(
        CreateScanningTextGameObject(
            *font
            , piano_dir.string()));

    auto drum_dir = midistar_dir;
    // The '/=' operator appends paths in the correct native format.
    // Don't ask me why.
    drum_dir /= DRUM_MIDI_DIR;
    drum_menu.GetGameObject()->AddChild(
        CreateScanningTextGameObject(
            *font
            , drum_dir.string()));

    // Add menu items for Piano songs
    // Get songs recursively from song dir and sort
    auto songs = GetSortedMidiSongs(PIANO_MIDI_DIR);

    bool* practice_mode = new bool(false);

    for (const auto & entry : songs) {
        auto path = entry.path();
        piano_menu_normal.AddMenuItem(
            factory.CreateMenuItem(path.filename().string())
                .SetOnSelect(([path, practice_mode](Game* g, GameObject*, int) {
                    Scene* new_scene = nullptr;
                    auto piano_scene_factory = PianoSceneFactory{
                        path.string()
                        , false };
                    if (!piano_scene_factory.Create(
                        g
                        , &g->GetWindow()
                        , &new_scene)) {
                        throw "Scene creation failed";
                    }
                    g->SetScene(new_scene);
                }))
                .SetFontSize(20));

        piano_menu_practice.AddMenuItem(
            factory.CreateMenuItem(path.filename().string())
                .SetOnSelect(([path, practice_mode](Game* g, GameObject*, int) {
                    Scene* new_scene = nullptr;
                    auto piano_scene_factory = PianoSceneFactory{
                        path.string()
                        , true };
                    if (!piano_scene_factory.Create(
                        g
                        , &g->GetWindow()
                        , &new_scene)) {
                        throw "Scene creation failed";
                    }
                    g->SetScene(new_scene);
                }))
                .SetFontSize(20));
    }

    if (!songs.size()) {
        piano_menu_normal.GetGameObject()->AddChild(
            CreateNoFilesFoundTextGameObject(*font));
        piano_menu_practice.GetGameObject()->AddChild(
            CreateNoFilesFoundTextGameObject(*font));
    }

    // Add menu items for Drum songs
    songs = GetSortedMidiSongs(DRUM_MIDI_DIR);
    for (const auto & entry : songs) {
        auto path = entry.path();
        drum_menu.AddMenuItem(
            factory.CreateMenuItem(path.filename().string())
                .SetOnSelect(([path](Game* g, GameObject*, int) {
                    Scene* new_scene = nullptr;
                    auto drum_scene_factory = DrumSceneFactory{ path.string() };
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

    if (!songs.size()) {
        drum_menu.GetGameObject()->AddChild(
            CreateNoFilesFoundTextGameObject(*font));
    }

    auto piano_mode_menu = factory.CreateMenu("Select mode"
        , item_default_font_size)
        .SetTitleFontSize(35)
        .AddMenuItem(factory.CreateMenuItem("1. Normal")
            .SetOnSelect(piano_menu_normal))
        .AddMenuItem(factory.CreateMenuItem("2. Practice")
            .SetOnSelect(piano_menu_practice));

    item_default_font_size = 35;
    auto main_menu =
        factory.CreateMenu("midistar", item_default_font_size)
        .SetTitleColour(sf::Color::Green)
        .AddMenuItem(factory.CreateMenuItem("1. Piano")
            .SetOnSelect(piano_mode_menu))
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

        auto game_objects = std::vector<GameObject*>
        {
            main_menu.GetGameObject()
            , piano_menu_normal.GetGameObject()
            , piano_menu_practice.GetGameObject()
            , drum_menu.GetGameObject()
            , piano_mode_menu.GetGameObject()
        };

        if (background_music && Config::GetInstance().GetEnableTitleMusic()) {
            GameObject* background_music_game_object;
            if (CreateBackgroundMusicPlayer(&background_music_game_object)) {
                game_objects.push_back(background_music_game_object);
            } else {
                std::cerr << "Warning: Could not create title screen background"
                    << " music player!\n";
            }
        }
        return game_objects;
}

bool IntroSceneFactory::CreateBackgroundMusicPlayer(
    GameObject** game_object_out) {
    // Create MIDI file GameObject to read notes from MIDI file
    auto midi_file_object_factory = MidiFileGameObjectFactory{};
    GameObject* midi_file_game_object = nullptr;
    if (!midi_file_object_factory.Create(
        Config::GetInstance().GetTitleMusicMidiFilePath(),
        &midi_file_game_object,
        false)) {
        return false;
    }

    auto midi_out = new MidiOut{ };
    if (!midi_out->Init()) {
        return false;
    }
    midi_file_game_object->SetComponent(new MidiOutputComponent{ midi_out });
    midi_file_game_object->AddTag("MidiOut");

    midi_file_game_object->SetComponent(new BackgroundSongPlayerComponent{});
    *game_object_out = midi_file_game_object;
    return true;
}

GameObject* IntroSceneFactory::CreateCopyrightTextGameObject(
    const sf::Font& font) {
    auto copyright_string = new std::string{
        "Copyright (c) Jeremy Collette 2018-2021" };
    TextFactory text_builder{ *copyright_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::CENTER);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneFactory::CreateNoFilesFoundTextGameObject(
    const sf::Font& font) {
    auto message = new std::string{ "No .mid files found!" };
    TextFactory text_builder{ *message, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::Red);
    text_builder.SetXPosition(TextFactory::MIN, 50);
    text_builder.SetYPosition(TextFactory::MIN, 150);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneFactory::CreateScanningTextGameObject(
    const sf::Font& font
    , std::string directory) {
    auto subtitle_string = new std::string{ "Scanning directory "
        + directory };
    TextFactory text_builder{ *subtitle_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    text_builder.SetXPosition(TextFactory::MIN);
    text_builder.SetYPosition(TextFactory::MIN, 80);
    return text_builder.GetGameObject();
}

GameObject* IntroSceneFactory::CreateVersionTextGameObject(
    const sf::Font& font) {
    auto version_string = new std::string{ MIDISTAR_VERSION };
    TextFactory text_builder{ *version_string, font };
    text_builder.SetFontSize(25);
    text_builder.SetColour(sf::Color::White);
    // TODO(@jez): investigate why this is slightly off
    text_builder.SetXPosition(TextFactory::MAX, -10.0f);
    text_builder.SetYPosition(TextFactory::MAX, -20.0f);
    return text_builder.GetGameObject();
}

std::vector<fs::directory_entry> IntroSceneFactory::GetSortedMidiSongs(
        const std::string & path) {
    // Get songs recursively from song dir and sort
    auto songs_itr = fs::recursive_directory_iterator(path);
    auto songs = std::vector<fs::directory_entry>(
        fs::begin(songs_itr)
        , fs::end(songs_itr));

    // Remove files that aren't midi files
    songs.erase(
        std::remove_if(songs.begin(), songs.end()
            , [](const fs::v1::directory_entry& e)
            {
                // Convert to lower case
                auto filename = e.path().filename().string();
                std::transform(filename.begin(), filename.end()
                    , filename.begin()
                    , [](unsigned char c) {
                        return std::tolower(c);
                    });

                std::string suffix = ".mid";
                if (filename.size() < suffix.size())
                {
                    return true;
                }
                return !std::equal(suffix.rbegin(), suffix.rend(),
                    filename.rbegin());
            }),
        songs.end());

    // This is some outrageous fun to sort a list of strings case-insensitively.
    std::sort(songs.begin(), songs.end(),
        [](const fs::v1::directory_entry& a, const fs::v1::directory_entry& b) {
            auto filenameA = a.path().filename().string();
            std::transform(filenameA.begin(), filenameA.end(), filenameA.begin()
                , [](unsigned char c) {
                    return std::tolower(c);
                });

            auto filenameB = b.path().filename().string();
            std::transform(filenameB.begin(), filenameB.end(), filenameB.begin()
                , [](unsigned char c) {
                    return std::tolower(c);
                });

            return filenameA < filenameB;
        });
    return songs;
}

}   // End namespace midistar

