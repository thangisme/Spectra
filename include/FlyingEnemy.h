#ifndef PLATFORMER_FLYINGENEMY_H
#define PLATFORMER_FLYINGENEMY_H

#include "Enemy.h"

class FlyingEnemy : public Enemy {
public:
    FlyingEnemy();

    virtual ~FlyingEnemy(){};
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void clean();
    virtual void update();
    virtual void collision();
protected:
    int m_dyingTime;
    int m_health;
    int m_bulletFiringSpeed;
};

class FlyingEnemyCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new FlyingEnemy();
    }
};


#endif //PLATFORMER_FLYINGENEMY_H
