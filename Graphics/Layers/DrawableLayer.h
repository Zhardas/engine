class DrawableLayer;

#ifndef PLAYGROUND_DYNAMICLAYER_H
#define PLAYGROUND_DYNAMICLAYER_H

#include "Layer.h"
#include <algorithm>
#include <Objects/TexturedQuad.h>

class DrawableLayer : public Layer {
private:
    Type type;
public:
    DrawableLayer(Type type);

    bool reload = true;
    std::list<TexturedQuad *> *drawableList;
    LPDIRECT3DVERTEXBUFFER9 vertex_buffer;

    Type GetType() {
        return type;
    }

    void Add(TexturedQuad *obj) {
        drawableList->push_back(obj);
        reload = true;
    }

    void Remove(TexturedQuad *obj) {
        drawableList->remove(obj);
    }

    bool EventCall(Event event, unsigned char key, Position *parameter);
};

#endif //PLAYGROUND_DYNAMICLAYER_H
