# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("vs-temp-ref-method-invoke")

find_path(GSL_INCLUDE_DIR "gsl/gsl")

# Include sub-projects.
add_subdirectory ("vs-temp-ref-method-invoke")
