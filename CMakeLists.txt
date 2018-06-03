cmake_minimum_required(VERSION 2.8.9)
project (midistar)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# If build type is not set, default to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
        "Choose the type of build, options are: Debug Release")
endif(NOT CMAKE_BUILD_TYPE)

# Set compiler flags
if(CMAKE_BUILD_TYPE MATCHES Release)
    message("-- Release mode")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
else()
    message("-- Debug mode")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror -DDEBUG -g -O0")
endif()

# Find external libraries
include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/external/fluidsynth/src
    ${CMAKE_SOURCE_DIR}/external/midifile/lib/
    ${CMAKE_SOURCE_DIR}/external/rtmidi/.libs/
    ${CMAKE_SOURCE_DIR}/external/SFML/build/lib)

# Create executable
add_executable(midistar
    src/BarComponent.cpp
    src/CollisionDetectorComponent.cpp
    src/CollisionHandlerComponent.cpp
    src/Component.cpp
    src/Config.cpp
    src/DefaultGameObjectFactory.cpp
    src/DeleteOffscreenComponent.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/GameObjectFactory.cpp
    src/GraphicsComponent.cpp
    src/InstrumentComponent.cpp
    src/InstrumentInputHandlerComponent.cpp
    src/main.cpp
    src/MidiFileIn.cpp
    src/MidiIn.cpp
    src/MidiMessage.cpp
    src/MidiNoteComponent.cpp
    src/MidiOut.cpp
    src/MidiPortIn.cpp
    src/NoteInfoComponent.cpp
    src/PhysicsComponent.cpp
    src/PianoGameObjectFactory.cpp
    src/ResizeComponent.cpp
    src/SongNoteCollisionHandlerComponent.cpp
    src/SongNoteComponent.cpp
    )

# Link midistar
target_link_libraries(midistar
    midifile
    rtmidi
    sfml-graphics
    sfml-system
    sfml-window)

# Handle OSX
if (${APPLE})
    message("-- OSX detected")

    # fluidsynth is a framework on OSX
    set_target_properties(midistar PROPERTIES LINK_FLAGS "-Wl,-F${CMAKE_SOURCE_DIR}/external/fluidsynth/src")
    target_link_libraries(midistar
        "-framework FluidSynth")

    # Copy OSX run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/run_osx
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/run_osx
            ../run)

    # Copy OSX debug script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/debug_osx
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'debug'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/debug_osx
            ../debug)

    # Copy OSX config (if it does not exist)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/config.cfg)
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/data/osx.cfg
            ${CMAKE_SOURCE_DIR}/.)

        # Rename to 'config.cfg'
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/osx.cfg
            ../config.cfg)
    endif()
else() # Assuming Linux
    # fluidsynth is a normal library on Linux
    target_link_libraries(midistar
        fluidsynth)

    # Copy Linux run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/run_linux
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/run_linux
            ../run)

    # Copy Linux debug script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/debug_linux
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'debug'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/debug_linux
            ../debug)

    # Copy Linux config (if one does not already exist)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/config.cfg)
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/data/linux.cfg
            ${CMAKE_SOURCE_DIR}/.)

        # Rename to 'config.cfg'
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/linux.cfg
            ../config.cfg)
    endif()
endif()

# Copy 'make' script
add_custom_command(TARGET midistar POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/scripts/make
    ${CMAKE_SOURCE_DIR}/.)


