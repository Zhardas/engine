class Drawable;
#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <Helper/types.h>

class Drawable {
private:
protected:
    Size* d_size;
    Position* d_position;
public:
    Drawable();
    virtual ~Drawable();
    virtual Size* GetSize() = 0;
    virtual void SetSize(Size * /* new GetSize */) = 0;
    virtual Position* GetPosition() = 0;
    virtual void SetPosition(Position * /* new GetPosition */) = 0;
    virtual void SetPosition(int x, int y) = 0;
};


#endif //HEADACHE_DRAWABLE_H
