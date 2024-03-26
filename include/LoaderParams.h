#ifndef PLATFORMER_LOADERPARAMS_H
#define PLATFORMER_LOADERPARAMS_H

#include <string>

class LoaderParams {
public:
    LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0, int scaleFactor = 1, bool isFlipVertical = false) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames), m_animSpeed(animSpeed), m_callbackID(callbackID), m_scaleFactor(scaleFactor), m_isFlipVertical(isFlipVertical) {}
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_width; };
    int getHeight() const { return m_height; };
    std::string getTextureID() const { return m_textureID; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }
    int getScaleFactor() const { return m_scaleFactor; }

    bool isTurnLeft() const { return m_isFlipVertical; }

private:
    int m_x;
    int m_y;

    int m_width;
    int m_height;
    int m_scaleFactor;

    int m_numFrames;
    int m_animSpeed;

    int m_callbackID;

    std::string m_textureID;

    bool m_isFlipVertical;
};

#endif //PLATFORMER_LOADERPARAMS_H
