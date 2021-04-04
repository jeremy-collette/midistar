/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#include "midistar/PauseSongGameObjectFactory.h"

#include "midistar/Config.h"
#include "midistar/Constants.h"
#include "midistar/KeepAliveComponent.h"
#include "midistar/LambdaComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/SfmlEventsComponent.h"
#include "midistar/PauseSongSfmlEventsHandlerComponent.h"
#include "midistar/TextFactory.h"

namespace midistar {

bool PauseSongGameObjectFactory::CreatePauseSongGameObject(
    GameObject* midi_file_in
    , std::vector<GameObject*> scene_game_objects
    , GameObject** game_object_out) {

    midi_file_in->SetTimeScale(0.0f);

    // TODO(@jez): load fonts higher up and pass down where needed. Then clean-
    // up on exit.
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        std::cerr << "Could not load font \"" << MIDISTAR_FONT << "\"!\n";
        return false;
    }

    auto text_factory = TextFactory{ "Song paused.", *font };
    text_factory.SetXPosition(TextFactory::CENTER);
    text_factory.SetYPosition(TextFactory::CENTER);
    auto game_object = text_factory.GetGameObject();

    auto child_text_factory = TextFactory{ "Test your instrument and press "
        "enter when ready.", *font };
    child_text_factory.SetXPosition(TextFactory::CENTER);
    double text_width, text_height;
    game_object->GetSize(&text_width, &text_height);
    child_text_factory.SetYPosition(TextFactory::CENTER, text_height + 10.0);
    game_object->AddChild(child_text_factory.GetGameObject());

    game_object->AddTag("PauseGame");
    game_object->SetComponent(new PauseSongSfmlEventsHandlerComponent{});

    AddMidiKeyTextToInstruments(scene_game_objects, *font);

    *game_object_out = game_object;
    return true;
}

bool PauseSongGameObjectFactory::AddMidiKeyTextToInstruments(
    std::vector<GameObject*> scene_game_objects
    , const sf::Font& font) {

    for (auto instrument : scene_game_objects) {
        if (!instrument->HasTag("Drum")) {
            continue;
        }

        auto note_info_component = instrument->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
        if (!note_info_component) {
            continue;
        }

        auto note_annotation = std::to_string(note_info_component->GetKey());
        auto instrument_text_factory = TextFactory{ note_annotation, font };
        double ins_x, ins_y;
        instrument->GetPosition(&ins_x, &ins_y);
        double ins_w, ins_h;
        instrument->GetSize(&ins_w, &ins_h);

        auto text_game_object = instrument_text_factory.GetGameObject();
        double text_w, text_h;
        text_game_object->GetSize(&text_w, &text_h);
        // TODO(@jez): investigate why font placement is slightly off
        auto text_x = ins_x + ins_w / 2.0f - text_w / 2.0f - 5.0f;
        auto text_y = ins_y + ins_h / 2.0f - text_h / 2.0f - 5.0f;
        instrument_text_factory
            .SetXPosition(text_x)
            .SetYPosition(text_y);
        text_game_object->AddTag("MidiKeyText");
        instrument->AddChild(text_game_object);
    }

    return true;
}

}  // namespace midistar
