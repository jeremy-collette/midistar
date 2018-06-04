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

#ifndef MIDISTAR_PIANOGAMEOBJECTFACTORY_H_
#define MIDISTAR_PIANOGAMEOBJECTFACTORY_H_

#include <vector>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The PianoGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class PianoGameObjectFactory : public GameObjectFactory {
 public:
   /**
    * Constructor
    */
    explicit PianoGameObjectFactory(double note_speed);

    /**
     * \copydoc GameObjectFactory::CreateInstrumentBar()
     */
    virtual GameObject* CreateInstrumentBar();

    /**
     * \copydoc GameObjectFactory::CreateInstrument()
     */
    virtual std::vector<GameObject*> CreateInstrument();

    /**
     * \copydoc GameObjectFactory::CreateSongNote()
     */
    virtual GameObject* CreateSongNote(
            int track
            , int chan
            , int note
            , int vel
            , double duration);

 private:
    static const char BLACK_KEY_HEIGHT = 50;  //!< Black key height in pixels
    static const char NOTES_PER_OCTAVE = 12;  //!< Notes in an octave
    static const char NUM_BLACK_KEYS = 36;  //!< Num black keys on a piano
    static const char NUM_PIANO_KEYS = 88;  //!< Total num keys on a piano
    static const char NUM_WHITE_KEYS = NUM_PIANO_KEYS - NUM_BLACK_KEYS; 
                                                //!< Num white keys on a piano
    static const bool OCTAVE_BLACK_KEYS[NOTES_PER_OCTAVE];  //!< Black key 
                                                      //!< lookup in an octave
    static const char OCTAVE_KEY_TO_WHITE_KEY[NOTES_PER_OCTAVE];  //!< Converts
                                      //!< a key index to the closest white key
    static const char PIANO_FIRST_MIDI_KEY = 21;  //!< First MIDI key on a 
                                                                    //!< piano
    static const char WHITE_KEY_HEIGHT = 80;  //!< White key height in pixels
    static const char WHITE_KEYS_PER_OCTAVE = 7;  //!< White keys in an octave
    
    static int GetWhiteKeyIndex(int midi_key);  //!< Gets the index of the 
                                    //!< closest white piano key to a MIDI key
    static bool IsBlackKey(int midi_key);  //!< Determines if a MIDI key
                                        //!< correlates with a black piano key

    double CalculateXPosition(int midi_key);  //!< Calculates note / instrument
                                                                //!< X position
    GameObject* CreateInstrumentNote(int midi_key);  //!< Creates a note for 
                                                                 //!< the piano

    double note_width_;  //!< Holds the width of song notes
};

}  // End namespace midistar

#endif  // MIDISTAR_PIANOGAMEOBJECTFACTORY_H_
