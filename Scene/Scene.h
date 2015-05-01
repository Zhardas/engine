class Scene;
#ifndef HEADACHE_SCENE_H
#define HEADACHE_SCENE_H

#include <Objects/TexturedQuad.h>
#include <list>
#include <Graphics/Renderer.h>

class Scene {
private:
    bool loaded = false;
    Renderer *p_renderer;
protected:
    std::list<TexturedQuad*>* backgroundDrawableList;
    std::list<TexturedQuad*>* dynamicDrawableList;
    std::list<TexturedQuad*>* uiDrawableList;
public:
    Scene(Renderer* p_renderer);
    void Update();
    std::list<TexturedQuad*>* GetBackgroundDrawables(){return backgroundDrawableList;};
    std::list<TexturedQuad*>* GetDynamicDrawables(){return dynamicDrawableList;};
    std::list<TexturedQuad*>* GetUIDrawables(){return uiDrawableList;};
};


#endif //HEADACHE_SCENE_H
