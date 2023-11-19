cmake_minimum_required(VERSION 3.10)

project(base)  # Main game project
project(dataCreater)  # Extra program, for compailing all data to one file

# Set source files
add_executable( base
    # Base includes and defines
    src/include.hpp
    src/define.hpp
    src/structs.hpp

    # Function of initialasing all data
    src/init.hpp
    src/init.cpp

    # Functions of loading all in-game data
    src/dataLoader.hpp
    src/dataLoader.cpp

    # Base interface
    src/baseHud.hpp
    src/baseHud.cpp

    # Interface of game pausing
    src/pause.hpp
    src/pause.cpp

    # System of initialasing file loading and unloading
    src/initFile.hpp
    src/initFile.cpp

    # In game classes
    src/entity.hpp
    src/entity.cpp

    # Main function
    src/main.cpp 
)

# Setting static dlls
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# Including external libraries

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# Finding place of external libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# libzib include
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake")
find_package(libzip REQUIRED)

# Base project
# Including external libraries
target_include_directories( base
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2_image_INCLUDE_DIRS}
    PUBLIC ${SDL2_ttf_config_path}
    PUBLIC ${SDL2_mixer_config_path}
    PUBLIC &{libzip_INCLUDE_DIRS}
)

target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf mingw32)
target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_mixer::SDL2_mixer mingw32)
target_link_libraries(base PUBLIC ${libzip_LIBRARIES} libzip::zip)
