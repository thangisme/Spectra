#ifndef PLATFORMER_LAYER_H
#define PLATFORMER_LAYER_H

#include <vector>

class Level;

class Layer {
public:
    virtual void render() = 0;
    virtual void update(Level* pLevel) = 0;

    std::vector<Layer*> getLayers() { return m_layers; }
protected:
    virtual ~Layer() {}
    std::vector<Layer*> m_layers;
};

#endif //PLATFORMER_LAYER_H
