#ifndef PLATFORMER_SHOOTEROBJECT_H
#define PLATFORMER_SHOOTEROBJECT_H

#include <string>
#include "Game.h"
#include "Vector2D.h"
#include "GameObjectFactory.h"

class ShooterObject : public GameObject
{
public:
    virtual ~ShooterObject() {}
    virtual void load(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() {}
    virtual void collision() {}
    virtual std::string type() { return "SDLGameObject"; }
protected:
    ShooterObject();
    void doDyingAnimation();
    int m_bulletFiringSpeed;
    int m_bulletCounter;
    int m_moveSpeed;
    int m_dyingTime;
    int m_dyingCounter;
    bool m_bPlayedDeathSound;
};

#endif //PLATFORMER_SHOOTEROBJECT_H
