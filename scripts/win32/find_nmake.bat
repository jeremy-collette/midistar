@ECHO off

REM Setup variables
SET script_dir=%~dp0

REM Detect 32bit / 64bit operating system
REG query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT
if %OS%==32BIT (
	SET platform=x86
) ELSE (
	SET platform=x64
)

REM Find nmake:
ECHO.
ECHO Finding nmake.exe...
FOR /f "usebackq tokens=*" %%i in (`%script_dir%\vswhere -latest -requires Microsoft.Component.MSBuild -find **\Host%platform%\%platform%\nmake.exe`) do (
  SET nmake=%%i
)

IF "%nmake%" == "" (
    ECHO Could not find nmake! Please install Microsoft Developer Tools and try again.
    EXIT /b 1
)

REM Found binary!
ECHO Found nmake at "%nmake%".
EXIT /b 0