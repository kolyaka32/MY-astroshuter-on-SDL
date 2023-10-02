cmake_minimum_required(VERSION 3.10)

project(base)

# Set source files
add_executable( ${PROJECT_NAME}
    # Base includes and defines
    src/include.hpp
    src/define.hpp
    src/structs.hpp

    # Function of initialasing all data
    src/init.hpp
    src/init.cpp

    # Functions with images
    src/images.hpp
    src/images.cpp

    # Functions with audio
    src/audio.hpp
    src/audio.cpp

    # Base interface
    src/baseHud.hpp
    src/baseHud.cpp

    #
    src/pause.hpp
    src/pause.cpp

    # 
    src/initFile.hpp
    src/initFile.cpp

    # In game classes
    src/entity.hpp
    src/entity.cpp

    # Main function
    src/main.hpp
    src/main.cpp
    
)
# Setting static dlls
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# Including external libraries
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)


target_include_directories( ${PROJECT_NAME}
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2_image_INCLUDE_DIRS}
    PUBLIC ${SDL2_ttf_config_path}
    PUBLIC ${SDL2_mixer_config_path}
)

target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf mingw32)
target_link_libraries(base PUBLIC ${SDL2_LIBRARIES} SDL2_mixer::SDL2_mixer mingw32)
