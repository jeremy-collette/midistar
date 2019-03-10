@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (cd ..\..)
SET proj_dir="%cd%"

REM Tell user which build mode we're running:
ECHO Starting midistar Release build...

REM Find binary:
CALL scripts\win32\find_binary.bat Release

REM If we found the binary...:
IF %errorlevel%==0 (
    REM Run executable:
    CALL "%midistar%" %*
    CD "%proj_dir%"
)