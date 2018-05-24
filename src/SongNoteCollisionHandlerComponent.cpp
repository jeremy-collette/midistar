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

#include "midistar/SongNoteCollisionHandlerComponent.h"

#include <algorithm>

#include "midistar/CollisionDetectorComponent.h"
#include "midistar/Config.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"

namespace midistar {

SongNoteCollisionHandlerComponent::SongNoteCollisionHandlerComponent()
        : CollisionHandlerComponent{
            Component::NOTE_COLLISION_HANDLER}
        , auto_playing_{false} {
}

void SongNoteCollisionHandlerComponent::HandleCollisions(
        Game* g
        , GameObject* o
        , std::vector<GameObject*> colliding_with) {
    // Get some info about owner
    auto note = o->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO);
    if (!note) {
        return;
    }

    auto graphics = o->GetComponent<GraphicsComponent>(
        Component::GRAPHICS);
    if (!graphics) {
        return;
    }
    double x, y;
    o->GetPosition(&x, &y);

    double width, height;
    graphics->GetSize(&width, &height);

    // Get the bar object, for later use.
    GameObject* bar = g->GetInstrumentBar();
    double bar_x, bar_y;
    bar->GetPosition(&bar_x, &bar_y);

    auto bar_graphics = bar->GetComponent<GraphicsComponent>(
            Component::GRAPHICS);
    if (!bar_graphics) {
        return;
    }
    double bar_width, bar_height;
    bar_graphics->GetSize(&bar_width, &bar_height);

    // Handle each collision
    for (auto& collider : colliding_with) {
        auto other_note = collider->GetComponent<NoteInfoComponent>(
                Component::NOTE_INFO);

        // Here we check if the note is being played. If the note is colliding
        // with an instrument, it's being played. Once it is being played, we
        // anchor the note to the bar so that it shrinks during play.
        if (collider->HasComponent(Component::INSTRUMENT)) {
            // Check it's the correct instrument - we may collide with
            // neighbouring instruments if they overlap on the screen.
            if (!other_note || other_note->GetKey() != note->GetKey()) {
                return;
            }

            // If the bottom of the note is past the bottom of the bar,
            // separate the part below the bar in to a different (unplayable)
            // note. This section of the note has been missed.
            if (y + height > bar_y + bar_height) {
                auto note = o->GetComponent<NoteInfoComponent>(
                        Component::NOTE_INFO);
                if (!note) {
                    return;
                }

                GameObject* half = GameObjectFactory::CreateSongNote(
                            note->GetTrack()
                            , note->GetIsOn()
                            , note->GetChannel()
                            , note->GetKey()
                            , note->GetVelocity());

                // We don't want complete note behaviour - this is an
                // unplayable note
                half->DeleteComponent(
                        Component::NOTE_COLLISION_HANDLER);
                half->SetPosition(x, bar_y + bar_height);

                auto half_graphics = half->GetComponent<
                    GraphicsComponent>(Component::GRAPHICS);
                if (!half_graphics) {
                    return;
                }

                half_graphics->SetSize(
                        width
                        , (y + height) - (bar_y + bar_height));
                g->AddGameObject(half);
            }

            // Now we are guaranteed to have a note that ends before the bottom
            // of the bar (see above).
            //
            // If the top of the note is before the bar:
            if (y < bar_y) {
                // Resize the note so that it is not intersecting the bar and
                // add an anchor component anchored to the top of the bar.
                o->SetComponent(new ResizeComponent{width, bar_y-y});
            } else {  // Otherwise 'o' is now purely within the bar and
                     // can be removed.
                o->SetComponent(new ResizeComponent{0, 0});
            }
        // Handle auto play
        } else if (collider == bar
                && Config::GetInstance().GetAutomaticallyPlay()) {
            if (!auto_playing_) {  // Auto play plays the note
                o->SetComponent(new MidiNoteComponent{
                        true
                        , note->GetChannel()
                        , note->GetKey()
                        , note->GetVelocity()});
                auto_playing_ = true;
            } else if (y > bar_y) {  // If our top is inside the bar, stop
                                                                    // playing
                o->SetComponent(new MidiNoteComponent{
                        false
                        , note->GetChannel()
                        , note->GetKey()
                        , note->GetVelocity()});

                o->DeleteComponent(GetType());
            }
        }
    }
}

}  // End namespace midistar
