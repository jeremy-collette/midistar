@ECHO off

SET buildType="Debug"
IF NOT "%~1"=="" (
	SET buildType=%1
)

ECHO Building midistar in "%buildType%" mode...

MKDIR build
CD build
cmake ..
msbuild midistar.sln /p:Configuration=%buildType%
CD ..