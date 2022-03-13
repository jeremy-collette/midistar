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

#include "midistar/MidiFileGameObjectFactory.h"

#include "midistar/Config.h"
#include "midistar/MidiFileIn.h"
#include "midistar/MidiFileInComponent.h"
#include "midistar/SongNotePracticeModeComponent.h"

namespace midistar {

bool MidiFileGameObjectFactory::Create(
        std::string file_name
        , GameObject** game_object_out) {
    auto midi_file_in = new MidiFileIn{ };
    if (!midi_file_in->Init(file_name)) {
        return false;
    }

    auto midi_file_in_component = new MidiFileInComponent{ midi_file_in };

    auto rect = new sf::RectangleShape{ { 0, 0 } };
    *game_object_out = new GameObject{ rect, 0, 0, 0, 0 };
    (*game_object_out)->AddTag("MidiFile");
    (*game_object_out)->SetComponent(midi_file_in_component);
    if (Config::GetInstance().GetPracticeMode()) {
        (*game_object_out)->SetComponent(new SongNotePracticeModeComponent{});
    }

    return true;
}

}  // namespace midistar
