param(
    [string]$BuildDir = "build",
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug"
)

$ErrorActionPreference = "Stop"
$repositoryDir = Split-Path -Parent $PSScriptRoot
$buildPath = if ([IO.Path]::IsPathRooted($BuildDir)) {
    $BuildDir
} else {
    Join-Path $repositoryDir $BuildDir
}

Push-Location $repositoryDir
try {
    cmake -S . -B $buildPath
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    cmake --build $buildPath --config $Configuration
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    $executableCandidates = @(
        (Join-Path (Join-Path $buildPath $Configuration) "minicad.exe"),
        (Join-Path $buildPath "minicad.exe"),
        (Join-Path (Join-Path $buildPath $Configuration) "minicad"),
        (Join-Path $buildPath "minicad")
    )
    $executable = $executableCandidates |
        Where-Object { Test-Path -LiteralPath $_ -PathType Leaf } |
        Select-Object -First 1

    if (-not $executable) {
        throw "Could not find the MiniCAD executable in $buildPath."
    }

    & $executable
    exit $LASTEXITCODE
} finally {
    Pop-Location
}
