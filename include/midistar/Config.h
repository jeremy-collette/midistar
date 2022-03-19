/*
 * midistar
 * Copyright (C) 2018-2022 Jeremy Collette.
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
#include <unordered_map>
#include <vector>
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
     * Gets the specified order of drums by MIDI key.
     *
     * \return Drum instrument order using MIDI key.
     */
    std::vector<int> GetDrumMidiOrder();

    /**
     * Gets a bool indicating whether or not title screen background music
     * should be played.
     *
     * \return Play title screen background music.
     */
    bool GetEnableTitleMusic();

    /**
     * Gets the fall speed multiplier. This affects the fall speed of song
     * notes.
     *
     * \return Fall speed multiplier.
     */
    double GetFallSpeedMultiplier();

    /**
     * Gets the max delta before frame delta should be ignored.
     *
     * \return Max frame delta.
     */
    int GetFrameMaxDelta();

    /**
     * Gets a bool indicating whether or not full-screen mode is enabled.
     *
     * \return Full-screen mode.
     */
    bool GetFullScreen();

    const std::string GetIconPath();

    /**
     * Gets the MIDI note re-mapping (if it exists) of a note played on an
     * instrument.
     *
     * \param note The actual MIDI note played on the instrument.
     * \return The MIDI note it is mapped to in midistar. If there is no re-
     * mapping, returns the original note.
     */
    int GetInstrumentMidiNoteRemapping(int note);

    /**
     * Gets the maximum number of frames per second (FPS) for the SFML window.
     *
     * \return Maximum FPS.
     */
    int GetMaximumFramesPerSecond();

    /**
     * Gets the MIDI file channels to play.
     *
     * \return MIDI file channels.
     */
    std::vector<int> GetMidiFileChannels();

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
     * Gets the MIDI file tracks to play.
     *
     * \return MIDI file tracks.
     */
    std::vector<int> GetMidiFileTracks();

    /**
     * Gets the MIDI port to read instrument notes from.
     *
     * \return MIDI input port.
     */
    int GetMidiInputPort();

    /**
     * Gets the MIDI output insturment mapping (channel -> instrument).
     *
     * \return MIDI output insturment mapping.
     */
    const std::unordered_map<int, int>& GetMidiOutputInstrumentMapping();

    /**
     * Gets the velocity of MIDI notes output by the game.
     *
     * \return MIDI out velocity.
     */
    int GetMidiOutVelocity();

    bool GetPracticeMode();

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
     * Gets an indication if whether or not the 'show third party' flag was
     * passed in.
     *
     * \return True if 'show third party' flag was used. False otherwise.
     */
    bool GetShowThirdParty();

    /**
     * Gets the SoundFont path used to create MIDI sounds.
     *
     * \return MIDI SoundFont path.
     */
    const std::string GetSoundFontPath();

    /**
     * Returns the path to the MIDI file to be played as title screen background
     * music.
     *
     * \return Title screen background music MIDI file path.
     */
    const std::string GetTitleMusicMidiFilePath();

    /**
     * Parses commandline arguments.
     *
     * \param argc Number of arguments.
     * \param argv Arguments.
     *
     * \return true for success. false for failure.
     */
    bool ParseOptions(int argc, char** argv);

 private:
    static const int MIDI_OUT_VELOCITY = 127;  //!< MIDI out velocity
    static const int MIDI_FILE_TICKS_PER_SPEED = 120;  //!< Number of MIDI file
                                               //!< ticks per one unit of speed

    static Config instance_;  //!< Holds singleton instance of Config

    Config();  //!< Constructor
    void InitCliApp(CLI::App* app);  //!< Sets up App instance for config /
                                                      //!< command line parsing

    std::string audio_driver_;  //!< Audio driver name
    bool auto_play_;  //!< Auto play setting
    std::vector<int> drum_midi_order_;  //!< Order of drums on screen by key
    bool enable_title_music_;  //!< Enable title background music
    double fall_speed_multiplier_;  //!< Affects fall speed of notes
    int frame_max_delta_;  //!< Max delta before delta is ignored (game not
                                                                 //!< updated).
    bool full_screen_;  //!< Full-screen setting
    std::string icon_path_;
    std::unordered_map<int, int> instrument_midi_remapping_;  //!< MIDI
                                    //!< remapping derived from commandline arg
    std::vector<int> instrument_midi_remapping_notes_;  //!< MIDI remapping
                                                           //!< commandline arg
    int keyboard_first_note_;  //!< The first MIDI note to map on the keyboard
    int max_frames_per_second_;  //!< Max FPS
    int midi_input_port_;  //!< MIDI input port for instrument input
    std::unordered_map<int, int> midi_output_inst_map_;  //!< Mapping from MIDI
                                                    //!< channel to instrument
    std::vector<int> midi_output_inst_indexes_;  //!< Raw MIDI instrument map
    std::vector<int> midi_file_channels_;  //!< MIDI file channels to play
    bool midi_file_repeat_;  //!< Continuously repeats MIDI file being played
    std::vector<int> midi_file_tracks_;  //!< MIDI tracks to play
    bool practice_mode_;
    int screen_height_;  //!< Screen height
    int screen_width_;  //!< Screen width
    bool show_third_party_;  //!< Determines whether or not to print out third-
                                                    //!< party copyright notices
    std::string soundfont_path_;  //!< Path of SoundFont file for MIDI notes
    std::string title_music_midi_file_;  //!< Path to MIDI file to use for title
                                                                      //!< music
};

}   // End namespace midistar

#endif  // MIDISTAR_CONFIG_H_
