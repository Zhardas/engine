class Scene;

#ifndef HEADACHE_SCENE_H
#define HEADACHE_SCENE_H

#include <Objects/TexturedQuad.h>
#include <Graphics/Renderer.h>
#include <Game.h>
#include <list>
#include <Helper/input.h>
#include <algorithm>

class Scene {
private:
    bool loaded;
    Game *g_game;
    std::list<TexturedQuad *> *backgroundDrawableList;
    std::list<TexturedQuad *> *dynamicDrawableList;
    std::list<TexturedQuad *> *uiDrawableList;
protected:
    enum layer_enum {
        BACKGROUND, DYNAMIC, UI
    };

    void AddTexQuad(layer_enum layer, TexturedQuad *obj);

public:
    Scene();

    virtual ~Scene();

    virtual void Update();

    std::list<TexturedQuad *> *GetBackgroundDrawables() { return backgroundDrawableList; }

    std::list<TexturedQuad *> *GetDynamicDrawables() { return dynamicDrawableList; }

    std::list<TexturedQuad *> *GetUIDrawables() { return uiDrawableList; }

    void DoEvnt(Event event, uint8_t key, Position *parameter);
};


#endif //HEADACHE_SCENE_H
