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

#include "midistar/Config.h"

#include <iostream>

namespace Midistar {

const sf::Keyboard::Key Config::MAPPED_KEYS[NUM_MAPPED_KEYS] {
        sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2
        , sf::Keyboard::Key::Num3, sf::Keyboard::Key::Num4
        , sf::Keyboard::Key::Num5, sf::Keyboard::Key::Num6
        , sf::Keyboard::Key::Num7, sf::Keyboard::Key::Num8
        , sf::Keyboard::Key::Num9, sf::Keyboard::Key::Num0
        , sf::Keyboard::Key::Dash, sf::Keyboard::Key::Equal
        , sf::Keyboard::Key::Q, sf::Keyboard::Key::W, sf::Keyboard::Key::E
        , sf::Keyboard::Key::R, sf::Keyboard::Key::T, sf::Keyboard::Key::Y
        , sf::Keyboard::Key::U, sf::Keyboard::Key::I, sf::Keyboard::Key::O
        , sf::Keyboard::Key::P, sf::Keyboard::Key::LBracket
        , sf::Keyboard::Key::RBracket, sf::Keyboard::Key::A
        , sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::F
        , sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::J
        , sf::Keyboard::Key::K, sf::Keyboard::Key::L
        , sf::Keyboard::Key::SemiColon, sf::Keyboard::Key::Quote
        , sf::Keyboard::Key::Z, sf::Keyboard::Key::X, sf::Keyboard::Key::C
        , sf::Keyboard::Key::V, sf::Keyboard::Key::B, sf::Keyboard::Key::N
        , sf::Keyboard::Key::M, sf::Keyboard::Key::Comma
        , sf::Keyboard::Key::Period, sf::Keyboard::Key::Slash
    };

Config* Config::instance_ = nullptr;

Config& Config::GetInstance() {
    if (!Config::instance_) {
        Config::instance_ = new Config{};
    }
    return *Config::instance_;
}

Config::Config()
        : audio_driver_{""}
        , auto_play_{false}
        , keyboard_first_note_{-1}
        , midi_file_name_{""}
        , midi_file_repeat_{false}
        , midi_highest_note_{-1}
        , midi_lowest_note_{-1}
        , player_midi_channel_{-1}
        , player_midi_track_{-1}
        , screen_height_{-1}
        , screen_width_{-1}
        , soundfont_path_{""} {
}

const std::string Config::GetAudioDriver() {
    return audio_driver_;
}

bool Config::GetAutomaticallyPlay() {
    return auto_play_;
}

int Config::GetFramesPerSecond() {
    return FRAMES_PER_SECOND;
}

int Config::GetMaximumMidiNote() {
    return midi_highest_note_;
}

const std::string Config::GetMidiFileName() {
    return midi_file_name_;
}

bool Config::GetMidiFileRepeat() {
    return midi_file_repeat_;
}

int Config::GetMidiOutVelocity() {
    return MIDI_OUT_VELOCITY;
}

int Config::GetMinimumMidiNote() {
    return midi_lowest_note_;
}

int Config::GetNumMidiNotes() {
    // We have to add 1 here because 0 is actually a MIDI note (ergo, the range
    // is inclusive).
    return GetMaximumMidiNote() - GetMinimumMidiNote() + 1;
}

int Config::GetPlayerMidiChannel() {
    return player_midi_channel_;
}

int Config::GetPlayerMidiTrack() {
    return player_midi_track_;
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

const std::string Config::GetSoundFontPath() {
    return soundfont_path_;
}

sf::Keyboard::Key Config::MidiNoteToKeyboardKey(
        int midi_note
        , bool control
        , bool shift) {
    // If the user is pressing CONTROL, we shift the MIDI note down by the
    // number of mapped keys. If the user is pressing SHIFT, we shift the MIDI
    // key up.
    //
    // This might look counter-intuitive, but we actually shift the MIDI note
    // down by changing the which key activates the relevant MIDI instrument.
    // As such, LOWERING the keyboard key index will play a higher MIDI note
    // on the same keyboard key, and INCREASING the keyboard key index will
    // play a lower MIDI note on the same keyboard key.
    int index = midi_note - keyboard_first_note_ + control * NUM_MAPPED_KEYS
        - shift * NUM_MAPPED_KEYS;
    return (index < 0 || index > NUM_MAPPED_KEYS-1) ?
        sf::Keyboard::Key::Unknown : MAPPED_KEYS[index];
}

int Config::ParseOptions(int argc, char** argv) {
    CLI::App app {};
    InitCliApp(&app);

    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        app.exit(e);
        return 1;
    }
    return 0;
}

void Config::InitCliApp(CLI::App* app) {
    app->option_defaults()->required();
    app->add_option("--audio_driver", audio_driver_, "The audio driver to use "
            "for MIDI output.");
    app->add_option("--auto_play", auto_play_, "Determines whether or not to "
            "automatically play song notes.");
    app->set_config("--config", "config.cfg", "Read a config file.")->required(
            false);
    app->add_option("--keyboard_first_note", keyboard_first_note_, "The first "
            "MIDI note to bind to the keyboard.");
    app->add_option("--midi_file", midi_file_name_, "The MIDI file to play.");
    app->add_option("--midi_file_repeat", midi_file_repeat_, "Determines "
            "whether or not to continuously repeat the MIDI file.");
    app->add_option("--midi_highest_note", midi_highest_note_, "The highest "
            "MIDI note to display and play.");
    app->add_option("--midi_lowest_note", midi_lowest_note_, "The lowest MIDI "
            "note to display and play.");
    app->add_option("--midi_track", player_midi_track_, "The MIDI track to "
            "read notes from.");
    app->add_option("--player_channel", player_midi_channel_, "The MIDI "
            "channel for instrument MIDI events.");
    app->add_option("--screen_height", screen_height_, "The screen height.");
    app->add_option("--screen_width", screen_width_, "The screen width.");
    app->add_option("--soundfont_path", soundfont_path_, "The SoundFont file "
            "to use for MIDI output.");
}

}  // End namespace Midistar
