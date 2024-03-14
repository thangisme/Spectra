#ifndef PLATFORMER_SCROLLINGBACKGROUND_H
#define PLATFORMER_SCROLLINGBACKGROUND_H

#include "ShooterObject.h"

class ScrollingBackground : public ShooterObject {
public:
    virtual ~ScrollingBackground() {}
    ScrollingBackground();

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
private:
    int m_scrollSpeed;

    int count;
    int maxCount;

    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;

    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;

    int m_srcRect1Width;
    int m_srcRect2Width;

    int m_destRect1Width;
    int m_destRect2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};


#endif //PLATFORMER_SCROLLINGBACKGROUND_H
