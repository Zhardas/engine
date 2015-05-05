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
    bool loaded = false;
    Game* p_game;
protected:
    std::list<TexturedQuad*>* backgroundDrawableList;
    std::list<TexturedQuad*>* dynamicDrawableList;
    std::list<TexturedQuad*>* uiDrawableList;
public:
    Scene(Game* p_game);
    void Update();
    std::list<TexturedQuad*>* GetBackgroundDrawables(){return backgroundDrawableList;};
    std::list<TexturedQuad*>* GetDynamicDrawables(){return dynamicDrawableList;};
    std::list<TexturedQuad*>* GetUIDrawables(){return uiDrawableList;};
    void DoEvnt(Event event, uint8_t key, Position* parameter);
};


#endif //HEADACHE_SCENE_H
