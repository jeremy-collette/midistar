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

GameObject* GameObjectFactory::CreateInstrumentBar() {
    GameObject* bar = new GameObject{0, static_cast<double>(
            Config::GetInstance().GetScreenHeight()-100)};
    bar->SetComponent(new BarComponent{});

    sf::RectangleShape* rect = new sf::RectangleShape{
        {static_cast<float>(Config::GetInstance().GetScreenWidth()), 20.0f}};
    rect->setFillColor(sf::Color::Red);
    bar->SetComponent(new GraphicsComponent{rect});
    return bar;
}

GameObject* GameObjectFactory::CreateInstrumentNote(int note) {
    double width = Config::GetInstance().GetScreenWidth() /
        static_cast<double>(Config::GetInstance().GetNumMidiNotes());
    double x = (note - Config::GetInstance().GetMinimumMidiNote()) * width;
    double y = Config::GetInstance().GetScreenHeight()-100;
    GameObject* ins_note = new GameObject{x, y};

    ins_note->SetComponent(new InstrumentComponent{});
    ins_note->SetComponent(new NoteInfoComponent{
            -1
            , true
            , Config::GetInstance().GetMidiChannel()
            , note
            , Config::GetInstance().GetMidiOutVelocity()});
    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            width), 20}};
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
    const double speed = 1.0;
    double width = Config::GetInstance().GetScreenWidth() /
        static_cast<double>(Config::GetInstance().GetNumMidiNotes());
    double x_pos = (note - Config::GetInstance().GetMinimumMidiNote()) * width;
    double height = duration * (Config::GetInstance().GetFramesPerSecond()
            * speed);

    GameObject* song_note;
    sf::RectangleShape* rect;
    song_note = new GameObject{x_pos, -height};
    rect = new sf::RectangleShape{{static_cast<float>(width),
        static_cast<float>(height)}};
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, true, chan, note
            , vel});
    song_note->SetComponent(new GraphicsComponent{rect});
    song_note->SetComponent(new PhysicsComponent{0, speed});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new CollisionDetectorComponent{});
    song_note->SetComponent(new SongNoteCollisionHandlerComponent{});
    return song_note;
}

}  // End namespace midistar
