class Drawable;

#ifndef HEADACHE_DRAWABLE_H
#define HEADACHE_DRAWABLE_H

#include <Helper/types.h>

class Drawable {
private:
protected:
    SizeF d_size = SizeF(32.0f, 32.0f);
    SizeF d_size_scaled = SizeF(32.0f, 32.0f);
    Position d_position = Position(0, 0);
    SizeF d_scale = SizeF(1.0f, 1.0f);
    float d_rotation = 0.0f;
public:
    Drawable();

    virtual SizeF GetSize() = 0;

    virtual void SetSize(SizeF size) = 0;

    virtual Position GetPosition() = 0;

    virtual void SetPosition(Position position) = 0;

    virtual void SetPosition(float x, float y) = 0;

    virtual SizeF GetScale() { return d_scale; }

    virtual void SetScale(SizeF scale) {
        d_scale.width = scale.width;
        d_scale.height = scale.height;
        d_size_scaled.width = d_size.width * scale.width;
        d_size_scaled.height = d_size.width * scale.height;

    }

    virtual SizeF GetScaledSize() { return d_size_scaled; }

    virtual void SetRotation(float rot) {
        d_rotation = rot;
    }

    virtual float GetRotation() {
        return d_rotation;
    }

    virtual bool Contains(Position pos) {
        return pos.x >= GetPosition().x - d_size_scaled.width / 2 &&
               pos.x <= GetPosition().x + d_size_scaled.width / 2 &&
               pos.y >= GetPosition().y - d_size_scaled.height / 2 &&
               pos.y <= GetPosition().y + d_size_scaled.height / 2;
    }
};


#endif //HEADACHE_DRAWABLE_H
