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

#include <iostream>

#include "midistar/Config.h"
#include "midistar/Game.h"
#include "midistar/Version.h"

int main(int argc, char** argv) {
    std::cout << "midistar " << MIDISTAR_VERSION << " Copyright (C) 2018 "
    << "Jeremy Collette.\nThis program comes with ABSOLUTELY NO WARRANTY. "
    << "This is free software, and you are welcome to redistribute it under "
    << "certain conditions.\n\n";

#ifdef DEBUG
    std::cout << "This is a DEBUG build.\n";
#endif

    int err;
    if ((err = midistar::Config::GetInstance().ParseOptions(argc, argv))) {
        return err;
    }

    midistar::Game g;
    if ((err = g.Init())) {
        return err;
    }

    return g.Run();
}

