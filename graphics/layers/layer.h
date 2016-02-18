class Layer;
#ifndef HEADACHE_LAYER_H
#define HEADACHE_LAYER_H
// TODO(Zhardas): Remove specific graphics API requirements in order to add other APIs later.
#include <d3d9.h>
#include <list>
#include <helper/input.h>
#include <helper/types.h>
#include <objects/drawable.h>

class Layer {
 public:
  enum Type {
    STATIC = 0,
    DYNAMIC = 1
  };
  LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;
  std::list<std::shared_ptr<Drawable>> drawable_list_ = {};
  bool reload_ = true;

 private:
  Type type_;

 public:
  bool visible_ = true;

  Layer(Type type);

  Type type() {
    return type_;
  }

  bool EventCall(Event event,
                 uint8_t key,
                 const Position &parameter,
                 std::shared_ptr<Drawable> drawable);
  bool EventCall(Event event, uint8_t key, const Position &parameter);
  void Add(std::shared_ptr<Drawable> obj);
  void Remove(std::shared_ptr<Drawable> obj);
};


#endif // HEADACHE_LAYER_H
