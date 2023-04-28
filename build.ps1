################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

$CMakeRequiredVersion = "3.25.0"
$CMakeBuildDirectory = ".\_build"
$CMakeGenerator = "Ninja"
$CMakeBuildConfig = "Debug"
$CMakeCleanRebuild = $False

if ($args.Count -gt 0) {
  if ($args[0] -eq "--help") {
    Write-Host "Usage: build.ps1 [ --clean | --rebuild | --release ]"
    return
  }
  elseif ($args[0] -eq "--clean") {
    if ((Test-Path -PathType Container $CMakeBuildDirectory) -ne $False) {
      Remove-Item $CMakeBuildDirectory -Force -Recurse
    }
    return
  }
  elseif ($args[0] -eq "--rebuild") {
    $CMakeCleanRebuild = $True
  }
  elseif ($args[0] -eq "--release") {
    $CMakeBuildConfig = "Release"
  }
}

function Select-CMakeVersion {
  param (
    $VersionString
  )
  $VersionStringLines = $VersionString.Split("`n`r")
  $FirstLine = $VersionStringLines[0]
  $VersionTokens = $FirstLine.Split(" ")
  $Version = $VersionTokens[2]
  return $Version.Trim()
}

function Find-CMakeVersion ($CMakePath) {
  $VersionString = & $CMakePath --version | Out-String
  $Version = Select-CMakeVersion -VersionString $VersionString
  return $Version.Trim()
}

function Compare-Versions($CurrentVersion, $RequiredVersion) {
  $CurrentVersionTokens = $CurrentVersion.Split(".")
  $RequiredVersionTokens = $RequiredVersion.Split(".")
  if ($CurrentVersionTokens.Count -ge $RequiredVersionTokens.Count) {
    $TokenCount = $CurrentVersionTokens.count
  }
  else {
    $TokenCount = $RequiredVersionTokens.count
  }
  For ($i = 0; $i -lt $TokenCount; $i++) {
    $CompareResult = $CurrentVersionTokens[$i].CompareTo($RequiredVersionTokens[$i])
    if ($CompareResult -eq -1) {
      return -1
    }
    elseif ($CompareResult -eq 1) {
      return 1
    }
  }
  return 0
}

###############################################################################
# Check whether a useable version of cmake is available.
if ($CMakeFound -eq $False) {
  $CMakeInstallPath = "cmake.exe"
  if (Get-Command $CMakeInstallPath -ErrorAction SilentlyContinue) {
    $CurrentCMakeVersion = Find-CMakeVersion $CMakeInstallPath
    $CompareResult = Compare-Versions $CurrentCMakeVersion $CMakeRequiredVersion
    if ($CompareResult -gt -1) {
      $CMakeFound = $True
    }
  }
}
if ($CMakeFound -eq $False) {
  Write-Host -ForegroundColor Red Failed to find the required CMake version. Only 3.20.5 and higher is supported.
  return
}

###############################################################################
# Check whether a useable version of Microsoft C++ is available.
if ($Null -eq (Get-Command "cl.exe")) {
  $visualStudioPath = $Null
  if (Test-Path -Path (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\Installer\\vswhere.exe') -PathType Leaf) {
    $visualStudioPath = & (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\Installer\\vswhere.exe') -prerelease -latest -property installationPath
  }
  if ($Null -eq $visualStudioPath) {
    if (Test-Path -Path (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2022\\BuildTools') -PathType Container) {
      $visualStudioPath = (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2022\\BuildTools')
    }
    else {
      if (Test-Path -Path (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2019\\BuildTools') -PathType Container) {
        $visualStudioPath = (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2019\\BuildTools')
      }
      else {
        if (Test-Path -Path (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2017\\BuildTools') -PathType Container) {
          $visualStudioPath = (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\2017\\BuildTools')
        }
      }
    }
  }
  if ($Null -ne $visualStudioPath) {
    Import-Module (Join-Path $visualStudioPath 'Common7\\Tools\\Microsoft.VisualStudio.DevShell.dll')
    Enter-VsDevShell -VsInstallPath $visualStudioPath -SkipAutomaticLocation -DevCmdArguments "-arch=x64 -host_arch=x64" | Out-Null
  }
  else {
    Write-Host -ForegroundColor Red "Failed to find the required Visual Studio version. Only '2022', '2019' and '2017' are supported."
    return
  }
}

###############################################################################
# Configure project.
Write-Host "Configuring projects using $CMakeGenerator..."
cmake -B"$CMakeBuildDirectory" -G"$CMakeGenerator" -DCMAKE_BUILD_TYPE="$CMakeBuildConfig" -Wno-dev
if ($LastExitCode -ne 0) {
  Write-Host "Building projects using $CMakeGenerator..."
  return
}

###############################################################################
# Build project.
if ($True -eq $CMakeCleanRebuild) {
  cmake --build "$CMakeBuildDirectory" --clean-first --target reaper_ultraschall --config "$CMakeBuildConfig" -j
}
else {
  cmake --build "$CMakeBuildDirectory" --target reaper_ultraschall --config "$CMakeBuildConfig" -j
}
if ($LastExitCode -ne 0) {
  Write-Host -ForegroundColor Red "Failed to build project."
}
