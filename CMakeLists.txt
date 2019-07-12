# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.14)

#
# -- vcpkg configuration ----------------------------------------------------
#
# configure vcpkg from $ENV{VCPKG_ROOT} - must appear before project()
# default to in-project subdirector (eg via git submodule)
# 
if (NOT DEFINED ENV{VCPKG_ROOT})
  set(ENV{VCPKG_ROOT} "./vcpkg")
endif()

if (NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
  set(ENV{VCPKG_DEFAULT_TRIPLET} "x64-windows")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif()

# -- project ----------------------------------------------------------------

project ("vs-temp-ref-method-invoke")

find_path(GSL_INCLUDE_DIR "gsl/gsl")

# Include sub-projects.
add_subdirectory ("vs-temp-ref-method-invoke")
