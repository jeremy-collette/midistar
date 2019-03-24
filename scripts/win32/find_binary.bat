@echo off
REM Change to script dir:
cd "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (cd ..\..)

REM Check for 'build' folder:
IF NOT EXIST "build\" (
    ECHO 'build' folder does not exist!
    ECHO Refer to BUILDING MIDISTAR in the README.
    EXIT /b 1
)

REM Check for binary:
IF NOT EXIST "build\%1\midistar.exe" (
    ECHO Could not find '.\build\%1\midistar.exe' binary!
    ECHO Refer to BUILDING MIDISTAR in the README.
    EXIT /b 2
)

REM Found binary!
SET midistar="build\%1\midistar.exe"
EXIT /b 0
