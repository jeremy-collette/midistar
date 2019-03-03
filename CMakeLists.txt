cmake_minimum_required(VERSION 2.8.9)
project (midistar)

# If build type is not set, default to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

# Find external libraries
include_directories(include)

# Set compiler flags and link directories
if (WIN32)
    message("-- Windows detected")
    set(CMAKE_CXX_FLAGS "-std=c++14")
    link_directories(${CMAKE_SOURCE_DIR}/lib)
else()    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${build_type})

    if(CMAKE_BUILD_TYPE MATCHES Release)
        message("-- Release mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
    else()
        message("-- Debug mode")
        set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -Werror -DDEBUG -g -O0")
    endif()
    link_directories(${CMAKE_SOURCE_DIR}/lib/${build_type})
endif()

# Set headers
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/midistar/BarComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/CollidableComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/CollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Component.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Config.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DefaultGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/DeleteOffscreenComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Game.h
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObject.h
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObject.tpp
    ${CMAKE_SOURCE_DIR}/include/midistar/GameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentCollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InstrumentInputHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/InvertColourComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/LambdaComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiFileIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiMessage.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiNoteComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiOut.h
    ${CMAKE_SOURCE_DIR}/include/midistar/MidiPortIn.h
    ${CMAKE_SOURCE_DIR}/include/midistar/NoteInfoComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PhysicsComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/PianoGameObjectFactory.h
    ${CMAKE_SOURCE_DIR}/include/midistar/ResizeComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongNoteCollisionHandlerComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SongNoteComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/SpriteAnimatorComponent.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Utility.h
    ${CMAKE_SOURCE_DIR}/include/midistar/Version.h
    ${CMAKE_SOURCE_DIR}/include/midistar/VerticalCollisionDetectorComponent.h
)

# Set source
set(SOURCE
    ${CMAKE_SOURCE_DIR}/src/BarComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollidableComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/CollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Component.cpp
    ${CMAKE_SOURCE_DIR}/src/Config.cpp
    ${CMAKE_SOURCE_DIR}/src/DefaultGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/DeleteOffscreenComponent.cpp    
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InstrumentInputHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/InvertColourComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/LambdaComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiFileIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiIn.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiOut.cpp
    ${CMAKE_SOURCE_DIR}/src/MidiPortIn.cpp
    ${CMAKE_SOURCE_DIR}/src/NoteInfoComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PhysicsComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/PianoGameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/ResizeComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongNoteCollisionHandlerComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SongNoteComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/SpriteAnimatorComponent.cpp
    ${CMAKE_SOURCE_DIR}/src/Utility.cpp
    ${CMAKE_SOURCE_DIR}/src/VerticalCollisionDetectorComponent.cpp    
)

# Create executable
add_executable(midistar
    ${SOURCE}
    ${HEADERS}
)

# Link midistar
if (WIN32)
    # We only want Debug and Release
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    # Add libraries
    target_link_libraries(midistar
        fluidsynth
        midifile
        rtmidi
        debug sfml-graphics-d optimized sfml-graphics
        debug sfml-system-d optimized sfml-system
        debug sfml-window-d optimized sfml-window)

    # Copy libs
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/lib/$<CONFIGURATION>"
        $<TARGET_FILE_DIR:midistar>)

    # Copy Windows config (if it does not exist)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/config.cfg)
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/data/windows.cfg
            ${CMAKE_SOURCE_DIR}/.)

        # Rename to 'config.cfg'
        add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/windows.cfg
            ${CMAKE_SOURCE_DIR}/config.cfg)
    endif()

    # Set compiler flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /EHSc")

    # Set debugging directory
    set_property(TARGET midistar
        PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

    # Set startup project
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT midistar)

    # Copy Windows run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/run_windows.bat
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run.bat'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/run_windows.bat
            ../run.bat)
else()
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_link_libraries(midistar
            midifile
            rtmidi
            sfml-graphics-d
            sfml-system-d
            sfml-window-d)
    else()
        target_link_libraries(midistar
            midifile
            rtmidi
            sfml-graphics
            sfml-system
            sfml-window)
    endif()
endif()

# Handle OSX
if (${APPLE})
    message("-- OSX detected")

    # fluidsynth is a framework on OSX
    set_target_properties(midistar PROPERTIES LINK_FLAGS
        "-Wl,-F${CMAKE_SOURCE_DIR}/lib/${build_type}")

    target_link_libraries(midistar 
        "-framework FluidSynth")

    # Copy OSX run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/run_osx_${build_type}
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/run_osx_${build_type}
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
elseif(UNIX)
    message("-- UNIX detected")
    # fluidsynth is a normal library on Linux
    target_link_libraries(midistar
        fluidsynth)

    # Copy Linux run script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/run_linux_${build_type}
        ${CMAKE_SOURCE_DIR}/.)

    # Rename to 'run'
    add_custom_command(TARGET midistar POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename
            ${CMAKE_SOURCE_DIR}/run_linux_${build_type}
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

if (WIN32)
    # Copy 'make.bat' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/make.bat
        ${CMAKE_SOURCE_DIR}/.)
else()
    # Copy 'make' script
    add_custom_command(TARGET midistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/scripts/make
        ${CMAKE_SOURCE_DIR}/.)
endif()

