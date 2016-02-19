class Scene;

#ifndef SCENE_SCENE_H_
#define SCENE_SCENE_H_

#include <list>
#include <algorithm>
#include <iostream>
#include "../game.h"
#include "../graphics/layers/layer.h"
#include "../objects/camera.h"
#include "../objects/drawable.h"
#include "../helper/input.h"

class Scene {
 private:
  std::list<std::unique_ptr<Layer>> layers_ = {};

 public:
  std::unique_ptr<Camera> camera_ = std::make_unique<Camera>();

  // Callback lists
  std::list<std::function<bool(const uint8_t &, const Position &position)>> events_mouse_up_ = {};
  std::list<std::function<bool(const uint8_t &, const Position &position)>> events_mouse_down_ = {};
  std::list<std::function<bool(const Position &position)>> events_mouse_move_ = {};
  std::list<std::function<bool(const uint8_t &)>> events_key_up_ = {};
  std::list<std::function<bool(const uint8_t &)>> events_key_down_ = {};

  Scene() { }

  // Update
  virtual void Update();

  // Collision
  void CheckCollision(Drawable *collider);

  // Input events
  void EventCall(Event event, uint8_t key, Position *parameter);
  bool KeyUp(const uint8_t &parameter);
  bool KeyDown(const uint8_t &parameter);
  bool MouseUp(const uint8_t &parameter, const Position &position);
  bool MouseDown(const uint8_t &parameter, const Position &position);
  bool MouseMove(const Position &position);

  // Layers
  std::list<std::unique_ptr<Layer>> *GetLayers() { return &layers_; }
  void AddLayer(Layer *layer);
  void RemoveLayer(Layer *layer);

  // TODO(Zhardas): Make networking-related includes/methods/etc more "modular".
  virtual void Parse(ENetPacket *packet) { }
};

#endif  // SCENE_SCENE_H_
