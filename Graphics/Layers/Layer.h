class Layer;
#ifndef HEADACHE_LAYER_H
#define HEADACHE_LAYER_H
#include <d3d9.h>
#include <Helper/input.h>
#include <Helper/types.h>
#include <objects/drawable.h>
#include <objects/interfaces/interactive.h>
#include <objects/interfaces/complex.h>

class Layer {
 public:
  enum Type {
    STATIC = 0,
    DYNAMIC = 1
  };

  LPDIRECT3DVERTEXBUFFER9 vertex_buffer_ = nullptr;
  std::list<Drawable *> drawable_list_ = {};
  bool reload_ = true;

 private:

  Type type_;

 public:

  Layer(Type type);

  Type type() {
    return type_;
  }

  bool EventCall(Event event, unsigned char key, Position *parameter);

  void Add(Drawable *obj) {
    drawable_list_.push_back(obj);
    reload_ = true;
  }

  void Remove(Drawable *obj) {
    drawable_list_.remove(obj);
    reload_ = true;
  }
};


#endif // HEADACHE_LAYER_H