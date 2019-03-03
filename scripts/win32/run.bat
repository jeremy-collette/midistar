@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="scripts" (cd ..)
SET proj_dir="%cd%"

REM Find binary:
CALL scripts\win32\find_binary.bat

REM If we found the binary...:
IF %errorlevel%==0 (
    REM Run executable:
    CALL "build\Debug\midistar.exe" %*
    CD "%proj_dir%"
)