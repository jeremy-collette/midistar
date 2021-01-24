# midistar
midistar Copyright (C) 2018-2021 Jeremy Collette.

## 1. About midistar
midistar is a free music game that challenges users to play a MIDI file with
their computer keyboard or a MIDI instrument, such as an electronic piano or
drums.

![Title Screen](images/midistar_title_screen.png | width=250)
![Piano Game Mode](images/midistar_piano_song.png | width=250)

midistar uses third-party libraries, utilities, and assets that are not
considered to be part of the midistar project, but are distributed with midistar
for ease-of-access and completeness. Each sub-folder in the 'external' folder
contains the source code of a different third-party project that is used by
midistar. The 'external/assets' folder contains third-party assets that are used
by midistar. See the LICENSE file for more information.

The following third-party libraries and utilities are used by (and distributed
with) midistar:
 * CLI11: Copyright (c) 2017-2018 University of Cincinnati.
 * fluidsynth: Copyright (C) 2003 Peter Hanappe and others.
 * midifile: Copyright (c) 1999-2018, Craig Stuart Sapp.
 * RtMidi: Copyright (c) 2003-2017 Gary P. Scavone.
 * SFML: Copyright (C) 2007-2017 Laurent Gomila.
 * vcpkg: Copyright (C) Microsoft Corporation.

The following third-party assets are used by (and distributed with or downloaded
by) midistar:
 * Fluid SoundFont: Copyright (C) 2000-2002, 2008, 2013 Frank Wen.
 * Nocturne MIDI: Copyright (C) 1881 G. Schirmer.
 * Silkscreen font: Copyright (C) Jason Kottke.

Thanks to the developers, creators, and supporters of these projects! Note that
you can see these copyright notices in midistar by running the project with the
`--show_third_party` command line flag.

midistar is written in C++ using code (and shared libraries) that are
compatible with Linux, OSX, and Windows. However, at the current time, only 64-
bit Debian Linux, Ubuntu Linux, Catalina OSX, and Windows 10 are supported. That
being said, building and running on unsupported platforms / architectures is
possible.

The instructions in this README are written for the supported platforms listed
above. Also note that releases may not contain binaries for all (if any)
supported platforms.


## 2. Installation
### 2.1 Installing midistar
If you're using Windows, OSX, Debian, or Ubuntu, installing midistar on your
system is quite straightforward. Firstly, download the pre-built binaries for
your system from one of the midistar releases. For Windows, pre-built binaries
are distributed in a compressed .zip archive. For OSX, they are distributed in
a .tar.gz archive. For Debian, and Ubuntu, they are distributed in a .deb
package.

On Windows or OSX, extract the pre-built binaries from the compressed archive
after downloading. If you're using Debian or Ubuntu, install the .deb package on
your system. You're done! See the RUNNING MIDISTAR section of this README to
start playing.

If you're using another distribution of Linux or an unsupported platform /
architecture, or you don't want to use a pre-built binary, you can still build
midistar from source. See the BUILDING section of this README.

### 2.2 Installing additional SoundFont files
When you run the midistar initial setup, the Fluid SoundFont (Release 3) will
automatically be installed on your machine. If you want to install additional
SoundFont files, simply place them on your machine and update the
`soundfont_path` setting in the midistar `config.cfg`. See INITIAL SETUP and
CONFIGURING MIDISTAR for more information.


## 3. Running midistar
### 3.1 Configuring midistar
midistar has configuration options that can be configured for varying levels of
customisation. Run midistar with the `--help` option to see a list of
configuration options. These can be set in the 'config.cfg' file, which can be
found in the midistar folder, or provided as command line arguments.

If you have installed a midistar release using a .deb package, you will find
'config.cfg' at `/usr/local/bin/midistar_<pkg-version>/config.cfg`. Where
'pkg-version' is the version of the .deb package that you installed. You can
find the version in the file name of the package.

If you are building midistar from scratch, please note that the 'config.cfg'
file will not be created until midistar has been built for the first time. Also
note that it is recommended to use absolute paths instead of relative paths in
configuration settings.

### 3.2 Initial setup
midistar requires a brief initial setup which is mostly automated. If you are
running a copy of midistar that you built from scratch, this is already
completed during build setup. If you are running a copy of midistar that you
installed using a ".deb" package, you can skip this section.

Otherwise, if you are running a pre-built binary that you downloaded as a
release, simply navigate to the extracted release folder and run the setup
command. To do this, open a terminal and change directories to the extracted
release folder. On Windows run the `setup.bat` command and on Linux/OSX run the
`./setup` command.

### 3.3 Starting from terminal
Once you have completed the initial setup as described above, you're ready to
play. If you have downloaded a midistar release with pre-built binaries for your
platform, you can start midistar with the `./run` command from a terminal that
is in the midistar directory.

If you installed a midistar release using a .deb package, you can start midistar
by running the `midistar` command in any terminal. This is a wrapper that calls
the 'run' script mentioned above. It will also handle initial setup the first
time it is called.

If there is not a midistar release with pre-built binaries for your platform,
or you have cloned the midistar repository, you will have to build midistar
from scratch before running. See the BUILDING section in this README.

### 3.4 Playing midistar
When you play midistar, you will select a MIDI file to play from the main menu.
The MIDI notes from this file will be rendered on the game screen in real-time,
falling from top to bottom. While falling, each MIDI note will pass through the
instrument bar near the bottom of the screen. When MIDI notes are passing
through the instrument bar, they can be played by activating the corresponding
note. The aim of midistar is to play each MIDI note as it passes through the
instrument bar, as precisely as possible.

