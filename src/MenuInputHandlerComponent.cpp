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

#include "midistar/MenuInputHandlerComponent.h"

#include "midistar/Game.h"
#include "midistar/MenuComponent.h"

namespace midistar {
MenuInputHandlerComponent::MenuInputHandlerComponent()
		: Component(Component::MENU_INPUT_HANDLER) {
}

void MenuInputHandlerComponent::Update(Game* g, GameObject* o, int delta) {
	// Check for required component
	auto menu = o->GetComponent<MenuComponent>(Component::MENU);
	if (!menu) {
		return;
	}

	// Check SFML events for key presses
	for (const auto& e : g->GetSfEvents()) {
		// Check if its the right key and event type
		if (e.type != sf::Event::KeyPressed ||
			(e.key.code != sf::Keyboard::Down && e.key.code != sf::Keyboard::Up
				&& e.key.code != sf::Keyboard::Enter)) {
			continue;
		}

		switch (e.key.code) {
			case sf::Keyboard::Down:
				menu->OnNextFocus();
				break;
			case sf::Keyboard::Up:
				menu->OnPreviousFocus();
				break;
			case sf::Keyboard::Enter:
				menu->OnSelect();
				break;
			default:
				throw "Unexpected key code";
		}
	}
}

}  // End namespace midistar
