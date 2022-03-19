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

#ifndef MIDISTAR_SCOREMANAGERCOMPONENT_H_
#define MIDISTAR_SCOREMANAGERCOMPONENT_H_

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

class ScoreManagerComponent : public Component {
 public:
    ScoreManagerComponent();

    int GetScore();

    void ModifyScore(int delta);

    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    int score_;
    std::string text_;
};

}   // End namespace midistar

#endif  // MIDISTAR_DELETEOFFSCREENCOMPONENT_H_
