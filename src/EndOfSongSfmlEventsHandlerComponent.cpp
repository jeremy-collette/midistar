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

#include "midistar/EndOfSongSfmlEventsHandlerComponent.h"

#include "midistar/IntroSceneFactory.h"

namespace midistar {

void EndOfSongSongSfmlEventsHandlerComponent::HandleEvent(
        Game* g
        , GameObject* o
        , int
        , sf::Event evt) {
    if (evt.type != sf::Event::KeyPressed
            || evt.key.code != sf::Keyboard::Enter) {
        return;
    }

    // Set scene to intro
    auto intro_scene_factory = IntroSceneFactory{};
    auto next_scene = new Scene{
        g,
        &g->GetWindow(),
        std::vector<GameObject*>{ }
    };

    if (!intro_scene_factory.Create(
        g
        , &g->GetWindow()
        , &next_scene)) {
        throw "Could not create Intro scene.";
    }
    g->SetScene(next_scene);
}

}  // End namespace midistar
