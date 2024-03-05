#ifndef PLATFORMER_SDLGAMEOBJECT_H
#define PLATFORMER_SDLGAMEOBJECT_H

#include <string>
#include "Game.h"
#include "Vector2D.h"


class SDLGameObject : public GameObject {
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
protected:
    Vector2D m_pos;
    Vector2D m_velocity;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_textureID;
};

#endif //PLATFORMER_SDLGAMEOBJECT_H
