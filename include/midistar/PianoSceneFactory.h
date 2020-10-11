/*
 * midistar
 * Copyright (C) 2018-2019 Jeremy Collette.
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

#ifndef MIDISTAR_PIANOSCENEFACTORY_H_
#define MIDISTAR_PIANOSCENEFACTORY_H_

#include <string>

#include "midistar/SceneFactory.h"

namespace midistar {

class PianoSceneFactory : public SceneFactory {
 public:
    explicit PianoSceneFactory(const std::string& midi_file_name);

    virtual bool Create(
        Game* game
        , sf::RenderWindow& render_window
        , Scene** scene);

 private:
     const std::string& midi_file_name_;
};

}   // End namespace midistar

#endif  // MIDISTAR_PIANOSCENEFACTORY_H_
