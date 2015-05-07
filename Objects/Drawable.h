class Drawable;

#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <Helper/types.h>

class Drawable {
private:
protected:
    SizeF *d_size;
    SizeF *d_scaledsize;
    Position *d_position;
    SizeF *d_scale;
public:
    Drawable();

    virtual ~Drawable();

    virtual SizeF *GetSize() = 0;

    virtual void SetSize(SizeF * /* new GetSize */) = 0;

    virtual Position *GetPosition() = 0;

    virtual void SetPosition(Position * /* new GetPosition */) = 0;

    virtual void SetPosition(float x, float y) = 0;

    virtual SizeF *GetScale() { return d_scale; }

    virtual void SetScale(SizeF *scale);

    virtual SizeF *GetScaledSize() { return d_scaledsize; }


};


#endif //HEADACHE_DRAWABLE_H
