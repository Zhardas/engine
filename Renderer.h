class Renderer;
#ifndef HEADACHE_RENDERER_H
#define HEADACHE_RENDERER_H

#include <windows.h>
#include<d3dx9.h>
#include<d3d9.h>
#include "Game.h"


class Renderer {
    struct v_3c {
        float x, y, z;
        DWORD color;
    };

    Game* p_Game;
    LPDIRECT3DVERTEXBUFFER9 p_dx_VB;
    LPDIRECT3DINDEXBUFFER9 p_dx_IB;

    void DrawScene(LPDIRECT3DDEVICE9 p_dx_Device, LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer,
                   LPDIRECT3DINDEXBUFFER9 p_dx_IndexBuffer);

    LPDIRECT3DVERTEXBUFFER9 FillVertices(LPDIRECT3DDEVICE9 p_dx_Device);

    LPDIRECT3DINDEXBUFFER9 FillIndices(LPDIRECT3DDEVICE9 p_dx_Device);

    void SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device);

public:
    Renderer(Game* p_Game);

    void Draw();
};


#endif //HEADACHE_RENDERER_H
