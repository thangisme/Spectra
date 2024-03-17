#ifndef PLAYER_H
#define PLAYER_H

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject {
public:
    Player();

    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams* pParams);
    virtual void collision();

    virtual std::string type() { return "Player";}
    Vector2D getVelocity() const { return m_velocity; }
private:
    void resurrect();
    void handleInput();
    void handleAnimation();

    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator {
    GameObject* createGameObject() const {
        return new Player();
    }
};

#endif //PLAYER_H
