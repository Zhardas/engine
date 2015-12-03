class Scene;

#ifndef SCENE_SCENE_H_
#define SCENE_SCENE_H_

#include <list>
#include <algorithm>
#include <iostream>
#include "../game.h"
#include "../graphics/layers/layer.h"
#include "../objects/camera.h"
#include "../objects/interfaces/collidable.h"
#include "../objects/interfaces/collider.h"
#include "../objects/drawable.h"
#include "../helper/input.h"

class Scene : public Interactive {
 private:
  std::list<Layer *> layers_ = {};
  bool CheckComplexReload(Complex *obj);

 public:
  Camera *camera_;

  Scene();

  virtual void Update();

  void CheckCollision(Drawable *drawable);

  void EventCall(Event event, uint8_t key, Position *parameter);

  std::list<Layer *> *GetLayers() { return &layers_; }

  void AddLayer(Layer *layer) {
    layers_.push_back(layer);
  }

  void RemoveLayer(Layer *layer) {
    layers_.remove(layer);
  }

  virtual void Parse(ENetPacket *packet) { }
};

#endif  // SCENE_SCENE_H_
