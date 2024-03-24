#ifndef PLATFORMER_FLOATINGENEMY_H
#define PLATFORMER_FLOATINGENEMY_H

#include "Enemy.h"

class FloatingEnemy : public Enemy {
public:
    FloatingEnemy();

    virtual ~FloatingEnemy(){};
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void clean();
    virtual void update();
    virtual void collision();
protected:
    int m_dyingTime;
    int m_health;
    int m_moveSpeed;
};

class FloatingEnemyCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new FloatingEnemy();
    }
};

#endif //PLATFORMER_FLOATINGENEMY_H
