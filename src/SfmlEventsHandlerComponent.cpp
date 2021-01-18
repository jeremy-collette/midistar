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

#include "midistar/SfmlEventsHandlerComponent.h"

#include "midistar/SfmlEventsComponent.h"

namespace midistar {

SfmlEventsHandlerComponent::SfmlEventsHandlerComponent()
        : Component{ Component::SFML_EVENTS_HANDLER } {
}

SfmlEventsHandlerComponent::~SfmlEventsHandlerComponent() {
}

void SfmlEventsHandlerComponent::Update(Game* g, GameObject* o, int delta) {
    auto sfml_events_component = o->GetComponent<SfmlEventsComponent>(
        Component::SFML_EVENTS);

    if (!sfml_events_component) {
        return;
    }

    for (const auto& sfml_event : sfml_events_component->GetEvents()) {
        this->HandleEvent(g, o, delta, sfml_event);
    }
}

}  // End namespace midistar
