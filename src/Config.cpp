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

#include "midistar/Config.h"

#include <iostream>

namespace midistar {

Config Config::instance_;

Config& Config::GetInstance() {
    return instance_;
}

Config::Config()
        : audio_driver_{""}
        , auto_play_{false}
        , fall_speed_multiplier_{0}
        , full_screen_{false}
        , instrument_midi_remapping_{}
        , instrument_midi_remapping_notes_{}
        , keyboard_first_note_{-1}
        , max_frames_per_second_{-1}
        , midi_input_port_{ 0 }
        , midi_file_channels_{}
        , midi_file_repeat_{false}
        , midi_file_tracks_{}
        , practice_mode_{ false }
        , screen_height_{-1}
        , screen_width_{-1}
        , show_third_party_{false}
        , soundfont_path_{""} {
}

const std::string Config::GetAudioDriver() {
    return audio_driver_;
}

bool Config::GetAutomaticallyPlay() {
    return auto_play_;
}

std::vector<int> Config::GetDrumMidiOrder() {
    return drum_midi_order_;
}

bool Config::GetEnableTitleMusic() {
    return enable_title_music_;
}

double Config::GetFallSpeedMultiplier() {
    return fall_speed_multiplier_;
}

int Config::GetFrameMaxDelta() {
    return frame_max_delta_;
}

bool Config::GetFullScreen() {
    return full_screen_;
}

const std::string Config::GetIconPath() {
    return icon_path_;
}

int Config::GetInstrumentMidiNoteRemapping(int note) {
    return instrument_midi_remapping_.count(note) ?
        instrument_midi_remapping_[note] : note;
}

int Config::GetMaximumFramesPerSecond() {
    return max_frames_per_second_;
}

std::vector<int> Config::GetMidiFileChannels() {
    return midi_file_channels_;
}

bool Config::GetMidiFileRepeat() {
    return midi_file_repeat_;
}

int Config::GetMidiFileTicksPerUnitOfSpeed() {
    return MIDI_FILE_TICKS_PER_SPEED;
}

std::vector<int> Config::GetMidiFileTracks() {
    return midi_file_tracks_;
}

int Config::GetMidiInputPort() {
    return midi_input_port_;
}

const std::unordered_map<int, int>& Config::GetMidiOutputInstrumentMapping() {
    return midi_output_inst_map_;
}

int Config::GetMidiOutVelocity() {
    return MIDI_OUT_VELOCITY;
}

bool Config::GetPracticeMode() {
    return practice_mode_ && !auto_play_;
}

int Config::GetScreenHeight() {
    return screen_height_;
}

void Config::GetScreenSize(int* width, int* height) {
    *width = GetScreenWidth();
    *height = GetScreenHeight();
}

int Config::GetScreenWidth() {
    return screen_width_;
}

bool Config::GetShowThirdParty() {
    return show_third_party_;
}

const std::string Config::GetSoundFontPath() {
    return soundfont_path_;
}

const std::string Config::GetTitleMusicMidiFilePath() {
    return title_music_midi_file_;
}

bool Config::ParseOptions(int argc, char** argv) {
    CLI::App app {};
    InitCliApp(&app);

    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        app.exit(e);
        return false;
    }

    // Derive MIDI note mapping from commandline arg list
    if (instrument_midi_remapping_notes_.size() % 2) {
        std::cerr << "Error: \"instrument_midi_remapping\" config option must "
            "have a length perfectly divisble by 2.\n";
        return false;
    }

    for (auto i=0U; i < instrument_midi_remapping_notes_.size(); i += 2) {
        if (instrument_midi_remapping_[i] == -1) {
            continue;
        }

        instrument_midi_remapping_[instrument_midi_remapping_notes_[i]] =
            instrument_midi_remapping_notes_[i+1];
    }

    // Derive MIDI insturment mapping from comandline arg list
    if (midi_output_inst_indexes_.size() % 2) {
        std::cerr << "Error: \"midi_output_instrument_mapping\" config option "
            "must have a length perfectly divisble by 2.\n";
        return false;
    }

