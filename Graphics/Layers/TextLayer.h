class TextLayer;

#ifndef PLAYGROUND_TEXTLAYER_H
#define PLAYGROUND_TEXTLAYER_H

#include <Objects/Text.h>
#include "Layer.h"

class TextLayer : public Layer {
private:
public:
    TextLayer();

    std::list<Text *> *text_list;

    Type GetType() {
        return Type::TEXT;
    }

    void Add(Text *text) {
        text_list->push_back(text);
    }
    void Remove(Text * text){
        text_list->remove(text);
    }

    virtual void EventCall(Event event, unsigned char key, Position *parameter){

    };
};


#endif //PLAYGROUND_TEXTLAYER_H
