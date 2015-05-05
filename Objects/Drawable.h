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
    virtual Size GetSize() = 0;
    virtual void SetSize(Size * /* new GetSize */) = 0;
    virtual Position GetPosition() = 0;
    virtual void SetPosition(Position * /* new GetPosition */) = 0;
};


#endif //HEADACHE_DRAWABLE_H
