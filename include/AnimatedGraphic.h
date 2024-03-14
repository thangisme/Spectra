#ifndef PLATFORMER_ANIMATEDGRAPHIC_H
#define PLATFORMER_ANIMATEDGRAPHIC_H


#include "GameObject.h"
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:

    AnimatedGraphic();
    virtual ~AnimatedGraphic() {}

    virtual void load(LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    int m_animSpeed;
    int m_frameCount;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};


#endif //PLATFORMER_ANIMATEDGRAPHIC_H