    for (auto i = 0U; i < midi_output_inst_indexes_.size(); i += 2) {
        if (midi_output_inst_indexes_[i] == -1) {
            continue;
        }

        midi_output_inst_map_[midi_output_inst_indexes_[i]] =
            midi_output_inst_indexes_[i + 1];
    }

    return true;
}

void Config::InitCliApp(CLI::App* app) {
    app->option_defaults()->required();
    app->add_option("--audio_driver", audio_driver_, "The audio driver to use "
            "for MIDI output.");
    app->add_option("--auto_play", auto_play_, "Determines whether or not to "
            "automatically play song notes.");
    app->set_config("--config", "config.cfg", "Read a config file.")->required(
            false);
    app->add_option("--drum_midi_order", drum_midi_order_, "Determines the "
        "order of drums on the screen with the specified MIDI keys. -1 will "
        "order the drums in ascending order of their MIDI key.");
    app->add_option("--enable_title_music", enable_title_music_, "Determines "
        "whether or not to play background music on the title screen.");
    app->add_option("--frame_max_delta", frame_max_delta_, "The maximum time "
        "between two frames before the latter is dropped. -1 means no frames "
        "will ever be dropped.");
    app->add_option("--full_screen", full_screen_, "Determines whether or not "
        "to enable full-screen mode.");
    app->add_option("--icon_path", icon_path_, "The path to the icon used for "
        "the game window.");
    app->add_option("--keyboard_first_note", keyboard_first_note_, "The first "
        "MIDI note to bind to the keyboard.");
    app->add_option("--max_fps", max_frames_per_second_, "The maximum number "
        "of times the game will update in one second.");
    app->add_option("--midi_input_port", midi_input_port_, "The MIDI port to "
        "read instrument notes from.");
    app->add_option("--midi_file_channels", midi_file_channels_, "The MIDI "
        "channels to read notes from. -1 will enable all channels.");
    app->add_option("--midi_file_repeat", midi_file_repeat_, "Determines "
        "whether or not to continuously repeat the MIDI file.");
    app->add_option("--midi_file_tracks", midi_file_tracks_, "The MIDI tracks "
        "to read notes from. -1 will enable all tracks.");
    app->add_option("--midi_output_instrument_mapping"
        , midi_output_inst_indexes_,
        "Maps specified MIDI channel to SoundFont instrument. Mappings "
        "are formatted as a list of pairs of notes, where the first note "
        "in a pair is the original note, and the second note is the "
        "mapped note. This size of this list must be perfectly divisible "
        "by two. Please note instrument support is dependent on the SoundFont "
        "in use.");
    app->add_option("--practice_mode"
        , practice_mode_,
        "Enables practice mode. Pauses the game until all current notes have "
        "been played. Only supported in piano mode.");
    app->add_option("--instrument_midi_remapping"
        , instrument_midi_remapping_notes_,
        "Remaps specified instrument MIDI notes to another note. Mappings "
        "are formatted as a list of pairs of notes, where the first note "
        "in a pair is the original note, and the second note is the "
        "mapped note. This size of this list must be perfectly divisible "
        "by two.");
    app->add_option("--fall_speed_multiplier", fall_speed_multiplier_,
        "Affects the falling speed of notes on the screen. Fall speed "
        "is also dependent on the speed of the MIDI file being played.");
    app->add_option("--screen_height", screen_height_, "The screen height.");
    app->add_option("--screen_width", screen_width_, "The screen width.");
    app->add_option("--soundfont_path", soundfont_path_, "The SoundFont file "
        "to use for MIDI output.");
    app->add_flag("--show_third_party", show_third_party_, "Adding this flag "
        "prints out the copyright notices of third-party projects that are "
        "used by midistar.");
    app->add_option("--title_music_midi_file", title_music_midi_file_, "The "
        "path to a MIDI file to use for title screen background music (if "
        "enabled).");
}

}  // End namespace midistar
