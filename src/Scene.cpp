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

#include <algorithm>

#include "midistar/Scene.h"

namespace midistar {

Scene::Scene(
	Game* game
	, sf::RenderWindow& render_window
	, std::vector<GameObject*> game_objects)
		: game_{game}
		, game_objects_{ game_objects }
		, render_window_{ render_window }
		, new_game_objects_{ } {

}

Scene::~Scene()
{
	for (auto& o : game_objects_) {
		delete o;
	}
}

bool Scene::Init() {
	return true;
}

bool Scene::Update(int delta) {
	unsigned num_objects;
	unsigned i = 0;
	do {
		num_objects = game_objects_.size();
		while (i < game_objects_.size()) {
			game_objects_[i++]->Update(game_, delta);
		}
		FlushNewObjectQueue();
		// If we've added new objects during updating, we will update them now.
		// NOTE: This could cause an infinite loop if new objects create new
		// objects.
	} while (num_objects != game_objects_.size());

	return true;
}

bool Scene::Draw() {
	// Handle drawing
	for (auto obj : game_objects_) {
		obj->Draw(&render_window_);
	}

	return true;
}

void Scene::AddNewGameObject(GameObject* new_game_object) {
	this->new_game_objects_.push(new_game_object);
}

void Scene::FlushNewObjectQueue() {
	while (!new_game_objects_.empty()) {
		game_objects_.push_back(new_game_objects_.front());
		new_game_objects_.pop();
	}
}

void Scene::DeleteObject(GameObject * o)
{
	auto itr = std::find(game_objects_.begin(), game_objects_.end(), o);
	if (itr != game_objects_.end()) {
		game_objects_.erase(itr);
	}
	delete o;
}

std::vector<GameObject*>& Scene::GetGameObjects()
{
	return game_objects_;
}

void Scene::CleanUpObjects()
{
	auto game_objects_copy{ game_objects_ };
	for (auto& o : game_objects_copy) {
		if (o->GetRequestDelete()) {
			DeleteObject(o);
		}
	}
}

}   // End namespace midistar
