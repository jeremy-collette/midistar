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

#include "midistar/SongNoteAnchorRemovalComponent.h"

#include "midistar/AnchorComponent.h"
#include "midistar/GraphicsComponent.h"
#include "midistar/NoteInfoComponent.h"
#include "midistar/ResizeComponent.h"

namespace Midistar {

SongNoteAnchorRemovalComponent::SongNoteAnchorRemovalComponent()
        : Component(Component::SONG_NOTE_ANCHOR_REMOVAL_COMPONENT) {
}

void SongNoteAnchorRemovalComponent::Update(Game* g, GameObject* o) {
    auto note = o->GetComponent<NoteInfoComponent>(
            Component::NOTE_INFO_COMPONENT);
    if (!note) {
        return;
    }

    // Find any ON notes that match the MIDI note of owner
    NoteInfoComponent* previous = nullptr;
    for (const auto& obj : g->GetGameObjects()) {
        // We only want to modify song notes made BEFORE the owner
        if (obj == o) {
            break;
        }

        if (!obj->HasComponent(Component::SONG_NOTE_COMPONENT)) {
            continue;
        }

        auto other_note = obj->GetComponent<NoteInfoComponent>(
                    Component::NOTE_INFO_COMPONENT);
        if (!other_note) {
            continue;
        }

        // Delete the AnchorComponent from the first (oldest) matching object
        if (other_note->GetIsOn() && other_note->GetKey() == note->GetKey()) {
            auto anchor = obj->GetComponent<AnchorComponent>(
                    Component::ANCHOR_COMPONENT);
            if (!anchor) {
                continue;
            }

            // We only want to delete AnchorComponents that are being used to
            // expand the note (i.e. are anchored above the screen).
            double anchor_x, anchor_y;
            anchor->GetTarget(&anchor_x, &anchor_y);
            if (anchor_y > 0) {
                continue;
            }

            if (previous) {
                std::cerr << "Warning: collision between two MIDI notes "
                    << "with key " << note->GetKey() << ". Tracks: "
                    << previous->GetTrack() << " and "
                    << other_note->GetTrack() << ". Channels: "
                    << previous->GetChannel() << " and "
                    << other_note->GetChannel() << ". Consider disabling one "
                    << "of these tracks and/or channels.\n";
            }
            previous = other_note;
            obj->DeleteComponent(Component::ANCHOR_COMPONENT);  // Bon voyage!

            // We're actually intersecting with the note off object here. We
            // really want to be 1 pixel down.
            auto graphics = obj->GetComponent<GraphicsComponent>(
                    Component::GRAPHICS_COMPONENT);
            if (!graphics) {
                continue;
            }

            double width, height;
            graphics->GetSize(&width, &height);
            // We may have the situation where we have a one-pixel high on-note
            // on top of an off-note due to the midistar frame rate being too
            // slow and the MIDI file being too quick. In this case, we don't
            // want to resize the on-note because it will disappear (0 height)!
            // Thus, only resize if our height is greater than 1.
            if (height > 1) {
                obj->SetComponent(new ResizeComponent{width, height-1
                    , ResizeComponent::BOT_LEFT | ResizeComponent::BOT_RIGHT});
            } else {  // Otherwise just move down one pixel
                double x, y;
                obj->GetPosition(&x, &y);
                y += 1;
                obj->SetPosition(x, y);
            }
        }
    }

    // If we deleted atleast one AnchorComponent, our job is done!
    if (previous) {
        o->DeleteComponent(GetType());
    }
}

}  // End namespace Midistar
