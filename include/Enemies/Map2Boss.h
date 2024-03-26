#ifndef SPECTRA_MAP2BOSS_H
#define SPECTRA_MAP2BOSS_H


#include "Enemy.h"

class Map2Boss : public Enemy {
public:
    Map2Boss();

    virtual ~Map2Boss(){};
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
    bool m_entered;
};

class Map2BossCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new Map2Boss();
    }
};

#endif //SPECTRA_MAP2BOSS_H
