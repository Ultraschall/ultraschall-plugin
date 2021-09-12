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

Function Remove-Directory ($Directory) {
  If ((Test-Path -PathType Container $Directory) -ne $False) {
    Remove-Item -Recurse -Force $Directory | Out-Null
  }
}

Function Find-VisualStudioVersion {
  $Version = "<unknown>"
  If (Get-Command "vswhere.exe" -ErrorAction SilentlyContinue) {
    $Version = & vswhere.exe -latest -property catalog_productLineVersion | Out-String -NoNewline
  }
  Return $Version.Trim()
}

Function Find-VisualStudioDirectory {
  $Version = "<unknown>"
  If (Get-Command "vswhere.exe" -ErrorAction SilentlyContinue) {
    $Version = & vswhere.exe -latest -property installationPath | Out-String -NoNewline
  }
  Return $Version.Trim()
}

Function Parse-CMakeVersion ($VersionString) {
  $VersionStringLines = $VersionString.Split("`n`r")
  $FirstLine = $VersionStringLines[0]
  $VersionTokens = $FirstLine.Split(" ")
  $Version = $VersionTokens[2]
  Return $Version.Trim()
}

Function Find-CMakeVersion ($CMakePath) {
  $VersionString = & $CMakePath --version | Out-String
  $Version = Parse-CMakeVersion $VersionString
  Return $Version.Trim()
}

Function Compare-Versions($CurrentVersion, $RequiredVersion) {
  $CurrentVersionTokens = $CurrentVersion.Split(".")
  $RequiredVersionTokens = $RequiredVersion.Split(".")
  If ($CurrentVersionTokens.Count -ge $RequiredVersionTokens.Count) {
    $TokenCount = $CurrentVersionTokens.count
  }
  Else {
    $TokenCount = $RequiredVersionTokens.count
  }
  For ($i = 0; $i -lt $TokenCount; $i++) {
    $CompareResult = $CurrentVersionTokens[$i].CompareTo($RequiredVersionTokens[$i])
    If ($CompareResult -eq -1) {
      Return 2
    }
    ElseIf ($CompareResult -eq 1) {
      Return 1
    }
  }

  Return 0
}
