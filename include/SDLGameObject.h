#ifndef PLATFORMER_SDLGAMEOBJECT_H
#define PLATFORMER_SDLGAMEOBJECT_H

#include <string>
#include "Game.h"
#include "Vector2D.h"
#include "GameObjectFactory.h"


class SDLGameObject : public GameObject {
public:
    SDLGameObject();

    void load(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    Vector2D& getPosition() { return m_pos; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
protected:
    Vector2D m_pos;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;

    std::string m_textureID;
};

class SDLObjectCreator : public BaseCreator {
    GameObject* createGameObject() const
    {
        return new SDLGameObject();
    }
};

#endif //PLATFORMER_SDLGAMEOBJECT_H
