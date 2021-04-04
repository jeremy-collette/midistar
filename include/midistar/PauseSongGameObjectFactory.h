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

#ifndef MIDISTAR_PAUSEGAMEOBJECTFACTORY_H_
#define MIDISTAR_PAUSEGAMEOBJECTFACTORY_H_

#include <vector>
#include <SFML/Graphics/Font.hpp>

#include "midistar/GameObject.h"

namespace midistar {

class PauseSongGameObjectFactory {
 public:
    bool CreatePauseSongGameObject(
        GameObject* midi_file_in
        , std::vector<GameObject*> scene_game_objects
        , GameObject** game_object_out);

 private:
    bool AddMidiKeyTextToInstruments(
        std::vector<GameObject*> scene_game_objects,
        const sf::Font& font);
};

}  // End namespace midistar

#endif  // MIDISTAR_PAUSEGAMEOBJECTFACTORY_H_
