# Setting minimum required for cmake versions
cmake_minimum_required(VERSION 3.5)

# Setting minimal c++ version for work
set(CMAKE_CXX_STANDARD 14)

# Creating project
project(Astroshuter)

# Setting prefix path for finding library
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Look for a SDL3 package
find_package(SDL3 REQUIRED SDL3-shared)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(libzip CONFIG REQUIRED)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3::SDL3)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE libzip::zip)
