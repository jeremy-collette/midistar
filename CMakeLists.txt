cmake_minimum_required(VERSION 2.8.9)
project (midistar)

# Find external libraries
include_directories(include)

# Set source
set(SOURCE
    ${CMAKE_SOURCE_DIR}/src/BarComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollidableComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Component.cpp
    ${CMAKE_SOURCE_DIR}/src/Config.cpp
    ${CMAKE_SOURCE_DIR}/src/DefaultGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DelayedComponentComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/DeleteOffscreenComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DrumSongNoteCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/FadeOutEffectComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentAutoPlayComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentInputHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertColourComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/LambdaComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiFileIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiInstrumentIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiOut.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiPortIn.cpp
    ${CMAKE_SOURCE_DIR}/src/NoteInfoComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PhysicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoSongNoteCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ResizeComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/ShrinkGrowComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SpriteAnimatorComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Utility.cpp
    ${CMAKE_SOURCE_DIR}/src/VerticalCollisionDetectorComponent.cpp    
)

# If build type is not set, default to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

# Check for valid build type
if(NOT ${build_type} STREQUAL "debug" AND NOT ${build_type} STREQUAL "release")
    message("Warning: invalid build type \"${CMAKE_BUILD_TYPE}\" supplied. Setting to \"Debug\"...")
    set(CMAKE_BUILD_TYPE "Debug")
    set(build_type "debug")
endif()

# Specify platform
if (WIN32)
    message("-- Windows detected")
    message("-- Release/Debug modes")
    set(platform win32)

    # Specify link directory
    link_directories(${CMAKE_SOURCE_DIR}/lib)
else()
    if (${APPLE})
        message("-- OSX detected")
        set(platform osx)
    else()
        message("-- Linux detected")
        set(platform debian)
    endif()

    # Specify link directory by build type
    link_directories(${CMAKE_SOURCE_DIR}/lib/${build_type})

    # Change binary output dir
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${build_type})
endif()

# Create executable
add_executable(midistar
    ${SOURCE}
)

# Create config (if it does not exist)
if (NOT EXISTS ${CMAKE_SOURCE_DIR}/config.cfg)
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/config.cfg
        ${CMAKE_SOURCE_DIR}/.)
endif()

# OS specific stuff
if (WIN32) # Windows
    # We only want Debug and Release
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    # Add libraries
    target_link_libraries(midistar
        debug debug/fluidsynth optimized release/fluidsynth
        debug debug/midifile optimized release/midifile
        debug debug/rtmidi-d optimized release/rtmidi
        debug debug/sfml-graphics-d optimized release/sfml-graphics
        debug debug/sfml-system-d optimized release/sfml-system
        debug debug/sfml-window-d optimized release/sfml-window)

    # Copy Release and Debug libs
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:midistar>)

    # Set compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

    # Set debugging directory
    set_property(TARGET midistar
        PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    # Set startup project
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT midistar)

    # Copy Windows run script for Debug / Release
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/win32/run_$<CONFIGURATION>.bat
        ${CMAKE_SOURCE_DIR}/.)    

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_SOURCE_DIR}/run_$<CONFIGURATION>.bat
        ../run.bat)

    # Copy 'make.bat' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/win32/make.bat
        ${CMAKE_SOURCE_DIR}/.)    

else() # Linux/OSX
    # Do common stuff for Linux/OSX (Unix)
    # Set compiler flags
    if(${build_type} STREQUAL "release")
        message("-- Release mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
    else()
        message("-- Debug mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Werror -DDEBUG -g -O0")
    endif()

    # Link libraries depending on build type
    if(${build_type} STREQUAL "release")
        target_link_libraries(midistar
            midifile
            rtmidi
            sfml-graphics
            sfml-system
            sfml-window)
    else()
        target_link_libraries(midistar
            midifile
            rtmidi
            sfml-graphics-d
            sfml-system-d
            sfml-window-d)
    endif()

    # Copy Unix 'make' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/unix/make
        ${CMAKE_SOURCE_DIR}/.)

    # Copy Linux/OSX run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/run_${build_type}
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
        ${CMAKE_SOURCE_DIR}/run_${build_type}
        ../run)

    # Copy Linux/OSX debug script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/${platform}/debug
        ${CMAKE_SOURCE_DIR}/.)

    # OSX specific stuff
    if(${APPLE})
        # fluidsynth is a framework on OSX
        set_target_properties(midistar PROPERTIES LINK_FLAGS
            "-Wl,-F${CMAKE_SOURCE_DIR}/lib/${build_type}")
        target_link_libraries(midistar 
            "-framework FluidSynth")

    # Linux specific stuff
    elseif(UNIX) 
        # fluidsynth is a normal library on Linux
        target_link_libraries(midistar
            fluidsynth)
    endif()
endif()
