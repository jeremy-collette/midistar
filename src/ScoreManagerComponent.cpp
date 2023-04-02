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

#include "midistar/ScoreManagerComponent.h"

#include <sstream>

namespace midistar {

ScoreManagerComponent::ScoreManagerComponent()
    : Component{ Component::SCORE_MANAGER },
        score_{ 0 } {
}

int ScoreManagerComponent::GetScore() {
    return score_;
}

void ScoreManagerComponent::ModifyScore(int score_delta) {
    score_ += score_delta;
}

void ScoreManagerComponent::Update(Game*, GameObject* o, int delta) {
    auto ss = std::stringstream();
    ss << "Score: " << score_;

    text_ = ss.str();
    auto sf_text = o->GetDrawformable<sf::Text>();
    sf_text->setString(text_);
}

}  // End namespace midistar
