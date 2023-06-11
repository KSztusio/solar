cmake_minimum_required(VERSION 3.15)
project(sim)
set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

add_subdirectory(SDL)
add_subdirectory(SDL2_gfx)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

set(SIM_SOURCES sim/simulate.cpp sim/object.cpp)
add_executable(sim ${SIM_SOURCES})
link_directories(C:/cpp/SDL2_gfx)
target_link_libraries(sim SDL2_gfx)
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(sim SDL2::SDL2main)
endif()
target_link_libraries(sim SDL2::SDL2 SDL2_gfx)
target_include_directories(sim PRIVATE ${PROJECT_SOURCE_DIR})