class Renderer;

#ifndef HEADACHE_RENDERER_H
#define HEADACHE_RENDERER_H

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#define D3D_DEBUG_INFO
#include <list>
#include <algorithm>
#include "game.h"
#include "objects/textured_quad.h"
#include "graphics/Layers/layer.h"
#include "graphics/Layers/layer_drawable.h"
#include "graphics/Layers/layer_text.h"
#include "scene/scene.h"

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
    struct v_3ct {
        float x, y, z;
        DWORD color;
        // tu and tv. They represent the
        // orientation of the texture. Hence, we can control where the upper-left and lower-right is.

        // A value of 0.0 is furthest left, or up. 1.0 is furthest right, or down. Hence, from 0.0 to
        // 1.0 is a complete drawing of the texture. You can even specify 2.0, which will draw the
        // texture twice.
        float tu, tv;
    };
    struct color {
        byte r, g, b;
    };

    void SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device);

    LPDIRECT3DVERTEXBUFFER9 GenerateStaticVertexBuffer(std::list<TexturedQuad *> *pList);

    LPDIRECT3DVERTEXBUFFER9 GenerateDynamicVertexBuffer(std::list<TexturedQuad *> *pList);

    void Draw(TexturedQuad *quad, UINT index);

public:
    color color_ = {72, 31, 39};

    Renderer();

    void DrawScene(Scene *scene);
};


#endif //HEADACHE_RENDERER_H
