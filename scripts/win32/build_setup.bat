@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (CD ..\..)

SET midistar_dir=%CD%
SET ext_dir=%CD%\external
SET lib_dir=%CD%\lib
SET lib_dir_debug=%lib_dir%\debug
SET lib_dir_release=%lib_dir%\release
SET dll_dir=%CD%\dll
SET inc_dir=%CD%\include
SET win_script_dir=%CD%\scripts\win32

ECHO Removing build folder...
RD /q /s build

ECHO.
ECHO Removing lib folder...
RD /q /s lib
MKDIR lib
MKDIR "lib\debug"
MKDIR "lib\release"

ECHO.
ECHO Resetting include folder...
RD /q /s "%inc_dir%\CLI"
RD /q /s "%inc_dir%\FluidSynth"
RD /q /s "%inc_dir%\midifile"
RD /q /s "%inc_dir%\rtmidi"
RD /q /s "%inc_dir%\SFML"
DEL "%inc_dir%\fluidsynth.h"

ECHO.
ECHO Setting up git submodules...
git submodule init
git submodule update

ECHO.
ECHO Preparing vcpkg...
CD "%ext_dir%\vcpkg" || GOTO :error
git clean -fdx
CALL bootstrap-vcpkg.bat
IF NOT %errorlevel%==0 (
	GOTO :error
)
vcpkg install glib || GOTO :error

ECHO.
ECHO Preparing CLI11...
CD "%ext_dir%\CLI11" || GOTO :error
git clean -fdx
XCOPY /E "include\CLI" "%inc_dir%\CLI\" || GOTO :error

ECHO.
ECHO Preparing fluidsynth...
CD "%ext_dir%\fluidsynth"
git clean -fdx
MKDIR build
CD build
cmake .. -DCMAKE_TOOLCHAIN_FILE="%ext_dir%\vcpkg\scripts\buildsystems\vcpkg.cmake" -Denable-pkgconfig:BOOL="0" || GOTO :error
msbuild FluidSynth.sln /p:Configuration=Debug || GOTO :error
COPY "src\Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "src\Debug\*.dll" "%lib_dir_debug%\." || GOTO :error
msbuild FluidSynth.sln /p:Configuration=Release || GOTO :error
COPY "src\Release\*.lib" "%lib_dir_release%\." || GOTO :error
COPY "src\Release\*.dll" "%lib_dir_release%\." || GOTO :error
XCOPY /E "..\include\fluidsynth" "%inc_dir%\fluidsynth\" || GOTO :error
COPY "include\fluidsynth.h" "%inc_dir%\." || GOTO :error
COPY "include\fluidsynth\version.h" "%inc_dir%\fluidsynth\." || GOTO :error

ECHO.
ECHO Preparing midifile...
CD "%ext_dir%\midifile" || GOTO :error
git clean -fdx
MKDIR build
CD build
cmake .. || GOTO :error
msbuild midifile.sln /p:Configuration=Debug || GOTO :error
COPY "Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
msbuild midifile.sln /p:Configuration=Release || GOTO :error
COPY "Release\*.lib" "%lib_dir_release%\." || GOTO :error
MKDIR "%inc_dir%\midifile" || GOTO :error
COPY "..\include\*.h" "%inc_dir%\midifile\." || GOTO :error

ECHO.
ECHO Preparing rtmidi...
CD "%ext_dir%\rtmidi" || GOTO :error
git clean -fdx
COPY "%win_script_dir%\rtmidi_debug_makefile" Makefile || GOTO :error
nmake /A rtmidi-d.lib || GOTO :error
COPY "*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "%win_script_dir%\rtmidi_release_makefile" Makefile || GOTO :error
nmake /A rtmidi.lib || GOTO :error
COPY "*.lib" "%lib_dir_release%\." || GOTO :error
MKDIR "%inc_dir%\rtmidi" || GOTO :error
COPY "*.h" "%inc_dir%\rtmidi\." || GOTO :error

ECHO.
ECHO Preparing SFML...
CD "%ext_dir%\SFML" || GOTO :error
git clean -fdx
MKDIR build
CD build
cmake .. || GOTO :error
msbuild SFML.sln /p:Configuration=Debug || GOTO :error
COPY "lib\Debug\*.lib" "%lib_dir_debug%\." || GOTO :error
COPY "lib\Debug\*.dll" "%lib_dir_debug%\." || GOTO :error
msbuild SFML.sln /p:Configuration=Release || GOTO :error
COPY "lib\Release\*.lib" "%lib_dir_release%\." || GOTO :error
COPY "lib\Release\*.dll" "%lib_dir_release%\." || GOTO :error
XCOPY /E "..\include\SFML" "%inc_dir%\SFML\" || GOTO :error

ECHO.
ECHO Finished! Refer to the README file for instructions on building midistar.
GOTO :end

:error
ECHO.
ECHO An error occured! Quitting...

:end
CD "%midistar_dir%"
