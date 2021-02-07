@ECHO off
REM Change to script dir:
CD "%~dp0"

REM Change to source dir if we're in the scripts folder:
FOR %%I in (.) do SET dir=%%~nxI
IF "%dir%"=="win32" (CD ..\..)
SET proj_dir="%cd%"
SET ext_dir="%cd%\external"

REM Download, extract, and install SoundFont
CD "%ext_dir%\assets\fluid" || GOTO :error
IF EXIST "FluidR3_GM.sf2" (
    ECHO Fluid SoundFont already installed!
    GOTO :end
) ELSE (
    ECHO Downloading...
    powershell -c "Invoke-WebRequest -Uri \"https://github.com/jeremy-collette/fluidsoundfont/releases/download/v1.0/FluidR3_GM.zip\" -OutFile \"fluid.zip\""
    ECHO Extracting...
    powershell -c "Expand-Archive -Force \"fluid.zip\" \"extracted\""
    ECHO Copying...
    MOVE "extracted\FluidR3_GM.sf2" "." || GOTO :error
    RD /q /s "extracted" || GOTO :error
    DEL "fluid.zip" || GOTO :error
    ECHO Done!
    GOTO :end
)

:error
ECHO An error occured! Quitting...
EXIT /b 1

:end
EXIT /b 0