#include "Drawable.h"

Drawable::Drawable() {
    d_position = new Position(0,0);
    d_size = new Size(0,0);
}

Drawable::~Drawable() {
    delete d_size;
    delete d_position;
}
