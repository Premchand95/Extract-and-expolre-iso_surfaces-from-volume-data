
cmake_minimum_required(VERSION 2.8)

PROJECT(prem)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(prem MACOSX_BUNDLE prem.cxx )

target_link_libraries(prem ${VTK_LIBRARIES})
