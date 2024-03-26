#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>


#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject {
public:
    virtual ~GameObject() {}

    virtual void load(const LoaderParams* pParams) = 0;

    virtual void draw() = 0;

    virtual void update() = 0;

    virtual void clean() = 0;

    virtual void collision() = 0;

    virtual std::string type() = 0;

    Vector2D &getPosition() { return m_position; }

    int getWidth() { return m_width * m_scaleFactor; }

    int getHeight() { return m_height * m_scaleFactor; }

    void scroll(float scrollSpeed) { m_position.setX(m_position.getX() - scrollSpeed); }

    bool updating() { return m_bUpdating; }

    bool dead() { return m_bDead; }

    bool dying() { return m_bDying; }

    bool isFlipVertical() { return m_bFlipVertical; }

    void setFlipVertical(bool flip) { m_bFlipVertical = flip; }

    void setUpdating(bool updating) { m_bUpdating = updating; }

protected:
    GameObject() : m_position(0, 0),
                   m_velocity(0, 0),
                   m_acceleration(0, 0),
                   m_width(0),
                   m_height(0),
                   m_currentRow(0),
                   m_currentFrame(0),
                   m_bUpdating(false),
                   m_bDead(false),
                   m_bDying(false),
                   m_bFlipVertical(false),
                   m_angle(0),
                   m_alpha(255),
                   m_scaleFactor(1){}

    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;
    int m_scaleFactor;

    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;

    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;

    bool m_bFlipVertical;

    double m_angle;

    int m_alpha;
};

#endif //GAMEOBJECT_H
