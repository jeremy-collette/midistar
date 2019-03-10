@ECHO off

REM Setup variables
SET script_dir=%~dp0

REM Find MSBuild:
ECHO.
ECHO Finding MSBuild.exe...
FOR /f "usebackq tokens=*" %%i in (`%script_dir%\vswhere -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
  SET msbuild=%%i
)

IF "%msbuild%" == "" (
    ECHO Could not find MSBuild! Please install Microsoft Developer Tools and try again.
    EXIT /b 1
)

REM Found binary!
ECHO Found MSBuild at "%msbuild%".
EXIT /b 0