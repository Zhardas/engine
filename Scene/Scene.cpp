#include <stdint.h>
#include "Scene.h"

Scene::Scene() {
    g_game = Game::GetInstance();
    layers = new std::list<Layer *>();
    camera = new Camera();
}

Scene::~Scene() {
    while (!layers->empty()) delete layers->front(), layers->pop_front();
}

void Scene::Update() {

}

void Scene::EventCall(Event event, uint8_t key, Position *parameter) {
    Position pos = *parameter;
    pos.x+=camera->position.x;
    pos.y+=camera->position.y;
    for (std::list<Layer *>::reverse_iterator rit = layers->rbegin(); rit != layers->rend(); ++rit) {
        auto layer = static_cast<Layer *>(*rit);
        if (layer->EventCall(event, key, &pos)) {
            return;
        }
    }
}