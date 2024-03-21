#ifndef PLATFORMER_MAP1BOSS_H
#define PLATFORMER_MAP1BOSS_H


#include "Enemy.h"

class Map1Boss : public Enemy {
public:
    Map1Boss();

    virtual ~Map1Boss(){};
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void clean();
    virtual void update();
    virtual void collision();
protected:
    int m_dyingTime;
    int m_health;
    int m_bulletFiringSpeed;
    int m_moveSpeed;
};

class Map1BossCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new Map1Boss();
    }
};


#endif //PLATFORMER_MAP1BOSS_H
