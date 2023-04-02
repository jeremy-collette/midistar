/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

#include "midistar/SongSceneSfmlEventsHandlerComponent.h"

#include "midistar/IntroSceneFactory.h"

namespace midistar {

void SongSceneSfmlEventsHandlerComponent::HandleEvent(
        Game* g
        , GameObject*
        , int
        , sf::Event evt) {
    if (evt.type != sf::Event::Closed && (evt.type != sf::Event::KeyPressed ||
            evt.key.code != sf::Keyboard::Escape)) {
        return;
    }

    // If the user has pressed escape or clicked the X, go back to menu.
    auto intro_scene_factory = IntroSceneFactory{};
    auto next_scene = new Scene{
        g,
        &g->GetWindow(),
        std::vector<GameObject*>{ }
    };

    intro_scene_factory.Create(
        g
        , &g->GetWindow()
        , &next_scene);

    g->SetScene(next_scene);
}

}  // End namespace midistar
