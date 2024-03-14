#ifndef PLATFORMER_COLLISION_H
#define PLATFORMER_COLLISION_H

#include <SDL.h>

const static int s_buffer = 4;

static bool RectRect(SDL_Rect* A, SDL_Rect* B) {
    int aHBuf = A -> h / s_buffer;
    int aWBuf = A -> w / s_buffer;

    int bHBuf = B -> h / s_buffer;
    int bWBuf = B -> w / s_buffer;

    // if bottom of A is less than the top of B => no collision
    if ((A -> y + A -> h) - aHBuf <= A -> y + bHBuf) { return false; }

    // if the top of A is more than the bottom of B => no collision
    if ((A -> y + aHBuf) >= (B -> y + B -> h) - bHBuf) { return false; }

    // if the right of A is less than the left of B => no collision
    if ((A -> x + A -> w) - aWBuf <= B -> x + bWBuf) { return false; }

    if ((A -> x + aWBuf) >= (B -> x + B -> w) - bWBuf) { return false; }

    return true;
}

#endif //PLATFORMER_COLLISION_H
