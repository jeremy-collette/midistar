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

#include "midistar/MenuBuilderHeapFactory.h"

namespace midistar {

MenuBuilderHeapFactory::~MenuBuilderHeapFactory() {
    // TODO(@jeremy): implement
}

MenuBuilder& MenuBuilderHeapFactory::Create(MenuItemBuilder& parent, sf::Font & font) {
    return *(new MenuBuilder{ &parent, font, *this });
}

MenuBuilder& MenuBuilderHeapFactory::Create(sf::Font & font) {
    return *(new MenuBuilder{ (MenuItemBuilder*)nullptr, font, *this });
}

}   // End namespace midistar

