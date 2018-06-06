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

#include "midistar/DefaultGameObjectFactory.h"

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

DefaultGameObjectFactory::DefaultGameObjectFactory(double note_speed)
        : GameObjectFactory{note_speed}
        , note_width_{Config::GetInstance().GetScreenWidth() /
            static_cast<double>(MAX_MIDI_KEY)} {
}

std::vector<GameObject*> DefaultGameObjectFactory::CreateInstrument() {
    std::vector<GameObject*> result;
    for (int key = 0; key <= MAX_MIDI_KEY; ++key) {
        result.push_back(CreateInstrumentNote(key));
    }
    return result;
}

GameObject* DefaultGameObjectFactory::CreateSongNote(
        int track
        , int chan
        , int note
        , int vel
        , double duration) {
    double x = note * note_width_;
    // Height is equal to duration in milliseconds * pixels per millisecond
    double height = duration * 1000 * GetNoteSpeed();

    GameObject* song_note;
    sf::RectangleShape* rect;
    song_note = new GameObject{x, -height};
    rect = new sf::RectangleShape{{static_cast<float>(note_width_)
        , static_cast<float>(height)}};
    rect->setPosition({static_cast<float>(x), -static_cast<float>(height)});
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, chan, note, vel});
    song_note->SetComponent(new GraphicsComponent{rect});
    song_note->SetComponent(new PhysicsComponent{0, GetNoteSpeed()});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new CollisionDetectorComponent{});
    song_note->SetComponent(new SongNoteCollisionHandlerComponent{});
    return song_note;
}

GameObject* DefaultGameObjectFactory::CreateInstrumentNote(int note) {
    double x = note * note_width_;
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

}  // End namespace midistar
