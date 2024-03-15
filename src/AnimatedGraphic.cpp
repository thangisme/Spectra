
#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() : ShooterObject()
{

}

void AnimatedGraphic::load(const LoaderParams* pParams)
{
    ShooterObject::load(pParams);
    m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
    ShooterObject::draw();
}

void AnimatedGraphic::update()
{
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
    ShooterObject::clean();
}