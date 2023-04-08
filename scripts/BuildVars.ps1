
$vsPath = & (Join-Path ${env:ProgramFiles(x86)} '\\Microsoft Visual Studio\\Installer\\vswhere.exe') -property installationPath
Import-Module (Join-Path $vsPath 'Common7\\Tools\\Microsoft.VisualStudio.DevShell.dll')
# Enter-VsDevShell -VsInstallPath $vsPath -SkipAutomaticLocation -DevCmdArguments "-arch=x64 -host_arch=x64"
Enter-VsDevShell -VsInstallPath $vsPath -SkipAutomaticLocation -DevCmdArguments "-arch=x64" | Out-Null
