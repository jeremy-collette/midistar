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

#include "midistar/ScoreManagerComponent.h"

#include <sstream>

namespace midistar {

ScoreManagerComponent::ScoreManagerComponent()
    : Component{ Component::SCORE_MANAGER },
        score_{ 0 } {
}

void ScoreManagerComponent::Update(Game*, GameObject* o, int delta) {
    //score_ += delta;

    auto ss = std::stringstream();
    // TODO(@jez): add some score factor to constants
    ss << "Score: " << score_ / 10;

    text_ = ss.str();
    auto sf_text = o->GetDrawformable<sf::Text>();
    sf_text->setString(text_);
}

void ScoreManagerComponent::ModifyScore(int delta) {
    score_ += delta;
}

}  // End namespace midistar
