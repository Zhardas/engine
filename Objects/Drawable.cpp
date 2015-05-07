#include "Drawable.h"

Drawable::Drawable() {
    d_position = new Position(0, 0);
    d_size = new Size(0, 0);
    d_scaledsize = new Size(0, 0);
    d_scale = new SizeF(1, 1);
}

Drawable::~Drawable() {
    delete d_size;
    delete d_position;
    delete d_scaledsize;
    delete d_scale;
}

void Drawable::SetScale(SizeF *scale) {
    d_scale = scale;
    d_scaledsize = new Size(static_cast<int>(d_size->width * scale->width),
                            static_cast<int>(d_size->width * scale->height));
}
