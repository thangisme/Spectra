#ifndef PLATFORMER_OBJECTLAYER_H
#define PLATFORMER_OBJECTLAYER_H

#include "Layer.h"
#include "GameObject.h"
#include <vector>
#include "CollisionManager.h"

class Level;

class ObjectLayer : public Layer {
public:
    virtual void update(Level* pLevel);
    virtual void render();

    std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }
private:
    std::vector<GameObject*> m_gameObjects;
    CollisionManager m_collisionManager;
};

#endif //PLATFORMER_OBJECTLAYER_H
