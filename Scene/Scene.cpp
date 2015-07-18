#include <stdint.h>
#include "Scene.h"

Scene::Scene() {
    g_game = Game::GetInstance();
    layers = new std::list<Layer*>();
}

Scene::~Scene() {
    while (!layers->empty()) delete layers->front(), layers->pop_front();
}

void Scene::Update() {

}

void Scene::EventCall(Event event, uint8_t key, Position *parameter) {
    for(Layer* layer : *layers){
        layer->EventCall(event, key, parameter);
    }
}