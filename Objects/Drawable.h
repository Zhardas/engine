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
    float d_rotation;
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

    virtual void SetRotation(float rot){
        d_rotation = rot;
    }

    virtual float GetRotation(){
        return d_rotation;
    }

    virtual bool Contains(Position *pos) {
        return pos->x >= GetPosition()->x - GetScaledSize()->width / 2 &&
               pos->x <= GetPosition()->x + GetScaledSize()->width / 2 &&
               pos->y >= GetPosition()->y - GetScaledSize()->height / 2 &&
               pos->y <= GetPosition()->y + GetScaledSize()->height / 2;
    }
};


#endif //HEADACHE_DRAWABLE_H
