/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
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

#ifndef MIDISTAR_GRAPHICSCOMPONENT_H_
#define MIDISTAR_GRAPHICSCOMPONENT_H_

#include <SFML/Graphics.hpp>

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace Midistar {

/**
 * The GraphicsComponent class draws a rectangle on the screen.
 */
class GraphicsComponent : public Component {
 public:
    /**
     * Constructor.
     *
     * \param rect Rectangle to draw on the screen.
     */
    explicit GraphicsComponent(sf::RectangleShape* rect);

    /**
     * Destructor.
     */
    ~GraphicsComponent();

    /**
     * Gets the underlying rectangle.
     *
     * \return A rectangle.
     */
    sf::RectangleShape& GetShape();

    /**
     * Gets the size of the underlying rectangle.
     *
     * \param[out] width Stores the width.
     * \param[out] height Stores the height.
     */
    virtual void GetSize(double* width, double* height);

    /**
     * Sets the size of the underlying rectangle.
     *
     * \param width New width.
     * \param height New height.
     */
    virtual void SetSize(double width, double height);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o);

 private:
    sf::RectangleShape* rect_;  //<! Underlying rectangle
};

}   // namespace Midistar

#endif  // MIDISTAR_GRAPHICSCOMPONENT_H_
