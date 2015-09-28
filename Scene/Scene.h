class Scene;

#ifndef HEADACHE_SCENE_H
#define HEADACHE_SCENE_H

#include <list>
#include <algorithm>
#include <iostream>
#include "game.h"
#include "graphics/layers/layer.h"
#include "objects/camera.h"
#include "objects/interfaces/collidable.h"
#include "objects/drawable.h"
#include "Helper/input.h"
#include "Helper/input.h"

class Scene {
 private:
  std::list<Layer *> layers_ = {};
 public:
  Camera *camera_;

  Scene();

  virtual ~Scene();

  virtual void Update();

  void CheckCollision(Drawable* drawable);

  void EventCall(Event event, uint8_t key, Position *parameter);

  std::list<Layer *> *GetLayers() { return &layers_; };

  void AddLayer(Layer *layer) {
    layers_.push_back(layer);
  }

  void RemoveLayer(Layer *layer) {
    layers_.remove(layer);
  }
  //std::list<Collidable *> collidables_ = {};
};


#endif //HEADACHE_SCENE_H
