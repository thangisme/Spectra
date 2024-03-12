#include "ObjectLayer.h"

void ObjectLayer::update() {
    for (auto& obj : m_gameObjects) {
        obj -> update();
    }
}

void ObjectLayer::render() {
    for (auto& obj : m_gameObjects) {
        obj -> draw();
    }
}