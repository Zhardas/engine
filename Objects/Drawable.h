//
// Created by Owner on 30.04.2015.
//

#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <Helper/Types/Size.h>
#include <Helper/Types/Position.h>

class Drawable {
private:
    Size size_;
    Position position_;
public:
    virtual Size size() = 0;
    virtual void set_size(Size /* new size */) = 0;
    virtual Position position() = 0;
    virtual void set_position(Position /* new position */) = 0;
};


#endif //HEADACHE_DRAWABLE_H
