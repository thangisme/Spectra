#ifndef PLATFORMER_MENUSTATE_H
#define PLATFORMER_MENUSTATE_H

#include <vector>
#include "GameState/GameState.h"

class MenuState : public GameState {
protected:
    typedef void(*Callback) ();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

#endif //PLATFORMER_MENUSTATE_H
