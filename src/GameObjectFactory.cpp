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

#include "midistar/GameObjectFactory.h"

#include "midistar/BarComponent.h"
#include "midistar/CollisionDetectorComponent.h"
#include "midistar/Config.h"
#include "midistar/DeleteOffscreenComponent.h"
#include "midistar/Game.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/InstrumentComponent.h"
#include "midistar/InstrumentInputHandlerComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/PhysicsComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/SongNoteCollisionHandlerComponent.h"
#include "midistar/SongNoteComponent.h"

namespace midistar {

GameObjectFactory GameObjectFactory::instance_;

GameObjectFactory& GameObjectFactory::GetInstance() {
    return instance_;
}

GameObject* GameObjectFactory::CreateInstrumentBar() {
    double x = 0;
    double y = Config::GetInstance().GetScreenHeight()-100.0;
    GameObject* bar = new GameObject{x, y};
    bar->SetComponent(new BarComponent{});

    sf::RectangleShape* rect = new sf::RectangleShape{
        {static_cast<float>(Config::GetInstance().GetScreenWidth()), 20.0f}};
    rect->setPosition({static_cast<float>(x), static_cast<float>(y)});
    rect->setFillColor(sf::Color::Red);
    bar->SetComponent(new GraphicsComponent{rect});
    return bar;
}

GameObject* GameObjectFactory::CreateInstrumentNote(int note) {
    double x = (note - Config::GetInstance().GetMinimumMidiNote())
        * note_width_;
    double y = Config::GetInstance().GetScreenHeight()-100;
    GameObject* ins_note = new GameObject{x, y};

    ins_note->SetComponent(new InstrumentComponent{});
    ins_note->SetComponent(new NoteInfoComponent{-1, 0, note
            , Config::GetInstance().GetMidiOutVelocity()});
    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            note_width_), 20}};
    rect->setPosition({static_cast<float>(x), static_cast<float>(y)});
    rect->setFillColor(sf::Color::Green);
    ins_note->SetComponent(new GraphicsComponent{rect});
    ins_note->SetComponent(new InstrumentInputHandlerComponent{});
    return ins_note;
}

GameObject* GameObjectFactory::CreateSongNote(
        int track
        , int chan
        , int note
        , int vel
        , double duration) {
    double x = (note - Config::GetInstance().GetMinimumMidiNote())
        * note_width_;
    // Height is equal to duration in milliseconds * pixels per millisecond
    double actual_speed = note_speed_ / 10.0;
    // TODO(jez): debug this - this should work at 1000
    double height = duration * 1000 * actual_speed;

    GameObject* song_note;
    sf::RectangleShape* rect;
    song_note = new GameObject{x, -height};
    rect = new sf::RectangleShape{{static_cast<float>(note_width_)
        , static_cast<float>(height)}};
    rect->setPosition({static_cast<float>(x), -static_cast<float>(height)});
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, chan, note, vel});
    song_note->SetComponent(new GraphicsComponent{rect});
    song_note->SetComponent(new PhysicsComponent{0, actual_speed});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new CollisionDetectorComponent{});
    song_note->SetComponent(new SongNoteCollisionHandlerComponent{});
    return song_note;
}

void GameObjectFactory::Init(double note_speed) {
    note_speed_ = note_speed;
    note_width_ = Config::GetInstance().GetScreenWidth() / static_cast<double>(
            Config::GetInstance().GetNumMidiNotes());
}

GameObjectFactory::GameObjectFactory()
    : note_speed_{0}
    , note_width_{0} {
}

}  // End namespace midistar