The instrument bar can be activated in two ways. The first way is by using the
computer keyboard. The A-Z, 0-9, and some punctuation keys (dash, equals,
square brackets, semi-colon, quote, comma, period, and forward slash) are all
bound to activate different notes on the instrument bar. The note that is
activated can be shifted up by pressing the SHIFT key, or shifted down by
pressing the CONTROL key. This allows all possible MIDI notes to be played with
the keyboard.

The instrument bar can also be activated by using a MIDI instrument, which is
the recommended way to play midistar. Connect your MIDI instrument to the
computer running midistar using a MIDI to USB connection cable. You may have to
virtually 'attach' the MIDI input port to the midistar 'RtMidi' MIDI port,
depending on which platform and/or MIDI software you are using. Once you have
connected and attached a MIDI instrument, the midistar instrument bar can be
activated by playing the correlating note on the MIDI instrument.


## 4. Building
### 4.1 cmake
'cmake' is required to build midistar and some of its third-party libraries. If
you are on Debian or Ubuntu, you can install cmake by using the command:
    `sudo apt-get install cmake`

On OSX, you can install cmake by first installing Homebrew and then using the
command:
    `brew install cmake`

On Windows, you will have to download CMake online and follow the installation
instructions.

### 4.2 Installing build dependencies
If you are developing midistar on OSX and Windows, third-party libraries should
come packaged with their dependencies and work out of the box. This means that
no extra software should be required (except build tools), so you can skip this
step.

However, on Linux, additional software must be installed to meet build
dependencies. If you're running Debian or Ubuntu, you should be able to install
the majority of build dependencies with the following command:
    `sudo apt-get install libasound2-dev libbsd-dev libc6-dev libflac-dev libfreetype6-dev libgl1-mesa-dev libglib2.0-dev libogg-dev libopenal-dev libpcre3-dev libpng-dev libsndfile1-dev libudev-dev libvorbis-dev libx11-dev libx11-xcb-dev libxau-dev libxcb-image0-dev libxcb-randr0-dev libxcb1-dev libxdmcp-dev libxext-dev libxrandr-dev libxrender-dev zlib1g-dev build-essential pkg-config cmake libtool automake autoconf`

Additionally, on Debian run the following command:
    `sudo apt-get install libjpeg62-turbo-dev`

On Ubuntu, run the following command:
    `sudo apt-get install libjpeg62-dev`

If a package cannot be found, check that you have added the 'universe'
repository in your apt sources and have run the 'apt-get update' command. If you
are trying to build midistar on an unsupported Linux distribution, you can try
and find equivalent packages using your system package manager.

### 4.3 Building midistar
If you're building midistar for the first time, some setup is required. If you
are on Linux or OSX, you can try running the `./build_setup_unix` command from a
terminal in the midistar directory. If you are on Windows, run the
`build_setup_win32.bat` command from the "x64 Native Tools Command Prompt for VS
2017" Developer Command Prompt. You will have to install Visual Studio 2017 to
access this Developer Command Prompt on Windows.

Please note that this command does not install prerequisites for the third-
party libraries. As such, they may fail to build. When a build failure occurs,
read the console output and install any missing prerequisites before trying
again.

If build setup succeeds, midistar has already been built! You can re-build
midistar at any time by using the `./make` command on Linux/OSX and the
`make.bat` command on Windows. You can specify whether to build in Debug or
Release mode by specifying the build mode to the make command, e.g.
`./make release` on Linux/OSX, or `make.bat Release` on Windows. See the RUNNING
MIDISTAR section for information on configuring, running, and debugging
midistar.

If build setup fails, try and troubleshoot the issue yourself. There should be
an error message that can be used to diagnose the failure.

### 4.4 Debugging midistar
If you would like to debug midistar on Linux or OSX, you can run the `./debug`
command to start midistar in gdb. You may have to install gdb before running the
`./debug` command.

If you would like to debug midistar on Windows, please see the OPENING MIDISTAR
IN VISUAL STUDIO section of this README.

Note that you should only debug a midistar binary that has been built in debug
mode. Binaries that are provided with releases have been built in release mode,
and are not suitable for debugging. As such, if you would like to debug
midistar, you will have to build a debug build from scratch. For information on
building midistar in debug mode, see the BUILDING section in this README.

### 4.5 Opening midistar in Visual Studio
If you are on Windows, you can open midistar in Visual Studio by running the
`startvs.bat` command from the midistar project folder. Please note that you
must have already successfully build midistar following the instructions in
BUILDING MIDISTAR before you can use this command.

### 4.6 Building Documentation
If you would like to build midistar documentation, you can do so using doxygen.
Before building documentation, you must install doxygen and Graphviz. If you're
on Debian or Ubuntu, you can install doxygen and Graphviz using the following
command:
    `sudo apt-get install doxygen graphviz`

If you're own OSX, you can use Homebrew:
    `brew install doxygen graphviz`

On Windows, you will have to download and doxygen and Graphviz online.

Once installed, navigate to the 'doc' folder, and type the command:
    `doxygen doxygen.config`

This will build the midistar documentation in the 'doc' folder.


## 5. License
Refer to the 'LICENSE' file for more information.
