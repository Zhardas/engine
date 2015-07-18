#include "DrawableLayer.h"

DrawableLayer::DrawableLayer(Type type) {
    this->type = type;
    drawableList = new std::list<TexturedQuad *>();
    vertex_buffer = NULL;
}

void DrawableLayer::EventCall(Event event, unsigned char key, Position *parameter) {
    if (event == MOUSE_UP) {
        for_each(drawableList->begin(), drawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseUp != NULL)obj->OnMouseUp(key, parameter);
        });
    } else if (event == MOUSE_DOWN) {
        for_each(drawableList->begin(), drawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseDown != NULL)obj->OnMouseDown(key, parameter);
        });
    } else if (event == MOUSE_MOVE) {
        for_each(drawableList->begin(), drawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseMove != NULL)obj->OnMouseMove(parameter);
        });
    } else if (event == KEYBOARD_UP) {
        for_each(drawableList->begin(), drawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyUp != NULL)obj->OnKeyUp(key);
        });
    } else if (event == KEYBOARD_DOWN) {
        for_each(drawableList->begin(), drawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyDown != NULL)obj->OnKeyDown(key);
        });
    }
}