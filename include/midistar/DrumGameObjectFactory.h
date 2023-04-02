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

#ifndef MIDISTAR_DRUMGAMEOBJECTFACTORY_H_
#define MIDISTAR_DRUMGAMEOBJECTFACTORY_H_

#include <set>
#include <vector>
#include <SFML/Window.hpp>

#include "midistar/GameObject.h"
#include "midistar/GameObjectFactory.h"

namespace midistar {

/**
 * The DrumGameObjectFactory class creates GameObjects with default
 * behaviours.
 */
class DrumGameObjectFactory : public GameObjectFactory {
 public:
    /**
     * Constructor
     *
     * \param note_speed The falling speed of notes.
     * \param song_notes Unique MIDI notes in the song.
     * \param max_note_duration The maximum duration of any MIDI note in the
     * song.
     */
    explicit DrumGameObjectFactory(
            double note_speed
            , const std::vector<int>& song_notes
            , double max_note_duration);

    /**
     * \copydoc GameObjectFactory::CreateNotePlayEffect()
     */
    virtual GameObject* CreateNotePlayEffect(GameObject* o);

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

    /**
     * \copydoc GameObjectFactory::Init()
     */
    virtual bool Init();

 private:
    static const sf::Color BACKGROUND_COLOUR;  //!< Background colour
    static constexpr float DRUM_PADDING_PERCENT = 0.1f;  //!< Padding percentage
    static constexpr double MAX_DRUM_RADIUS_PERCENT = 0.1;  //!< Max radius of
          //!< drum notes and instruments as a percentage of the size of the
                                                                     //!< screen
    static const sf::Color INSTRUMENT_FILL_COLOUR;  //!< Drum fill colour
    static constexpr float INSTRUMENT_HOVER_PERCENTAGE = 0.1f;  //!< The
             //!< percentage of the screen height that instruments will hover
    static constexpr float INSTRUMENT_OUTLINE_THICKNESS = -10.0f;  //!< Outline
                                                        //!< thickness of drums
    static const int NUM_DRUM_COLOURS = 6;  //!< Num drum colours
    static constexpr float NOTE_OUTLINE_THICKNESS = -3.0f;  //!< Outline
                                                    //!< thickness of notes
    static const int NUM_MIDI_KEYS = 128;  //!< Maximum MIDI key
    static const sf::Color OUTLINE_COLOUR;  //!< Outline colour

    static const sf::Color DRUM_COLOURS[NUM_DRUM_COLOURS];  //!< Holds drum
                                                                  //!< colours

    GameObject* CreatePhantomInstrumentNotes(std::set<int> midi_keys);
      //!< Handles MIDI input for non-visible drums (i.e. drums that are not
                                                //!< used in the current song).
    GameObject* CreateInstrumentNote(int midi_key);  //!< Creates a note for
                                 //!< the instrument with the given MIDI key
    void GetInstrumentKeyBinding(int midi_key, sf::Keyboard::Key* key,
            bool* ctrl, bool* shift);  //!< Gets instrument key binding
    int GetNoteUniqueIndex(int note);  //!< Gets MIDI note index in list of
                                                 //!< unique notes for the song
    double GetXPosition(int note);  //!< Gets the X position of a song
                                                         //!< note / instrument
    void SortDrumInstrumentNotes(); //!< Sorts drum instrument notes by the
    //!< order specified in the Config (if it has been specified)

    double drum_radius_;  //!< Holds the radius of drum notes / instruments
    std::vector<int> song_notes_;  //!< Unique MIDI notes in the song
    double x_pos_offset_;  //!< Defines offset for X coord for note and
                                                                //!< instruments
};

}  // End namespace midistar

#endif  // MIDISTAR_DRUMGAMEOBJECTFACTORY_H_
