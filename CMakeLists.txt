cmake_minimum_required(VERSION 3.22)
project(platformer)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: src/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} src/main.cpp
        include/Game.h
        src/Game.cpp
        include/TextureManager.h
        src/TextureManager.cpp
        include/GameObject.h
        include/LoaderParams.h
        include/SDLGameObject.h
        src/SDLGameObject.cpp
        include/Player.h
        src/Player.cpp
        include/Enemy.h
        src/Enemy.cpp
        include/Vector2D.h
        src/Vector2D.cpp
        include/InputHandler.h
        src/InputHandler.cpp

)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)

# Locate SDL2 and SDL_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        include
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})