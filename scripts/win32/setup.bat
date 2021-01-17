@ECHO off

SET midistar_dir=%CD%
SET win_script_dir=%CD%\scripts\win32

REM Install SoundFont:
ECHO Installing Fluid SoundFont...
CALL "%win_script_dir%\install_soundfont.bat" Debug

REM If we could not install the SoundFont...
IF NOT %errorlevel%==0 (
    ECHO Could not install SoundFont^!
    GOTO :error
)

REM Copy "run.bat"
ECHO.
ECHO Copying run.bat...
CD "%midistar_dir%"
COPY "%win_script_dir%\run_release.bat" "run.bat"

ECHO.
ECHO Setup complete! Run "run.bat" to play.
CD "%midistar_dir%"