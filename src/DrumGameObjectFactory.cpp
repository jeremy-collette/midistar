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

#include "midistar/DrumGameObjectFactory.h"

#include <algorithm>
#include <cassert>

#include "midistar/CollidableComponent.h"
#include "midistar/Config.h"
#include "midistar/DeleteOffscreenComponent.h"
#include "midistar/DrumSongNoteCollisionHandlerComponent.h"
#include "midistar/FadeOutEffectComponent.h"
#include "midistar/Game.h"
#include "midistar/InstrumentAutoPlayComponent.h"
#include "midistar/InstrumentComponent.h"
#include "midistar/InstrumentInputHandlerComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/OutlineEffectComponent.h"
#include "midistar/PhysicsComponent.h"
#include "midistar/ResizeComponent.h"
#include "midistar/ShrinkGrowComponent.h"
#include "midistar/SongNoteComponent.h"
#include "midistar/Utility.h"
#include "midistar/VerticalCollisionDetectorComponent.h"

namespace midistar {

const sf::Color DrumGameObjectFactory::BACKGROUND_COLOUR{ 40, 40, 40 };

const sf::Color DrumGameObjectFactory::DRUM_COLOURS[NUM_DRUM_COLOURS] {
    sf::Color{244, 66, 66}, sf::Color{66, 244, 69}, sf::Color{66, 164, 244}
    , sf::Color{244, 244, 65}, sf::Color{88, 65, 244}, sf::Color{65, 235, 244}
};

const sf::Color DrumGameObjectFactory::INSTRUMENT_FILL_COLOUR{ 150, 150, 150 };

const sf::Color DrumGameObjectFactory::OUTLINE_COLOUR{ 0, 0, 0 };

DrumGameObjectFactory::DrumGameObjectFactory(
    double note_speed
    , const std::vector<int>& song_notes
    , double)
        : GameObjectFactory{note_speed, BACKGROUND_COLOUR}
        , drum_radius_{Config::GetInstance().GetScreenWidth() /
            static_cast<double>(song_notes.size())}
        , song_notes_{song_notes} {
    double max_drum_radius = std::min(Config::GetInstance().GetScreenHeight()
        , Config::GetInstance().GetScreenWidth()) * MAX_DRUM_RADIUS_PERCENT;
    drum_radius_ = std::min(drum_radius_, max_drum_radius);
    x_pos_offset_ = Config::GetInstance().GetScreenWidth() / 2  -
        (song_notes.size() * drum_radius_);
}

GameObject* DrumGameObjectFactory::CreateNotePlayEffect(GameObject* note) {
    auto circle = note->GetDrawformable<sf::CircleShape>();
    if (!circle) {
        auto rect = new sf::RectangleShape{{0, 0}};
        return new GameObject{rect, 0, 0, 0, 0};
    }

    double w, h;
    note->GetSize(&w, &h);
    double x_pos, y_pos;
    note->GetPosition(&x_pos, &y_pos);
    auto* effect_circle = new sf::CircleShape{static_cast<float>(w) / 2.0f};
    effect_circle->setPosition({static_cast<float>(x_pos)
        , static_cast<float>(y_pos)});
    effect_circle->setFillColor(sf::Color::White);
    auto effect_object = new GameObject{effect_circle, x_pos, y_pos, w, h};
    effect_object->SetComponent(new FadeOutEffectComponent{});
    effect_object->SetComponent(new ShrinkGrowComponent{w * 1.25f, h * 1.25f});
    return effect_object;
}

std::vector<GameObject*> DrumGameObjectFactory::CreateInstrument() {
    std::vector<GameObject*> result;
    for (int key : song_notes_) {
        result.push_back(CreateInstrumentNote(key));
    }
    return result;
}

GameObject* DrumGameObjectFactory::CreateSongNote(
        int track
        , int chan
        , int note
        , int vel
        , double) {
    // Create underlying shape
    double x = GetXPosition(note);
    double padding_px = drum_radius_ * DRUM_PADDING_PERCENT;
    double padded_radius = drum_radius_ - padding_px * 2;
    sf::CircleShape* circle = new sf::CircleShape{ static_cast<float>(
        padded_radius) };

    auto colour = DRUM_COLOURS[GetNoteUniqueIndex(note) % NUM_DRUM_COLOURS];
    circle->setFillColor(colour);
    circle->setOutlineColor(OUTLINE_COLOUR);
    circle->setOutlineThickness(NOTE_OUTLINE_THICKNESS);

    // Create GameObject
    // Height is derived by note duration and speed (note should move its
    // entire height over its duration).
    auto y_pos = -padded_radius * 2.0f;
    auto song_note = new GameObject{ circle, x + padding_px, y_pos
        , padded_radius * 2.0f, padded_radius * 2.0f};
    song_note->AddTag("SongNote");

    // Add components
    song_note->SetComponent(new SongNoteComponent{});
    song_note->SetComponent(new CollidableComponent{});
    song_note->SetComponent(new NoteInfoComponent{track, chan, note, vel});
    song_note->SetComponent(new PhysicsComponent{0, GetNoteSpeed()});
    song_note->SetComponent(new DeleteOffscreenComponent{});
    song_note->SetComponent(new VerticalCollisionDetectorComponent{});
    song_note->SetComponent(new DrumSongNoteCollisionHandlerComponent{ this });
    return song_note;
}

GameObject* DrumGameObjectFactory::CreateInstrumentNote(int note) {
    // Create underlying shape
    double x = GetXPosition(note);
    double y = Config::GetInstance().GetScreenHeight() - (drum_radius_ * 2.0f) -
        (Config::GetInstance().GetScreenHeight() * INSTRUMENT_HOVER_PERCENTAGE);

    double padding_px = drum_radius_ * DRUM_PADDING_PERCENT;
    double padded_radius = drum_radius_ - padding_px * 2;
    sf::CircleShape* circle = new sf::CircleShape{ static_cast<float>(
        padded_radius) };
    circle->setFillColor(INSTRUMENT_FILL_COLOUR);
    circle->setOutlineColor(DRUM_COLOURS[GetNoteUniqueIndex(note) %
        NUM_DRUM_COLOURS]);
    circle->setOutlineThickness(INSTRUMENT_OUTLINE_THICKNESS);

    // Create GameObject
    auto ins_note = new GameObject{circle, x + padding_px, y
        , padded_radius * 2.0f, padded_radius * 2.0f};

    // Get key binding
    sf::Keyboard::Key key;
    bool ctrl, shift;
    GetInstrumentKeyBinding(note, &key, &ctrl, &shift);

    // Add components
    ins_note->SetComponent(new InstrumentComponent{});
    ins_note->SetComponent(new NoteInfoComponent{-1, 9, note
            , Config::GetInstance().GetMidiOutVelocity()});
    ins_note->SetComponent(new InstrumentInputHandlerComponent{key, ctrl
            , shift});
    ins_note->SetComponent(new VerticalCollisionDetectorComponent{});
    ins_note->SetComponent(new InstrumentAutoPlayComponent{
            InstrumentAutoPlayComponent::CollisionCriteria::CENTRE});
    return ins_note;
}

void DrumGameObjectFactory::GetInstrumentKeyBinding(
        int midi_key
        , sf::Keyboard::Key* key
        , bool* ctrl
        , bool* shift) {
    const std::vector<sf::Keyboard::Key>& keys = Utility::GetQwertyKeys();
    assert(keys.size() >= song_notes_.size());

    // Get the key
    int idx = GetNoteUniqueIndex(midi_key);
    *key = keys[idx];
    *ctrl = false;
    *shift = false;
}

int DrumGameObjectFactory::GetNoteUniqueIndex(int note) {
    auto pos = std::find(song_notes_.begin(), song_notes_.end(), note);
    assert(pos != song_notes_.end());
    return static_cast<int>(pos - song_notes_.begin());
}

double DrumGameObjectFactory::GetXPosition(int note) {
    return x_pos_offset_ + GetNoteUniqueIndex(note) * (drum_radius_ * 2);
}

bool DrumGameObjectFactory::Init() {
    // We have nothing to initialise...
    return true;
}

}  // End namespace midistar
