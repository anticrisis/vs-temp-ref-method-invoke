# CMakeList.txt : CMake project for vs-temp-ref-method-invoke, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (vs-temp-ref-method-invoke "vs-temp-ref-method-invoke.cpp" "vs-temp-ref-method-invoke.h")

target_compile_features(vs-temp-ref-method-invoke PUBLIC cxx_std_17)

target_include_directories(vs-temp-ref-method-invoke PUBLIC
    SYSTEM ${GSL_INCLUDE_DIR})

# TODO: Add tests and install targets if needed.
