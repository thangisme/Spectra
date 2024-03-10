#ifndef PLATFORMER_LAYER_H
#define PLATFORMER_LAYER_H

#include <vector>

class Layer {
public:
    virtual void render() = 0;
    virtual void update() = 0;

    std::vector<Layer*> getLayers() { return m_layers; }
protected:
    virtual ~Layer() {}
    std::vector<Layer*> m_layers;
};

#endif //PLATFORMER_LAYER_H
