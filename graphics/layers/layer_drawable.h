class DrawableLayer;

#ifndef PLAYGROUND_DYNAMICLAYER_H
#define PLAYGROUND_DYNAMICLAYER_H

#include <d3d9.h>
#include <algorithm>
#include "layer.h"
#include "objects/textured_quad.h"

class DrawableLayer : public Layer {
private:
    Type type_;
public:
    DrawableLayer(Type type);

    bool reload = true;
    std::list<TexturedQuad *> drawable_list_;
    LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;

    Type GetType() {
        return type_;
    }

    void Add(TexturedQuad *obj) {
        drawable_list_.push_back(obj);
        reload = true;
    }

    void Remove(TexturedQuad *obj) {
        drawable_list_.remove(obj);
    }

    bool EventCall(Event event, unsigned char key, Position *parameter);
};

#endif //PLAYGROUND_DYNAMICLAYER_H
