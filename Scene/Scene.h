class Scene;

#ifndef HEADACHE_SCENE_H
#define HEADACHE_SCENE_H

#include <Objects/TexturedQuad.h>
#include <Graphics/Renderer.h>
#include <Game.h>
#include <list>
#include <Helper/input.h>
#include <algorithm>
#include <Objects/Text.h>
#include <Graphics/Font.h>
#include <Helper/input.h>
#include <iostream>
#include <Graphics/Layers/Layer.h>

class Scene {
private:
    bool loaded;
    Game *g_game;
    std::list<Layer *> *layers;
public:
    Scene();

    virtual ~Scene();

    virtual void Update();

    void EventCall(Event event, uint8_t key, Position *parameter);

    std::list<Layer *> *GetLayers() { return layers; };

    void AddLayer(Layer *layer) {
        layers->push_back(layer);
    }

    void RemoveLayer(Layer *layer) {
        layers->remove(layer);
    }
};


#endif //HEADACHE_SCENE_H
