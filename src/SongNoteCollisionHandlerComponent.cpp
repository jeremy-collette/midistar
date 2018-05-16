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

#include "midistar/AnchorComponent.h"
#include "midistar/CollisionDetectorComponent.h"
#include "midistar/Config.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/MidiNoteComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"

namespace Midistar {

SongNoteCollisionHandlerComponent::SongNoteCollisionHandlerComponent()
        : CollisionHandlerComponent{
            Component::NOTE_COLLISION_HANDLER_COMPONENT} {
}

void SongNoteCollisionHandlerComponent::HandleCollision(
        Game* g
        , GameObject* o
        , GameObject* colliding_with) {
    auto note = o->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO_COMPONENT);
    if (!note) {
        return;
    }

    auto other_note = colliding_with->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO_COMPONENT);

    auto graphics = o->GetComponent<GraphicsComponent>(
        Component::GRAPHICS_COMPONENT);
    if (!graphics) {
        return;
    }

    // Get the bar object, for later use.
    GameObject* bar = nullptr;
    for (auto& obj : g->GetGameObjects()) {
        if (obj->HasComponent(Component::BAR_COMPONENT)) {
            bar = obj;
            break;
        }
    }

    // Here we check if the note is being played. If the note is colliding with
    // an instrument, it's being played. Once it is being played, we anchor the
    // note to the bar so that it shrinks during play.
    if (colliding_with->HasComponent(Component::INSTRUMENT_COMPONENT)) {
        // Check it's the correct instrument - we may collide with neighbouring
        // instruments if they overlap on the screen.
        if (!other_note || other_note->GetKey() != note->GetKey()) {
            return;
        }

        // Anchor the note to the bar.
        // If we already have an anchor component, we've already anchored
        // to something (likely the bar)
        if (!o->HasComponent(Component::ANCHOR_COMPONENT)) {
            double x, y;
            o->GetPosition(&x, &y);

            double width, height;
            graphics->GetSize(&width, &height);

            double bar_x, bar_y;
            bar->GetPosition(&bar_x, &bar_y);

            auto bar_graphics = bar->GetComponent<GraphicsComponent>(
                    Component::GRAPHICS_COMPONENT);
            if (!bar_graphics) {
                return;
            }
            double bar_width, bar_height;
            bar_graphics->GetSize(&bar_width, &bar_height);

            // If the bottom of the note is past the bottom of the bar,
            // separate the part below the bar in to a different
            // (unplayable) note. This section of the note has been
            // missed.
            if (y + height > bar_y + bar_height) {
                auto note = o->GetComponent<NoteInfoComponent>(
                        Component::NOTE_INFO_COMPONENT);
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
                half->DeleteComponent(Component::ANCHOR_COMPONENT);
                half->DeleteComponent(
                        Component::NOTE_COLLISION_HANDLER_COMPONENT);
                half->SetPosition(x, bar_y + bar_height);

                auto half_graphics = half->GetComponent<
                    GraphicsComponent>(Component::GRAPHICS_COMPONENT);
                if (!half_graphics) {
                    return;
                }

                half_graphics->SetSize(
                        width
                        , (y + height) - (bar_y + bar_height));
                g->AddGameObject(half);
            }

            // Now we are guaranteed to have a note that ends before the
            // bottom of the bar (see above).
            //
            // If the top of the note is before the bar:
            if (y < bar_y) {
                // Resize the note so that it is not intersecting the
                // bar and add an anchor component anchored to the top
                // of the bar.
                o->SetComponent(new ResizeComponent{width, bar_y-y});
                o->SetComponent(new AnchorComponent{
                        x
                        , bar_y
                        , AnchorComponent::FALLING});
            } else { // Otherwise 'o' is now purely within the bar and
                     // can be removed.
                o->SetComponent(new ResizeComponent{0, 0});
            }
        }
    } else if (colliding_with == bar) {
        if (Config::GetInstance().GetAutomaticallyPlay()) {  // Auto play plays
                                                                    // the note
            o->SetComponent(new MidiNoteComponent{
                    note->GetIsOn()
                    , note->GetChannel()
                    , note->GetKey()
                    , note->GetVelocity()});
            o->DeleteComponent(GetType());
        } else {
            // If we're colliding with the bar, but we're not colliding with an
            // instrument, we should delete our anchor component. If we're not
            // colliding the bar, we might be using an anchor component for
            // other purposes (e.g. note expansion).
            auto detector = o->GetComponent<CollisionDetectorComponent>(
                    Component::COLLISION_DETECTOR_COMPONENT);
            if (!detector) {
                return;
            }

            bool found_inst = false;
            auto collisions = detector->GetCollidingWith();
            for (const auto& obj : collisions) {
                if (obj->HasComponent(Component::SONG_NOTE_COMPONENT)) {
                    found_inst = true;
                    break;
                }
            }
            if (!found_inst) {
                o->DeleteComponent(Component::ANCHOR_COMPONENT);
            }
        }
    }
}

}  // End namespace Midistar
