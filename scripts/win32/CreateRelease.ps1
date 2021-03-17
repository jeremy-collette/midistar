$ITEMS_TO_COPY = @(
    ".git\modules\",
    "assets\",
    "build\Release",
    "external\",
    "images\",
    "include\",
    "lib\release",
    "scripts\win32\config.cfg",
    "scripts\win32\find_binary.bat",
    "scripts\win32\install_soundfont.bat",
    "scripts\win32\run_release.bat",
    "scripts\win32\setup.bat",
    "songs\drums\NOTE",
    "songs\piano\NOTE",
    "src\",
    "GPLv3",
    "LICENSE",
    "README.md"
)

$EXTERNAL_REPOS = @(
    "CLI11",
    "fluidsynth",
    "midifile",
    "rtmidi",
    "SFML",
    "vcpkg"
)

$ITEMS_TO_DELETE = @(
    ".git\",
    "doc\doxygen.config",
    "external\assets\fluid\FluidR3_GM.sf2"
)

function Print(
    [string]$Text,
    [string]$ForegroundColor = "DarkGreen")
{
    Write-Host -ForegroundColor $ForegroundColor $Text
}

function GetScriptDirectory
{
    $scriptDir = Split-Path $script:MyInvocation.MyCommand.Path
    Write-Verbose "Script dir: $scriptDir" -Verbose
    return $scriptDir
}

function GetMidistarDirectory
{
    $scriptDir = GetScriptDirectory
    $midistarDir = (Get-Item $scriptDir).Parent.Parent.Fullname
    Write-Verbose "midistar dir: $midistarDir" -Verbose
    return $midistarDir
}

function CreateReleaseFolder(
    [Parameter(Mandatory=$true)][string]$MidistarDir,
    [Parameter(Mandatory=$true)][string]$Version)
{
    Print "Creating release folder..."
    $releaseDir = (Join-Path $MidistarDir (Join-Path "package" "midistar-$($Version)_x86_64-win32"))
    if (Test-Path $releaseDir)
    {
        throw "Release directory $releaseDir already exists!"
    }
    Write-Verbose "Release folder: $releaseDir" -Verbose

    # TODO: automatically create required folders
    Write-Verbose "Creating scripts folder inside release folder..." -Verbose
    $scriptsDir = New-Item -Type "Directory" -Path (Join-Path $releaseDir (Join-Path "scripts" "win32")) -Verbose

    Write-Verbose "Creating songs folder inside release folder..." -Verbose
    $drumsDir = New-Item -Type "Directory" -Path (Join-Path $releaseDir (Join-Path "songs" "drums")) -Verbose
    $pianoDir = New-Item -Type "Directory" -Path (Join-Path $releaseDir (Join-Path "songs" "piano")) -Verbose
    return $releaseDir
}

function CopyToReleaseFolder(
    [Parameter(Mandatory=$true)][string]$MidistarDir,
    [Parameter(Mandatory=$true)][string]$ReleaseDir)
{
    Print "Copying items to release folder $ReleaseDir..."
    foreach ($item in $ITEMS_TO_COPY)
    {
        Write-Verbose "Copying $item..." -Verbose
        $itemInputPath = Join-Path $MidistarDir $item
        $itemOutputPath = Join-Path $ReleaseDir $item
        Copy-Item -Path $itemInputPath -Destination $itemOutputPath -Recurse -Container
    }
}

function CleanUpExternalGitRepos(
    [Parameter(Mandatory=$true)][string]$ReleaseDir)
{
    $originalLocation = Get-Location
    Write-Verbose "Cleaning up git submodules..." -Verbose
    $externalDir = Join-Path $ReleaseDir "external"
    foreach ($repo in $EXTERNAL_REPOS)
    {
        Write-Verbose "Cleaning up $repo..." -Verbose
        $repoDir = Join-Path $externalDir $repo
        Write-Verbose "Repo dir: $repoDir"
        Set-Location -Path $repoDir
        git clean -fdx
        if (Test-Path ".git")
        {
            Remove-Item -Path ".git" -Recurse -Force -Verbose
        }
        else
        {
            Write-Verbose "No .git folder found in $repo." -Verbose
        }

        if (Test-Path ".gitignore")
        {
            Remove-Item ".gitignore"-Verbose  -ErrorAction "Ignore"
        }
        else
        {
            Write-Verbose "No .gitignore file found in $repo." -Verbose
        }
    }
    Set-Location $originalLocation
}

function CleanUpReleaseFolder(
    [Parameter(Mandatory=$true)][string]$MidistarDir,
    [Parameter(Mandatory=$true)][string]$ReleaseDir)
{
    CleanUpExternalGitRepos -ReleaseDir $ReleaseDir

    Print "Cleaning up $ReleaseDir..."
    foreach ($item in $ITEMS_TO_DELETE)
    {
        Write-Verbose "Deleting $item..." -Verbose
        $itemPath = Join-Path $ReleaseDir $item
        Remove-Item -Path $itemPath -Recurse -Force
    }
}

function FinalizeReleaseFolder(
    [Parameter(Mandatory=$true)][string]$ReleaseDir)
{
    $originalLocation = Get-Location
    Print "Finalizing release directoy..."
    Set-Location $ReleaseDir
    Move-Item -Path "scripts\win32\config.cfg" -Destination .
    Move-Item -Path "scripts\win32\setup.bat" -Destination .
    Set-Location $originalLocation
}

function CreateNewRelease(
    [Parameter(Mandatory=$true)][string]$Version)
{
    $midistarDir = GetMidistarDirectory
    $releaseDir = CreateReleaseFolder -MidistarDir $midistarDir -Version $Version
    CopyToReleaseFolder -MidistarDir $midistarDir -ReleaseDir $releaseDir
    CleanUpReleaseFolder -MidistarDir $midistarDir -ReleaseDir $releaseDir
    FinalizeReleaseFolder -ReleaseDir $releaseDir
    Print "New release created at $releaseDir"
    Print -ForegroundColor Green "Congratulations on releasing midistar v$Version!"
}

$ErrorActionPreference = "Stop"

Print "This script will create a new midistar release. Ensure the Release binaries are
up-to-date and the source folder has been prepared for release. You may want to
build documentation or update the source version.`n"

Read-Host -Prompt "Press enter to continue or CTRL+C to quit"

if ($args[0] -eq $null)
{
    $version = Read-Host -Prompt "Enter version (#.#.#)"
}
else
{
    $version = $args[0]
}

Print "Preparing release for midistar v$version..."
CreateNewRelease -Version $version
