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

#ifndef MIDISTAR_LAMBDACOMPONENT_H_
#define MIDISTAR_LAMBDACOMPONENT_H_

#include <functional>

#include "midistar/Component.h"
#include "midistar/Game.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The LambdaComponent allows for lambda functions to be used as a Component.
 */
class LambdaComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param func The lambda function to call.
     */
    explicit LambdaComponent(
            std::function<void(Game*, GameObject*, int)> func);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    std::function<void(Game*, GameObject*, int)> func_;  //!< The lambda to
                                                                //!< invoke
};

}   // End namespace midistar

#endif  // MIDISTAR_LAMBDACOMPONENT_H_
