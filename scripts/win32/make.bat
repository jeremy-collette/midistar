@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (cd ..\..)
SET proj_dir="%cd%"

REM Get build type:
SET build_type=%1
IF "%~1"=="" (
	ECHO WARNING: Build type not specified. Setting to debug mode...
	SET build_type=Debug
)

REM Build project:
ECHO Building midistar in %build_type% mode...
MKDIR build
CD build
cmake ..
msbuild midistar.sln /p:Configuration=%build_type%
CD %proj_dir%