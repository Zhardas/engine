class Complex;
#ifndef OVERLORD_COMPLEX_H
#define OVERLORD_COMPLEX_H
#include <objects/drawable.h>

class Complex {
 public:
  std::list<Drawable *> complex_list_;

  void Add(Drawable *drawable) {
    complex_list_.push_back(drawable);
  }

  void Remove(Drawable *drawable) {
    complex_list_.push_back(drawable);
  }
};

#endif //OVERLORD_COMPLEX_H