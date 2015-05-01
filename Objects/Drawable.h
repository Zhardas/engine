class Drawable;
#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <Helper/Types/Size.h>
#include <Helper/Types/Position.h>

class Drawable {
private:
protected:
    Size size_ = Size(0.1f, 0.1f);
    Position position_ = Position(0.0f, 0.0f);
public:
    Drawable();
    virtual Size size() = 0;
    virtual void set_size(Size* /* new size */) = 0;
    virtual Position position() = 0;
    virtual void set_position(Position* /* new position */) = 0;
};


#endif //HEADACHE_DRAWABLE_H
