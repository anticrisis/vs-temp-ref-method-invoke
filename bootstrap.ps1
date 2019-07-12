# -- start ------------------------------------------------------------------

$me = $MyInvocation.MyCommand.Name

Write-Output "$($me): Starting"

# -- git submodules ---------------------------------------------------------

Write-Output "$($me): Updating git submodules..."
Write-Progress -Activity "Updating git submodules" -CurrentOperation "git submodule init"
Invoke-Expression -Command "git submodule init"
Write-Progress -Activity "Updating git submodules" -CurrentOperation "git submodule update"
Invoke-Expression -Command "git submodule update"
Write-Progress -Activity "Updating git submodules" -Completed

# -- fetch cmake modules ----------------------------------------------------

# Write-Output "$($me): Fetching cmake modules from github..."
# Write-Progress -Activity "Fetching cmake modules" -CurrentOperation "cotire.cmake"
# Invoke-WebRequest https://raw.githubusercontent.com/sakra/cotire/master/CMake/cotire.cmake -OutFile "./cmake/cotire.cmake"
# Write-Progress -Activity "Fetching cmake modules" -Completed

# -- vcpkg ------------------------------------------------------------------

Write-Output "$($me): Executing ./vcpkg/bootstrap-vcpkg.bat"
Invoke-Expression -Command "./vcpkg/bootstrap-vcpkg.bat"

# -- finish -----------------------------------------------------------------

Write-Output "$($me): Finished."
