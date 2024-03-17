#ifndef PLATFORMER_TURRET_H
#define PLATFORMER_TURRET_H

#include "Enemy.h"

class Turret : public Enemy {
public:
    Turret();

    virtual ~Turret();
    virtual void load(const LoaderParams* pParams);
    virtual void draw();
    virtual void collision();
    virtual void update();
    virtual void clean();
protected:
    int m_dyingTime;
    int m_health;
    int m_bulletFiringSpeed;
};

class TurretCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new Turret();
    }
};

#endif //PLATFORMER_TURRET_H
