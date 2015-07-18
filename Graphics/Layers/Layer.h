class Layer;
#ifndef PLAYGROUND_LAYER_H
#define PLAYGROUND_LAYER_H
#include <Helper/input.h>
#include <Helper/types.h>

class Layer {
private:
public:
    enum Type{
        STATIC = 0,
        DYNAMIC = 1,
        TEXT = 2
    };
    Layer();
    virtual Type GetType() = 0;
    virtual void EventCall(Event event, unsigned char key, Position *parameter) = 0;
};


#endif //PLAYGROUND_LAYER_H