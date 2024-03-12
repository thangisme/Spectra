#ifndef PLATFORMER_OBJECTLAYER_H
#define PLATFORMER_OBJECTLAYER_H

#include "Layer.h"
#include "GameObject.h"
#include <vector>

class ObjectLayer : public Layer {
public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }
private:
    std::vector<GameObject*> m_gameObjects;
};

#endif //PLATFORMER_OBJECTLAYER_H
