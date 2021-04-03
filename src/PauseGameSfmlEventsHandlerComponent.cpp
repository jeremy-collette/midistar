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

#include "midistar/PauseGameSfmlEventsHandlerComponent.h"

#include "midistar/UnpauseGameComponent.h"

namespace midistar {

void PauseGameSfmlEventsHandlerComponent::HandleEvent(
        Game* g
        , GameObject* o
        , int
        , sf::Event evt) {
    if (evt.type != sf::Event::KeyPressed
            || evt.key.code != sf::Keyboard::Enter) {
        return;
    }

    o->SetComponent(new UnpauseGameComponent{ });
    o->DeleteComponent(this->GetType());
}

}  // End namespace midistar
