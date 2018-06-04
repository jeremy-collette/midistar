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

#include <cassert>

#include "midistar/PianoGameObjectFactory.h"

#include "midistar/BarComponent.h"
#include "midistar/CollidableComponent.h"
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

const bool PianoGameObjectFactory::OCTAVE_BLACK_KEYS[NOTES_PER_OCTAVE] {
    0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1
};

const char PianoGameObjectFactory::OCTAVE_KEY_TO_WHITE_KEY[NOTES_PER_OCTAVE] {
    0, 0, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6
};

PianoGameObjectFactory::PianoGameObjectFactory(double note_speed)
        : GameObjectFactory{note_speed}
        , note_width_{Config::GetInstance().GetScreenWidth() /
            static_cast<double>(NUM_WHITE_KEYS)} {
}

GameObject* PianoGameObjectFactory::CreateInstrumentBar() {
    double x = 0;
    double y = Config::GetInstance().GetScreenHeight()-100.0;
    GameObject* bar = new GameObject{x, y};
    bar->SetComponent(new BarComponent{});

    sf::RectangleShape* rect = new sf::RectangleShape{
        {static_cast<float>(Config::GetInstance().GetScreenWidth())
        , WHITE_KEY_HEIGHT}};
    rect->setPosition({static_cast<float>(x), static_cast<float>(y)});
    rect->setFillColor(sf::Color::Red);
    bar->SetComponent(new CollidableComponent{});
    bar->SetComponent(new GraphicsComponent{rect});
    return bar;
}

std::vector<GameObject*> PianoGameObjectFactory::CreateInstrument() {
    std::vector<GameObject*> result;
    for (int key = PIANO_FIRST_MIDI_KEY; key < PIANO_FIRST_MIDI_KEY + 
            NUM_PIANO_KEYS; ++key) {
        GameObject* note = CreateInstrumentNote(key);
        // We put black keys after white keys so they are displayed on top
        result.insert(IsBlackKey(key) ? result.end() : result.begin(), note);
    }
    return result;
}

GameObject* PianoGameObjectFactory::CreateSongNote(
        int track
        , int chan
        , int note
        , int vel
        , double duration) {
    double x = CalculateXPosition(note);
    // Height is equal to duration in milliseconds * pixels per millisecond
    double height = duration * 1000 * GetNoteSpeed();

    GameObject* song_note = new GameObject{x, -height};
    
    // TODO(@jez): constant for colours
    sf::Color colour = sf::Color{50, 50, 200};
    double width = note_width_;
    if (IsBlackKey(note)) {
        // TODO(@jez): use constant
        colour = sf::Color{50, 200, 50};
        width /= 2;
    }

    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            width), static_cast<float>(height)}};
    rect->setPosition({static_cast<float>(x), -static_cast<float>(height)});
    rect->setFillColor(colour);
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new CollidableComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, chan, note, vel});
    song_note->SetComponent(new GraphicsComponent{rect});
    song_note->SetComponent(new PhysicsComponent{0, GetNoteSpeed()});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new CollisionDetectorComponent{});
    song_note->SetComponent(new SongNoteCollisionHandlerComponent{});
    return song_note;
}

int PianoGameObjectFactory::GetWhiteKeyIndex(int midi_key) {
    int key_index = midi_key - PIANO_FIRST_MIDI_KEY;
    int octave_num = key_index / NOTES_PER_OCTAVE;
    int prev_white_keys = octave_num * WHITE_KEYS_PER_OCTAVE;
    int octave_index = key_index % NOTES_PER_OCTAVE; 
    int result =  prev_white_keys + OCTAVE_KEY_TO_WHITE_KEY[octave_index];
    assert(result >= 0 && result < NUM_WHITE_KEYS);
    return result;
}

bool PianoGameObjectFactory::IsBlackKey(int midi_key) {
    // The OCTAVE_BLACK_KEYS array indicates black keys in a typical octave.
    // To find if a specific key is a black key, we subtract the first piano 
    // MIDI key (the MIDI key of the first key on a piano), and find the
    // remainder if we divide by NOTES_PER_OCTAVE. 
    //
    // This gives us a value between 0 and NOTES_PER_OCTAVE, that we can use
    // as an index in the OCTAVE_BALCK_KEYS array. We return the value at this
    // index.
    return OCTAVE_BLACK_KEYS[(midi_key - PIANO_FIRST_MIDI_KEY) 
        % NOTES_PER_OCTAVE];
}

double PianoGameObjectFactory::CalculateXPosition(int midi_key) {
    double white_key_index = GetWhiteKeyIndex(midi_key);
    double x = white_key_index * note_width_;
    if (IsBlackKey(midi_key)) {
        x += note_width_ / 2.0 + note_width_ / 4.0;
    }
    return x;
} 

GameObject* PianoGameObjectFactory::CreateInstrumentNote(int note) {
    double x = CalculateXPosition(note);
    double y = Config::GetInstance().GetScreenHeight()-100;
    GameObject* ins_note = new GameObject{x, y};
    ins_note->SetComponent(new InstrumentComponent{});
    ins_note->SetComponent(new NoteInfoComponent{-1, 0, note
            , Config::GetInstance().GetMidiOutVelocity()});

    double height = WHITE_KEY_HEIGHT;
    double width = note_width_;
    sf::Color colour = sf::Color::White;
    if (IsBlackKey(note)) {
        height = BLACK_KEY_HEIGHT;
        colour = sf::Color::Black; 
        width /= 2;
    }

    sf::RectangleShape* rect = new sf::RectangleShape{{static_cast<float>(
            width), static_cast<float>(height)}};
    rect->setPosition({static_cast<float>(x), static_cast<float>(y)});
    rect->setFillColor(colour);
    ins_note->SetComponent(new GraphicsComponent{rect});
    ins_note->SetComponent(new InstrumentInputHandlerComponent{});
    return ins_note;
}

}  // End namespace midistar
