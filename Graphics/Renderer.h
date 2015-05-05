class Renderer;

#ifndef HEADACHE_RENDERER_H
#define HEADACHE_RENDERER_H

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <Scene/Scene.h>
#include <Objects/TexturedQuad.h>
#include <Game.h>
#include <list>

class Renderer {
    struct v_3c {
        float x, y, z;
        DWORD color;
    };
    struct v_3 {
        float x, y, z;
    };
    struct v_3t {
        float x, y, z;

        // tu and tv. They represent the
        // orientation of the texture. Hence, we can control where the upper-left and lower-right is.

        // A value of 0.0 is furthest left, or up. 1.0 is furthest right, or down. Hence, from 0.0 to
        // 1.0 is a complete drawing of the texture. You can even specify 2.0, which will draw the
        // texture twice.
        float tu, tv;
    };

    Game* p_Game;
    LPDIRECT3DVERTEXBUFFER9 vb_static_background;
    LPDIRECT3DVERTEXBUFFER9 vb_static_ui;
    LPDIRECT3DVERTEXBUFFER9 vb_dynamic;


    void SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device);

    LPDIRECT3DVERTEXBUFFER9 GenerateStaticVertexBuffer(std::list<TexturedQuad *> *pList);
    LPDIRECT3DVERTEXBUFFER9 GenerateDynamicVertexBuffer(std::list<TexturedQuad *> *pList);
    void Draw(TexturedQuad *pQuad, UINT index);

public:
    Renderer(Game *p_game);

    void DrawScene(Scene* scene);

    void Reload();


};


#endif //HEADACHE_RENDERER_H