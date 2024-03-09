#ifndef PLATFORMER_GAMEOBJECTFACTORY_H
#define PLATFORMER_GAMEOBJECTFACTORY_H

#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator {
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator(){};
};

class GameObjectFactory {
public:
    static GameObjectFactory* Instance() {
        if (s_pInstance == 0){
            s_pInstance = new GameObjectFactory();
            return s_pInstance;
        }

        return s_pInstance;
    }
    bool registerType(std::string typeID, BaseCreator* pCreator);
    GameObject* create(std::string typeID);
private:
    std::map<std::string, BaseCreator*> m_creators;
    static GameObjectFactory* s_pInstance;
};

#endif //PLATFORMER_GAMEOBJECTFACTORY_H
