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

#include "midistar/NoteInfoComponent.h"

namespace midistar {

NoteInfoComponent::NoteInfoComponent(
    int track
    , bool on
    , int chan
    , int note
    , int vel)
        : Component{Component::NOTE_INFO_COMPONENT}
        , chan_{chan}
        , note_{note}
        , on_{on}
        , track_{track}
        , vel_{vel} {
}

int NoteInfoComponent::GetChannel() {
    return chan_;
}

bool NoteInfoComponent::GetIsOn() {
    return on_;
}

int NoteInfoComponent::GetKey() {
    return note_;
}

int NoteInfoComponent::GetTrack() {
    return track_;
}

int NoteInfoComponent::GetVelocity() {
    return vel_;
}

void NoteInfoComponent::Update(Game*, GameObject*) {
}

}  // End namespace midistar
