#ifndef PLATFORMER_SDLGAMEOBJECT_H
#define PLATFORMER_SDLGAMEOBJECT_H

#include <string>
#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"

class SDLGameObject : public GameObject {
public:
    SDLGameObject(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
protected:
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_textureID;
};

#endif //PLATFORMER_SDLGAMEOBJECT_H
