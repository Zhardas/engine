#include "Scene.h"

Scene::Scene(Renderer* p_renderer) {
    this->p_renderer = p_renderer;
    backgroundDrawableList = new std::list<TexturedQuad *>();
    dynamicDrawableList = new std::list<TexturedQuad*>();
    uiDrawableList = new std::list<TexturedQuad *>();


    TexturedQuad * t = new TexturedQuad();
    t->set_position(new Position(0.0f, 0.0f));
    t->set_size(new Size(10.0f, 10.0f));
    t->SetTexture("default.png");

    TexturedQuad * t2 = new TexturedQuad();
    t2->set_position(new Position(10.0f, 0.0f));
    t2->set_size(new Size(10.0f, 10.f));
    t2->SetTexture("default.png");

    TexturedQuad * t3 = new TexturedQuad();
    t3->set_position(new Position(10.0f, -10.0f));
    t3->set_size(new Size(10.0f, 10.0f));
    t3->SetTexture("default.png");

    TexturedQuad * t4 = new TexturedQuad();
    t4->set_position(new Position(0.0f, -10.0f));
    t4->set_size(new Size(10.0f, 10.0f));
    t4->SetTexture("default.png");

    TexturedQuad * t5 = new TexturedQuad();
    t5->set_position(new Position(-10.0f, 0.0f));
    t5->set_size(new Size(10.0f, 10.0f));
    t5->SetTexture("default.png");


    //backgroundDrawableList->push_back(t);
    backgroundDrawableList->push_back(t2);
    backgroundDrawableList->push_back(t3);
    backgroundDrawableList->push_back(t4);
    backgroundDrawableList->push_back(t5);
    uiDrawableList->push_back(t);
    dynamicDrawableList->push_back(t);
}

void Scene::Update(){
    if(!loaded){
        p_renderer->Reload();
        loaded = true;
    }
    //for (std::list<TexturedQuad*>::iterator it=backgroundDrawableList.begin(); it !=backgroundDrawableList.end() ; ++it){
    //
    //}
}