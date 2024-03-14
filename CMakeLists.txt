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
        include/ShooterObject.h
        src/ShooterObject.cpp
        include/Player.h
        src/Player.cpp
        include/Enemy.h
        include/Vector2D.h
        src/Vector2D.cpp
        include/InputHandler.h
        src/InputHandler.cpp
        include/GameState.h
        include/MainMenuState.h
        src/MainMenuState.cpp
        include/PlayState.h
        src/PlayState.cpp
        include/GameStateManager.h
        src/GameStateManager.cpp
        include/MenuButton.h
        src/MenuButton.cpp
        include/PauseState.h
        src/PauseState.cpp
        include/GameOverState.h
        src/GameOverState.cpp
        include/GameObjectFactory.h
        src/GameObjectFactory.cpp
        include/StateParser.h
        src/StateParser.cpp
        include/MenuState.h
        include/tinyxml2.cpp
        include/tinyxml2.h
        include/base64.cpp
        include/base64.h
        include/Level.h
        include/Layer.h
        src/Level.cpp
        include/TileLayer.h
        include/LevelParser.h
        src/LevelParser.cpp
        src/TileLayer.cpp
        include/helper.h
        include/ObjectLayer.h
        src/ObjectLayer.cpp
        include/AnimatedGraphic.h
        src/AnimatedGraphic.cpp
        include/SoundManager.h
        src/SoundManager.cpp
        include/ScrollingBackground.h
        src/ScrollingBackground.cpp
        include/Bullet.h
        include/BulletHandler.h
        src/BulletHandler.cpp
        include/CollisionManager.h
        src/CollisionManager.cpp

)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL2/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "SDL2/x86_64-w64-mingw32")

# Locate SDL2 and SDL_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_subdirectory(include/zlib)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${ZLIB_DEPS_DIR}
        include
)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} zlib)