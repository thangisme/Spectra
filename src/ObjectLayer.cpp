#include "ObjectLayer.h"
#include "Level.h"

void ObjectLayer::update(Level* pLevel) {
    m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
    m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

    if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() < Game::Instance()->getGameWidth() && pLevel -> getPlayer() -> getPosition().getY() + pLevel -> getPlayer() -> getHeight() < Game::Instance() -> getGameHeight())
    {
        m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), *pLevel->getCollisionLayers());
    }

    for (auto& obj : m_gameObjects) {
        if (obj -> getPosition().getX() <= Game::Instance() -> getGameWidth()) {
            obj ->setUpdating(true);
            obj -> update();
        } else {
            if (obj -> type() != std::string("Player")) {
                obj ->setUpdating(false);
                obj ->scroll(Game::Instance() -> getScrollSpeed());
            } else {
                obj -> update();
            }
        }
    }
}

void ObjectLayer::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}