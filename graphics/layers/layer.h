class Layer;

#ifndef GRAPHICS_LAYERS_LAYER_H_
#define GRAPHICS_LAYERS_LAYER_H_

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
  std::list<std::unique_ptr<Drawable>> drawable_list_;
  bool reload_ = true;

 private:
  Type type_;

 public:
  bool visible_ = true;

  explicit Layer(Type type);

  Type type() { return type_; }

  bool EventCall(Event event,
                 uint8_t key,
                 const Position &parameter,
                 Drawable *drawable);
  bool EventCall(Event event, uint8_t key, const Position &parameter);
  void Add(Drawable* obj);
  void Remove(Drawable *obj);
};

#endif // GRAPHICS_LAYERS_LAYER_H_
