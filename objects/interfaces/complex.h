class Complex;
#ifndef OVERLORD_COMPLEX_H
#define OVERLORD_COMPLEX_H
#include <objects/drawable.h>

class Complex{
 public:
  virtual void Add(std::list<Drawable*> &list) = 0;
  virtual void Remove(std::list<Drawable *> &list) = 0;
};

#endif //OVERLORD_COMPLEX_H