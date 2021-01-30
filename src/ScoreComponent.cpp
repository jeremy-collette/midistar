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

#include "midistar/ScoreComponent.h"

#include <cassert>

#include "midistar/ScoreManagerComponent.h"

namespace midistar {

ScoreComponent::ScoreComponent(ScoreDeltaProvider* score_delta_provider)
    : Component{ Component::SCORE }
        , being_played_{ false }
        , score_delta_provider_{ score_delta_provider } {
}

ScoreComponent::~ScoreComponent() {
    delete score_delta_provider_;
}

void ScoreComponent::Update(Game* g, GameObject* o, int delta) {
    auto score_game_object = g->GetCurrentScene()
        .GetFirstGameObjectByTag("ScoreManager");
    assert(score_game_object);

    auto score_manager = score_game_object->
        GetComponent<ScoreManagerComponent>(Component::SCORE_MANAGER);
    assert(score_manager);
    score_manager->ModifyScore(this->score_delta_provider_->GetScoreDelta(
        g
        , o
        , delta
        , this->being_played_));
}

void ScoreComponent::SetIsBeingPlayed(bool being_played) {
    this->being_played_ = being_played;
}

}  // End namespace midistar
