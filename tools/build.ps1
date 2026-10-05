[CmdletBinding()]
param(
    [string]$BuildDir = 'build',
    [ValidateSet('Debug', 'Release', 'RelWithDebInfo')]
    [string]$Configuration = 'RelWithDebInfo',
    [string]$DataDir = $(if ($env:DL2_DATA) { $env:DL2_DATA } else { 'C:\GOG Games\Deadlock 2' }),
    [string]$VcpkgRoot = $(if ($env:VCPKG_ROOT) { $env:VCPKG_ROOT } else { 'C:\vcpkg' }),
    [string]$Sdl2Dir = $env:SDL2_DIR,
    [string]$PythonExecutable = $env:Python3_EXECUTABLE,
    [switch]$Test
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
# CMake decodes MSVC /showIncludes using the console input code page, while cl
# emits using its output code page. Keep both equal, including localized VS.
$previousInputEncoding = [Console]::InputEncoding
$previousOutputEncoding = [Console]::OutputEncoding
$previousPipeEncoding = $OutputEncoding
$utf8 = [System.Text.UTF8Encoding]::new($false)
[Console]::InputEncoding = $utf8
[Console]::OutputEncoding = $utf8
$OutputEncoding = $utf8
try {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    if (-not (Test-Path -LiteralPath $vswhere)) {
        throw 'Install Visual Studio C++ Build Tools (including Ninja) before building.'
    }
    $installation = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if ($LASTEXITCODE -ne 0 -or -not $installation) {
        throw 'No Visual Studio installation with the C++ toolchain was found.'
    }
    $devShell = Join-Path $installation 'Common7\Tools\VsDevCmd.bat'
    # Import the toolchain environment into this process without printing its contents.
    $environmentLines = & $env:ComSpec /d /c "call `"$devShell`" -no_logo -arch=x64 -host_arch=x64 >nul && set"
    if ($LASTEXITCODE -ne 0) { throw 'Visual Studio environment initialization failed.' }
    foreach ($line in $environmentLines) {
        $separator = $line.IndexOf('=')
        if ($separator -gt 0) {
            [Environment]::SetEnvironmentVariable($line.Substring(0, $separator), $line.Substring($separator + 1), 'Process')
        }
    }
    # Visual Studio's CMake tools are not always exported by VsDevCmd.
    $cmakeTools = Join-Path $installation 'Common7\IDE\CommonExtensions\Microsoft\CMake'
    $env:Path = "$(Join-Path $cmakeTools 'CMake\bin');$(Join-Path $cmakeTools 'Ninja');$env:Path"
    $dependencyArgs = @()
    if ($Sdl2Dir) {
        if (-not (Test-Path -LiteralPath (Join-Path $Sdl2Dir 'sdl2-config.cmake')) -and
            -not (Test-Path -LiteralPath (Join-Path $Sdl2Dir 'SDL2Config.cmake'))) {
            throw "SDL2 CMake package not found: $Sdl2Dir"
        }
        $dependencyArgs += "-DSDL2_DIR=$Sdl2Dir"
    } else {
        $toolchain = Join-Path $VcpkgRoot 'scripts\buildsystems\vcpkg.cmake'
        if (-not (Test-Path -LiteralPath $toolchain)) { throw "vcpkg toolchain not found: $toolchain. Supply -Sdl2Dir to use an SDL2 SDK instead." }
        $dependencyArgs += "-DCMAKE_TOOLCHAIN_FILE=$toolchain", '-DVCPKG_TARGET_TRIPLET=x64-windows'
    }
    if ($PythonExecutable) {
        if (-not (Test-Path -LiteralPath $PythonExecutable)) { throw "Python executable not found: $PythonExecutable" }
        $dependencyArgs += "-DPython3_EXECUTABLE=$PythonExecutable"
    }

    Push-Location $projectRoot
    try {
        & cmake -S . -B $BuildDir -G Ninja "-DCMAKE_BUILD_TYPE=$Configuration" `
            @dependencyArgs `
            -DBUILD_TESTING=ON "-DDL2_DATA_DIR=$DataDir"
        if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed ($LASTEXITCODE)." }
        & cmake --build $BuildDir --config $Configuration
        if ($LASTEXITCODE -ne 0) { throw "Build failed ($LASTEXITCODE)." }
        if ($Test) {
            & ctest --test-dir $BuildDir -C $Configuration --output-on-failure --no-tests=error --output-junit ctest-results.xml
            if ($LASTEXITCODE -ne 0) { throw "Tests failed ($LASTEXITCODE)." }
        }
    } finally {
        Pop-Location
    }
} finally {
    [Console]::InputEncoding = $previousInputEncoding
    [Console]::OutputEncoding = $previousOutputEncoding
    $OutputEncoding = $previousPipeEncoding
}
