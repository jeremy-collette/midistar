@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (CD ..\..)
SET proj_dir="%cd%"

REM Check for Visual Studio
ECHO Finding Visual Studio...
WHERE devenv.exe
if %errorLevel% == 1 (
    ECHO Could not find Visual Studio^! Please install Visual Studio 2017, open "Developer Command Prompt For VS 2017", and run this script there.
    GOTO :fin
)
ECHO.

REM Check for 'build' folder:
IF NOT EXIST "build\" (
    ECHO 'build' folder does not exist!
    ECHO Refer to BUILDING MIDISTAR in the README.
	GOTO :fin
)

REM Check for project:
IF NOT EXIST "build\midistar.sln" (
    ECHO Could not find '.\build\midistar.sln' solution file!
    ECHO Refer to BUILDING MIDISTAR in the README.
    GOTO :fin
)

REM Open solution in Visual Studio
ECHO Opening "build\midistar.sln" in Visual Studio...
CALL devenv "build\midistar.sln"

:fin
CD %proj_dir%
