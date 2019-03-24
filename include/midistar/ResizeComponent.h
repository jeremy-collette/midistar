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

#ifndef MIDISTAR_RESIZECOMPONENT_H_
#define MIDISTAR_RESIZECOMPONENT_H_

#include <SFML/Graphics.hpp>

#include "midistar/Component.h"
#include "midistar/GameObject.h"

namespace midistar {

/**
 * The AnchorFlag typedef is used as the data type in the anchor flags enum.
 */
typedef char AnchorFlag;

/**
 * The ResizeComponent class resizes the GraphicsComponent shape of its owner
 * by a given size, from a specified corner.
 */
class ResizeComponent : public Component {
 public:
    /**
     * AnchorFlag are used to specify anchoring behaviour when resizing.
     *
     * During resizing, the shape is stretched away (or shortened towards) the
     * anchor. The point where the anchor lies is unchanged by the resize.
     *
     * For example, if the TOP_LEFT flag is used, the top left corner of the
     * shape is not moved during resizing. Conversely, the other three corners
     * are moved to create the new size.
     *
     * Anchor flags may be combined, to specify more precise anchor points.
     * For example, if the TOP_LEFT and TOP_RIGHT flags are combined, the
     * anchor point is the mid-point of the top left and top right edges, or
     * the middle of the top edge. Resulting resizes will not move this
     * point of the shape.
     *
     * If all the flags are combined, the anchor will be in the centre of the
     * shape, and a resize will move each edge out or in equally.
     */
    enum : AnchorFlag {
        TOP_LEFT = 1,
        TOP_RIGHT = 1 << 1,
        BOT_LEFT = 1 << 2,
        BOT_RIGHT = 1 << 3,
        TOP = TOP_LEFT | TOP_RIGHT,
        BOT = BOT_LEFT | BOT_RIGHT,
        CENTRE = TOP | BOT
    };

    /**
     * Constructor.
     *
     * \param new_width The new width.
     * \param new_height The new height.
     * \param anchor_flags Indicates the anchoring flags.
     */
    ResizeComponent(
            double new_width
            , double new_height
            , AnchorFlag anchor_flags);


    /**
     * Constructor.
     *
     * \param new_width The new width.
     * \param new_height The new height.
     */
    ResizeComponent(double new_width, double new_height);

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    void CalculateAnchorPosition(double* anchor_x, double* anchor_y);  //!<
                                     //!< Calculates the position of the anchor

    AnchorFlag anchor_flags_;  //!< Anchoring flags
    double new_height_;  //!< Target height
    double new_width_;  //!< Target width
};

}  // namespace midistar

#endif  // MIDISTAR_RESIZECOMPONENT_H_
