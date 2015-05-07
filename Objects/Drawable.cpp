#include "Drawable.h"

Drawable::Drawable() {
    d_position = new Position(0, 0);
    d_size = new SizeF(0.0f, 0.0f);
    d_scaledsize = new SizeF(0.0f, 0.0f);
    d_scale = new SizeF(1.0f, 1.0f);
}

Drawable::~Drawable() {
    delete d_size;
    delete d_position;
    delete d_scaledsize;
    delete d_scale;
}

void Drawable::SetScale(SizeF *scale) {
    d_scale = scale;
    d_scaledsize = new SizeF(d_size->width * scale->width,
                            d_size->width * scale->height);
}
