/*
 * midistar
 * Copyright (C) 2018-2023 Jeremy Collette.
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

#ifndef MIDISTAR_MIDIFILEINCOMPONENT_H_
#define MIDISTAR_MIDIFILEINCOMPONENT_H_

#include <vector>

#include "midistar/Component.h"
#include "midistar/GameObject.h"
#include "midistar/MidiFileIn.h"
#include "midistar/MidiMessage.h"

namespace midistar {

/**
 * The MidiFileInComponent allows the reading of MIDI files.
 */
class MidiFileInComponent : public Component {
 public:
     explicit MidiFileInComponent(MidiFileIn* midi_file_in);

     ~MidiFileInComponent();

     double GetMaximumNoteDuration() const;

     const std::vector<MidiMessage>& GetMessages() const;

     int GetTicksPerQuarterNote() const;

     std::vector<int> GetUniqueMidiNotes() const;

     bool IsEof() const;

    /**
     * \copydoc Component::Update()
     */
    virtual void Update(Game* g, GameObject* o, int delta);

 private:
    std::vector<MidiMessage> message_buffer_;
    MidiFileIn* midi_file_in_;
};

}   // End namespace midistar

#endif  // MIDISTAR_MIDIFILEINCOMPONENT_H_
