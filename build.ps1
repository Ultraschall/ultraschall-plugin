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

. "./scripts/BuildTools.ps1"

$ToolsDirectory = "./tools"
$BuildDirectory = "./build"
$BuildConfig = "Debug"
$CMakeExtraArgs = ""

If ($args.Count -gt 0) {
  If ($args[0] -eq "--help") {
    Write-Host "Usage: build.ps1 [ --bootstrap | --rebuild | --clean | --clean-all ]"
    Return
  }
  ElseIf ($args[0] -eq "--bootstrap") {
    Remove-Directory $BuildDirectory
    Remove-Directory $ToolsDirectory
    . "bootstrap.ps1"
    Return
  }
  ElseIf ($args[0] -eq "--cleanall") {
    Remove-Directory $BuildDirectory
    Remove-Directory $ToolsDirectory
    Return
  }
  ElseIf ($args[0] -eq "--clean") {
    Remove-Directory $BuildDirectory
    Return
  }
  ElseIf ($args[0] -eq "--rebuild") {
    $CMakeExtraArgs = "--clean-first"
  }
  ElseIf ($args[0] -eq "--release") {
    $BuildConfig = "Release"
  }
}

$LocalCMakeDirectory = $ToolsDirectory + "/cmake"
$RequiredCMakeVersion = "3.20.5"
$CMakeFound = $False

Write-Host Looking for CMake $RequiredCMakeVersion"."
Write-Host Checking system install...
If ($CMakeFound -eq $False) {
  $CMakeInstallPath = "cmake.exe"
  If (Get-Command $CMakeInstallPath -ErrorAction SilentlyContinue) {
    $CurrentCMakeVersion = Find-CMakeVersion $CMakeInstallPath
    Write-Host Found CMake version $CurrentCMakeVersion"."
    $CompareResult = Compare-Versions $CurrentCMakeVersion $RequiredCMakeVersion
    If ($CompareResult -ne 2) {
      $CMakeFound = $True
    }
  }
}

If ($CMakeFound -eq $False) {
  Write-Host CMake $RequiredCMakeVersion does not seem to be installed on this system.
  Write-Host Checking local install...
  $CMakeInstallPath = $LocalCMakeDirectory + "/bin/cmake"
  If (Get-Command $CMakeInstallPath -ErrorAction SilentlyContinue) {
    $CurrentCMakeVersion = Find-CMakeVersion $CMakeInstallPath
    Write-Host Found CMake version $CurrentCMakeVersion"."
    $CompareResult = Compare-Versions $CurrentCMakeVersion $RequiredCMakeVersion
    If ($CompareResult -ne 2) {
      $CMakeFound = $True
    }
  }
}

If ($CMakeFound -eq $False) {
  Write-Host -ForegroundColor Red Failed to find the required CMake version. Only 3.20.5 and higher is supported.
  Return
}

$VisualStudioFound = $False
$CMakeGenerator = "<unknown>"

Write-Host "Looking for Visual Studio 2022 or 2019..."
If ($VisualStudioFound -eq $False) {
  $VisualStudioVersion = Find-VisualStudioVersion
  Write-Host Found Visual Studio $VisualStudioVersion"."
  If ($VisualStudioVersion -eq "2022") {
    $CMakeGenerator = "Visual Studio 17 2022"
    $VisualStudioFound = $True
  }
  ElseIf ($VisualStudioVersion -eq "2019") {
    $CMakeGenerator = "Visual Studio 16 2019"
    $VisualStudioFound = $True
  }
}

If ($VisualStudioFound -eq $False) {
  Write-Host -ForegroundColor Red "Failed to find the required Visual Studio version. Only '2022' and '2019' are supported."
  Return
}

If ((Test-Path -PathType Container $BuildDirectory) -eq $False) {
  New-Item -ItemType Directory $BuildDirectory | Out-Null
}

Write-Host Entering build directory"..."
Push-Location $BuildDirectory | Out-Null

Write-Host Configuring projects using $CMakeGenerator"..."
& cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ../
If ($LastExitCode -eq 0) {
  Write-Host Done"."
  Write-Host Building projects using $CMakeGenerator"..."
  &cmake --build . $CMakeExtraArgs --target reaper_ultraschall --config Debug -j
  If ($LastExitCode -eq 0) {
    Write-Host Done"."
  }
  Else {
    Write-Host -ForegroundColor Red Failed to build projects"."
  }
}
Else {
  Write-Host -ForegroundColor Red Failed to configure projects"."
}

Write-Host Leaving build directory"..."
Pop-Location | Out-Null
