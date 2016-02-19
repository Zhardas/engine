class Drawable;

#ifndef OBJECTS_DRAWABLE_H_
#define OBJECTS_DRAWABLE_H_

#include <string>
#include <list>
#include <functional>
#include "game.h"
#include "helper/types.h"
#include "../graphics/renderer.h"

class Drawable {
 protected:
  Size size_ = Size(32.0f, 32.0f);
  Size size_scaled = Size(32.0f, 32.0f);
  Position position_ = Position(0, 0);
  Size scale_ = Size(1.0f, 1.0f);
  float rotation_ = 0.0f;
  bool visible_ = true;
  bool destroy_after_animation_ = false;

 public:
  uint8_t type_ = 0;
  uint16_t id_ = 0;
  bool remove_ = false;

  Drawable();

  // Callback lists
  std::list<std::function<bool(const uint8_t &, const Position &)>> events_mouse_up_ = {};
  std::list<std::function<bool(const uint8_t &, const Position &)>> events_mouse_down_ = {};
  std::list<std::function<bool(const Position &)>> events_mouse_move_ = {};
  std::list<std::function<bool(const uint8_t &)>> events_key_up_ = {};
  std::list<std::function<bool(const uint8_t &)>> events_key_down_ = {};
  std::list<std::function<void(Drawable *)>> events_collision_ = {};

  // Collision
  void Collide(Drawable *collidable);

  // Complex
  std::list<std::unique_ptr<Drawable>> complex_list_ = {};
  bool *reload_layer_ = nullptr;
  void Add(Drawable *drawable);
  void Remove(Drawable *drawable);

  // Input events
  bool MouseUp(const uint8_t &parameter, const Position &position);
  bool MouseDown(const uint8_t &parameter, const Position &position);
  bool MouseMove(const Position &position);
  bool KeyUp(const uint8_t &parameter);
  bool KeyDown(const uint8_t &parameter);

  // Basic info
  virtual Size size() = 0;
  virtual void set_size(Size size);
  virtual void set_size(float width, float height) = 0;
  virtual Position position() = 0;
  virtual void set_position(Position position);
  virtual void set_position(float x, float y) = 0;
  virtual void set_scale(Size scale);
  virtual Size scale();
  virtual Size scaled_size();
  virtual void set_rotation(float rot);
  virtual float rotation();
  virtual bool visible();
  virtual void set_visible(bool visible);
  virtual bool Contains(const Position &pos);
  virtual void set_reload_ptr(bool *ptr);

  // Update
  virtual void Update();

  // Render
  virtual void Draw(Renderer *renderer, uint32_t *index) { };
  virtual void PrepareVertices(Renderer *renderer, v_3ct *vertices, uint32_t *index) { };
  bool is_complex_ = false;
};

#endif  // OBJECTS_DRAWABLE_H_
