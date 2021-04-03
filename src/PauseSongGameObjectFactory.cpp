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
#include "midistar/SfmlEventsComponent.h"
#include "midistar/PauseSongSfmlEventsHandlerComponent.h"
#include "midistar/TextFactory.h"

namespace midistar {

bool PauseSongGameObjectFactory::CreatePauseSongGameObject(
    GameObject* midi_file_in
    , GameObject** game_object_out) {

    midi_file_in->SetTimeScale(0.0f);

    // Note: this is not getting cleaned up.
    auto font = new sf::Font();
    if (!font->loadFromFile(MIDISTAR_FONT)) {
        std::cerr << "Could not load font \"" << MIDISTAR_FONT << "\"!\n";
        return false;
    }

    auto text_factory = TextFactory{ "Song paused. Press enter when ready."
        , *font };
    text_factory.SetXPosition(TextFactory::CENTER);
    text_factory.SetYPosition(TextFactory::CENTER);
    auto game_object = text_factory.GetGameObject();
    game_object->DeleteComponent(Component::KEEP_ALIVE);
    game_object->AddTag("PauseGame");
    game_object->SetComponent(new PauseSongSfmlEventsHandlerComponent{});

    *game_object_out = game_object;
    return true;
}

}  // namespace midistar
