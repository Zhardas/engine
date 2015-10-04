class Complex;
#ifndef OVERLORD_COMPLEX_H
#define OVERLORD_COMPLEX_H
#include <objects/drawable.h>
#include <Graphics/Layers/Layer.h>

class Complex: public Drawable {
 public:
  std::list<Drawable *> complex_list_;
  bool reload_layer_ = false;

  void Add(Drawable *drawable) {
    complex_list_.push_back(drawable);
    reload_layer_ = true;
  }

  void Remove(Drawable *drawable) {
    complex_list_.push_back(drawable);
    reload_layer_ = true;
  }
};

#endif //OVERLORD_COMPLEX_H