class text_layer;

#ifndef PLAYGROUND_TEXTLAYER_H
#define PLAYGROUND_TEXTLAYER_H

#include "objects/text.h"
#include "layer.h"

class text_layer: public Layer {
private:
public:
    text_layer();

    std::list<Text *> *text_list_;

    Type GetType() {
        return Type::TEXT;
    }

    void Add(Text *text) {
        text_list_->push_back(text);
    }
    void Remove(Text * text){
        text_list_->remove(text);
    }

    virtual bool EventCall(Event event, unsigned char key, Position *parameter){
        // TODO: text events
        return false;
    };
};


#endif //PLAYGROUND_TEXTLAYER_H