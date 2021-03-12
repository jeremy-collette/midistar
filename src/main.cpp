/*
 * midistar
 * Copyright (C) 2018-2021 Jeremy Collette.
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

#include <iostream>

#include "midistar/Config.h"
#include "midistar/Game.h"
#include "midistar/Version.h"

int main(int argc, char** argv) {
    std::cout << "midistar " << MIDISTAR_VERSION_FULL << " Copyright (C) 2018-"
    << "2021 Jeremy Collette.\nThis program comes with ABSOLUTELY NO WARRANTY. "
    << "This is free software, and you are welcome to redistribute it under "
    << "certain conditions. midistar uses free third-party software, that you "
    << "have obtained a copy of. Run with the '--show_third_party' argument to "
    << "see each included third-party project and their copyright notices.\n\n";

#ifdef DEBUG
    std::cout << "This is a DEBUG build.\n\n";
#endif

    if (!midistar::Config::GetInstance().ParseOptions(argc, argv)) {
        return 1;
    }

    if (midistar::Config::GetInstance().GetShowThirdParty()) {
        std::cout << "The following free third-party libraries and utilities "
            << "are used by (and distributed with) midistar:\n";
        std::cout << "\tCLI11: Copyright(c) 2017-2018 University of Cincinnati."
            << "\n\tfluidsynth: Copyright(C) 2003  Peter Hanappe and others.\n"
            << "\tmidifile: Copyright(c) 1999-2018, Craig Stuart Sapp.\n"
            << "\tRtMidi: Copyright(c) 2003-2017 Gary P.Scavone.\n"
            << "\tSFML: Copyright(C) 2007-2017 Laurent Gomila.\n"
            << "\tvcpkg: Copyright(C) Microsoft Corporation.\n";

        std::cout << "\nThe following free third-party assets are used by (and "
            << "distributed with or downloaded by) midistar:\n";
        std::cout << "\tFluid SoundFont: Copyright(C) 2000-2002, 2008, 2013 "
            << "Frank Wen."
            << "\n\tSilkscreen font: Copyright (C) Jason Kottke.\n";

        std::cout << "\nThe following third-party MIDI files are used by (and "
            << "distributed with) midistar:\n";
        std::cout << "\tNocturne MIDI: Copyright(C) 1881 G. Schirmer.\n";

        return 0;
    }

    midistar::Game g;
    if (!g.Init()) {
        return 2;
    }
    g.Run();

    return 0;
}

