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

#include "midistar/SfmlEventsComponent.h"

namespace midistar {
SfmlEventsComponent::SfmlEventsComponent(sf::Window* window)
        : Component{ Component::SFML_EVENTS }
        , event_buffer_{ }
        , window_{ window } {
}

SfmlEventsComponent::~SfmlEventsComponent() {
}

std::vector<sf::Event>& SfmlEventsComponent::GetEvents() {
    return event_buffer_;
}

void SfmlEventsComponent::Update(Game*, GameObject*, int) {
    event_buffer_.clear();

    sf::Event event;
    while (window_->pollEvent(event)) {
        event_buffer_.push_back(event);
    }
}

}  // End namespace midistar
