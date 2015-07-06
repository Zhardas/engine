#include <Helper/input.h>
#include <iostream>
#include "Scene.h"

Scene::Scene() {
    g_game = Game::GetInstance();
    backgroundDrawableList = new std::list<TexturedQuad *>();
    dynamicDrawableList = new std::list<TexturedQuad *>();
    uiDrawableList = new std::list<TexturedQuad *>();
    textList = new std::list<Text *>();
}

Scene::~Scene() {
    while (!backgroundDrawableList->empty()) delete backgroundDrawableList->front(), backgroundDrawableList->pop_front();
    while (!dynamicDrawableList->empty()) delete dynamicDrawableList->front(), dynamicDrawableList->pop_front();
    while (!uiDrawableList->empty()) delete uiDrawableList->front(), uiDrawableList->pop_front();
}

void Scene::Update() {
    if (!loaded) {
        g_game->g_renderer->Reload();
        loaded = true;
    }
}

void Scene::DoEvnt(Event event, uint8_t key, Position *parameter) {
    if (event == MOUSE_UP) {
        for_each(uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseUp != NULL)obj->OnMouseUp(key, parameter);
        });
        for_each(dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseUp != NULL)obj->OnMouseUp(key, parameter);
        });
        for_each(backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseUp != NULL)obj->OnMouseUp(key, parameter);
        });
        return;
    };
    if (event == MOUSE_DOWN) {
        for_each(uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseDown != NULL)obj->OnMouseDown(key, parameter);
        });
        for_each(dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseDown != NULL)obj->OnMouseDown(key, parameter);
        });
        for_each(backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseDown != NULL)obj->OnMouseDown(key, parameter);
        });
        return;
    }
    if (event == MOUSE_MOVE) {
        for_each(uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseMove != NULL)obj->OnMouseMove(parameter);
        });
        for_each(dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseMove != NULL)obj->OnMouseMove(parameter);
        });
        for_each(backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnMouseMove != NULL)obj->OnMouseMove(parameter);
        });
    } else if (event == KEYBOARD_UP) {
        for_each(uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyUp != NULL)obj->OnKeyUp(key);
        });
        for_each(dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyUp != NULL)obj->OnKeyUp(key);
        });
        for_each(backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyUp != NULL)obj->OnKeyUp(key);
        });
    } else if (event == KEYBOARD_DOWN) {
        for_each(uiDrawableList->begin(), uiDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyDown != NULL)obj->OnKeyDown(key);
        });
        for_each(dynamicDrawableList->begin(), dynamicDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyDown != NULL)obj->OnKeyDown(key);
        });
        for_each(backgroundDrawableList->begin(), backgroundDrawableList->end(), [&](TexturedQuad *obj) {
            if (obj->OnKeyDown != NULL)obj->OnKeyDown(key);
        });
    }
}

void Scene::AddTexQuad(Scene::layer_enum layer, TexturedQuad *obj) {
    switch (layer) {
        case BACKGROUND: {
            backgroundDrawableList->push_back(obj);
            loaded = false;
            return;
        };
        case DYNAMIC: {
            dynamicDrawableList->push_back(obj);
            return;
        };
        case UI: {
            uiDrawableList->push_back(obj);
            loaded = false;
            return;
        };
    }
}

void Scene::RemoveTexQuad(Scene::layer_enum layer, TexturedQuad *obj) {
    switch (layer) {
        case BACKGROUND: {
            backgroundDrawableList->remove(obj);
            return;
        };
        case DYNAMIC: {
            dynamicDrawableList->remove(obj);
            return;
        };
        case UI: {
            uiDrawableList->remove(obj);
            return;
        };
    }
}

void Scene::AddText(Text *obj) {
    textList->push_back(obj);
}
void Scene::RemoveText(Text *obj) {
    textList->remove(obj);
}
