# -- start ------------------------------------------------------------------

$me = $MyInvocation.MyCommand.Name

Write-Output "$($me): Starting"

# -- vcpkg ------------------------------------------------------------------

Write-Output "$($me): Executing ./vcpkg/vcpkg.exe install @packages.txt"
Invoke-Expression -Command "./vcpkg/vcpkg.exe --% install @packages.txt"

# -- finish -----------------------------------------------------------------

Write-Output "$($me): Finished."
