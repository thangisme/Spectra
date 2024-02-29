#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "LoaderParams.h"

class GameObject {
public:
    virtual void draw() =0;
    virtual void update() =0;
    virtual void clean() =0;
protected:
    GameObject(const LoaderParams* pParams);
    virtual ~GameObject();
};

#endif //GAMEOBJECT_H
