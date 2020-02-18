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

#include "midistar/IntroSceneGameObjectFactory.h"
#include "midistar/LambdaComponent.h"

namespace midistar {

// TODO(@jeremy): this should be a scene factory
IntroSceneGameObjectFactory::IntroSceneGameObjectFactory() {
}

std::vector<GameObject*> IntroSceneGameObjectFactory::CreateGameObjects() {
	// TODO(@jeremy): cleanup heap objects
	// TODO(@jeremy): add font to project
	auto font = new sf::Font();
	if (!font->loadFromFile("arial.ttf")) {
		throw "Could not load font!";
	}
	auto text = new sf::Text("Press enter to play", *font, 50U);
	text->setFillColor(sf::Color::White);

	auto lamda_component = new LambdaComponent{
		[](Game* game, GameObject* game_object, auto delta) {
			for (const auto& evt : game->GetSfEvents()) {
				if (evt.key.code == sf::Keyboard::Enter && evt.type ==
					sf::Event::KeyPressed) {
					// TODO(@jeremy): use correct scene name
					game->SetScene("Foo");
				}
			}
		}
	};

	// Create text at (50, 50)
	auto text_object = new GameObject{ text, 50.0f, 50.0f, 100.0f, 100.0f };
	text_object->SetComponent(lamda_component);
	return std::vector<GameObject*> { text_object };
}

}  // End namespace midistar
