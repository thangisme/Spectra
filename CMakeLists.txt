cmake_minimum_required(VERSION 3.22)
project(Spectra)

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
        include/GameState/GameState.h
        include/GameState/MainMenuState.h
        src/GameState/MainMenuState.cpp
        include/GameState/PlayState.h
        src/GameState/PlayState.cpp
        include/GameState/GameStateManager.h
        src/GameState/GameStateManager.cpp
        include/MenuButton.h
        src/MenuButton.cpp
        include/GameState/PauseState.h
        src/GameState/PauseState.cpp
        include/GameState/GameOverState.h
        src/GameState/GameOverState.cpp
        include/GameObjectFactory.h
        src/GameObjectFactory.cpp
        include/GameState/StateParser.h
        src/StateParser.cpp
        include/GameState/MenuState.h
        include/Libraries/tinyxml2.cpp
        include/Libraries/tinyxml2.h
        include/Libraries/base64.cpp
        include/Libraries/base64.h
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
        include/Enemies/Turret.h
        src/Enemies/Turret.cpp
        include/Enemies/FlyingEnemy.h
        src/Enemies/FlyingEnemy.cpp
        include/Enemies/FloatingEnemy.h
        src/Enemies/FloatingEnemy.cpp
        include/Enemies/Map1Boss.h
        src/Enemies/Map1Boss.cpp
        include/GameState/WinState.h
        src/GameState/WinState.cpp
        include/GameState/LevelCompletedState.h
        src/GameState/LevelCompletedState.cpp
        include/GameState/GuideScreen.h
        src/GameState/GuideScreen.cpp
        include/Enemies/Map2Boss.h
        src/Enemies/Map2Boss.cpp

)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#Locate ZLib library
find_package(ZLIB REQUIRED)

# Locate SDL2 and SDL_image libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)


include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        include
)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ZLIB::ZLIB)