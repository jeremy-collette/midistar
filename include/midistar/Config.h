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

#ifndef MIDISTAR_CONFIG_H_
#define MIDISTAR_CONFIG_H_

#include <string>
#include <CLI/CLI.hpp>
#include <SFML/Graphics.hpp>

namespace midistar {

/**
 * The Config class provides an interface for reading and writing configurable
 * settings.
 */
class Config {
 public:
    /**
     * Gets the Config singleton.
     *
     * \return Config singleton instance.
     */
    static Config& GetInstance();

    /**
     * Gets the audio driver name.
     *
     * \return Audio driver name.
     */
    const std::string GetAudioDriver();

    /**
     * Gets a bool indicating whether or not notes should be automatically
     * played.
     *
     * \return Automatically play setting.
     */
    bool GetAutomaticallyPlay();

    /**
     * Gets the maximum number of frames per second (FPS) for the SFML window.
     *
     * \return Maximum FPS.
     */
    int GetMaximumFramesPerSecond();

    /**
     * Gets the maxmimum MIDI note to be displayed on the screen.
     *
     * \return Maximum MIDI note.
     */
    int GetMaximumMidiNote();

    /**
     * Gets the MIDI channel to play.
     *
     * \return MIDI channel.
     */
    int GetMidiChannel();

    /**
     * Gets the MIDI file name to be played by the player.
     *
     * \return MIDI file name.
     */
    const std::string GetMidiFileName();

    /**
     * Gets a value determining if the MIDI file should be continuously
     * repeated.
     *
     * \return Repeat MIDI file setting.
     */
    bool GetMidiFileRepeat();

    /**
     * Gets the number of MIDI file ticks (per quarter note) per one unit of
     * speed. The higher this value is set, the slower MIDI notes will fall.
     * The lower the this value is set, the faster MIDI notes will fall.
     *
     * \return MIDI ticks (per quarter note) per unit of speed.
     */
    int GetMidiFileTicksPerUnitOfSpeed();

    /**
     * Gets the velocity of MIDI notes output by the game.
     *
     * \return MIDI out velocity.
     */
    int GetMidiOutVelocity();

    /**
     * Gets the MIDI track to play.
     *
     * \return MIDI file track.
     */
    int GetMidiTrack();

    /**
     * Gets the minimum MIDI note to be displayed on the screen.
     *
     * \return Minimum MIDI note.
     */
    int GetMinimumMidiNote();

    /**
     * Gets the fall speed of song notes.
     *
     * \return Note fall speed.
     */
    double GetNoteFallSpeed();

    /**
     * Gets the number of MIDI notes between (inclusive) the minimum and
     * maximum.
     *
     * \return Number of MIDI notes.
     */
    int GetNumMidiNotes();

    /**
     * Gets the height of the screen.
     *
     * \return Screen height.
     */
    int GetScreenHeight();

    /**
     * Gets the screen size.
     *
     * \param[out] width Screen width.
     * \param[out] height Screen height.
     */
    void GetScreenSize(int* width, int* height);

    /**
     * Gets the width of the screen.
     *
     * \return Screen width.
     */
    int GetScreenWidth();

    /**
     * Gets the SoundFont path used to create MIDI sounds.
     *
     * \return MIDI SoundFont path.
     */
    const std::string GetSoundFontPath();

    /**
     * Converts a MIDI note to the instrument mapping on the keyboard.
     *
     * \param midi_note The MIDI note.
     * \param control Determines whether or not CONTROL is being pressed.
     * \param shift Determines whether or not SHIFT is being pressed.
     *
     * \return A keyboard note mapping.
     */
    sf::Keyboard::Key MidiNoteToKeyboardKey(
            int midi_note
            , bool control
            , bool shift);

    /**
     * Parses commandline arguments.
     *
     * \param argc Number of arguments.
     * \param argv Arguments.
     *
     * \return 0 for success. Other values for failure.
     */
    int ParseOptions(int argc, char** argv);

 private:
    static const int MIDI_OUT_VELOCITY = 127;  //!< MIDI out velocity
    static const int NUM_MAPPED_KEYS = 45;  //!< Number of keys mapped
    static const int MIDI_FILE_TICKS_PER_SPEED = 120;  //!< Number of MIDI file
                                               //!< ticks per one unit of speed
    static const sf::Keyboard::Key MAPPED_KEYS[NUM_MAPPED_KEYS];
                                            //!< The mapped keys on a keyboard

    static Config instance_;  //!< Holds singleton instance of Config

    Config();  //!< Constructor
    void InitCliApp(CLI::App* app);  //!< Sets up App instance for config /
                                                      //!< command line parsing

    std::string audio_driver_;  //!< Audio driver name
    bool auto_play_;  //!< Auto play setting
    int keyboard_first_note_;  //!< The first MIDI note to map on the keyboard
    int max_frames_per_second_;  //!< Max FPS
    int midi_channel_;  //!< MIDI channel to play
    std::string midi_file_name_;  //!< MIDI file being played by user
    bool midi_file_repeat_;  //!< Continuously repeats MIDI file being played
    int midi_highest_note_;  //!< The highest MIDI note to support
    int midi_lowest_note_;  //!< The lowest MIDI note to support
    int midi_track_;  //!< MIDI track to play
    double note_fall_speed_;  //!< Fall speed of notes on the screen
    int screen_height_;  //!< Screen height
    int screen_width_;  //!< Screen width
    std::string soundfont_path_;  //!< Path of SoundFont file for MIDI notes
};

}   // End namespace midistar

#endif  // MIDISTAR_CONFIG_H_
