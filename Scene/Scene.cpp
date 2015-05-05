#include <Helper/input.h>
#include <c++/iostream>
#include "Scene.h"
TexturedQuad * t;
Scene::Scene(Game* p_game) {
    this->p_game = p_game;
    backgroundDrawableList = new std::list<TexturedQuad *>();
    dynamicDrawableList = new std::list<TexturedQuad*>();
    uiDrawableList = new std::list<TexturedQuad *>();


    t = new TexturedQuad();
    t->set_position(new Position(0.0f, 0.0f));
    t->set_size(new Size(10.0f, 10.0f));
    t->SetTexture("default.png");
    t->OnMouseUp = [=](const uint8_t& key, Position* pos){
        switch (key){
            case Z_MOUSELEFT:{
                std::cout << "Left mouse button up at: " << pos->x << "-" << pos->y << "\n";
                t->set_position(new Position(pos->x, pos->y));
                break;
            };
            case Z_MOUSEMIDDLE:{
                std::cout << "MIDDLE MOUSE BUTTON UP! \n";
                break;
            };
            case Z_MOUSERIGHT:{
                std::cout << "RIGHT MOUSE BUTTON UP! \n";
                break;
            };
            default:{
                break;
            }
        }
    };

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
    t4->SetTexture("default2.png");

    TexturedQuad * t5 = new TexturedQuad();
    t5->set_position(new Position(-10.0f, 0.0f));
    t5->set_size(new Size(10.0f, 10.0f));
    t5->SetTexture("default2.png");


    //backgroundDrawableList->push_back(t);
    //backgroundDrawableList->push_back(t2);
    //backgroundDrawableList->push_back(t3);
    //backgroundDrawableList->push_back(t4);
    backgroundDrawableList->push_back(t5);
    uiDrawableList->push_back(t3);
    dynamicDrawableList->push_back(t);
}

void Scene::Update(){
    if(!loaded){
        p_game->p_renderer->Reload();
        loaded = true;
    }
    //t->set_position(p_game->p_input->GetMousePosition());
    //for (std::list<TexturedQuad*>::iterator it=backgroundDrawableList.begin(); it !=backgroundDrawableList.end() ; ++it){
    //
    //}
}

void Scene::DoEvnt(Event event, uint8_t key, Position* parameter) {
    for_each (uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad* obj){
        if(event == MOUSE_UP && obj->OnMouseUp != NULL){
            obj->OnMouseUp(key, parameter);
            return;
        }
        if(event == MOUSE_DOWN && obj->OnMouseDown != NULL){
            obj->OnMouseDown(key, parameter);
            return;
        }
        if(event == KEYBOARD_UP && obj->OnKeyUp != NULL){
            obj->OnKeyUp(key);
        }else if(event == KEYBOARD_DOWN && obj->OnKeyDown != NULL){
            obj->OnKeyDown(key);
        }
    });
    for_each (dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad* obj){
        if(event == MOUSE_UP && obj->OnMouseUp != NULL){
            obj->OnMouseUp(key, parameter);
            return;
        }
        if(event == MOUSE_DOWN && obj->OnMouseDown != NULL){
            obj->OnMouseDown(key, parameter);
            return;
        }
        if(event == KEYBOARD_UP && obj->OnKeyUp != NULL){
            obj->OnKeyUp(key);
        }else if(event == KEYBOARD_DOWN && obj->OnKeyDown != NULL){
            obj->OnKeyDown(key);
        }
    });
    for_each (backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad* obj){
        if(event == MOUSE_UP && obj->OnMouseUp != NULL){
            obj->OnMouseUp(key, parameter);
            return;
        }
        if(event == MOUSE_DOWN && obj->OnMouseDown != NULL){
            obj->OnMouseDown(key, parameter);
            return;
        }
        if(event == KEYBOARD_UP && obj->OnKeyUp != NULL){
            obj->OnKeyUp(key);
        }else if(event == KEYBOARD_DOWN && obj->OnKeyDown != NULL){
            obj->OnKeyDown(key);
        }
    });
}
