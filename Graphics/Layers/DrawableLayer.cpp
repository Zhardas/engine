#include "DrawableLayer.h"

DrawableLayer::DrawableLayer(Type type) {
    this->type = type;
    drawableList = new std::list<TexturedQuad *>();
    vertex_buffer = NULL;
}

bool DrawableLayer::EventCall(Event event, unsigned char key, Position *parameter) {
    for (std::list<TexturedQuad *>::reverse_iterator rit = drawableList->rbegin(); rit != drawableList->rend(); ++rit) {
        auto obj = static_cast<TexturedQuad *>(*rit);
        switch (event) {
            case MOUSE_UP: {
                if (obj->OnMouseUp != NULL) {
                    if (obj->OnMouseUp(key, parameter)) {
                        return true;
                    }
                }
            }
                break;
            case MOUSE_DOWN: {
                if (obj->OnMouseDown != NULL) {
                    if (obj->OnMouseDown(key, parameter)) {
                        return true;
                    }
                }
            }
                break;
            case MOUSE_MOVE: {
                if (obj->OnMouseMove != NULL) {
                    if (obj->OnMouseMove(parameter)) {
                        return true;
                    }
                }
            }
                break;
            case KEYBOARD_UP: {
                if (obj->OnKeyUp != NULL) {
                    if (obj->OnKeyUp(key)) {
                        return true;
                    }
                }
            }
                break;
            case KEYBOARD_DOWN: {
                if (obj->OnKeyDown != NULL) {
                    if (obj->OnKeyDown(key)) {
                        return true;
                    }
                }
            }
                break;
        }
    }
    return false;
}