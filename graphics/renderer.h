class Renderer;

#ifndef HEADACHE_RENDERER_H
#define HEADACHE_RENDERER_H

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <list>
#include <algorithm>
#include "game.h"
#include "objects/text.h"
#include "objects/textured_quad.h"
#include "graphics/Layers/layer.h"
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

  enum BufferType {
    STATIC,
    DYNAMIC
  };

  void SetUpCamera();

  LPDIRECT3DVERTEXBUFFER9 GenerateVertexBuffer(BufferType type, std::list<Drawable *> &list);

  void Draw(Drawable *drawable, UINT &index);
  void Draw(Complex *complex_obj, UINT &index, bool parent_visible);
  void GenerateVertices(v_3ct *vertices, UINT &index, Drawable* obj);

 public:
  color color_ = {72, 31, 39};

  Renderer();

  void DrawScene(std::shared_ptr<Scene> scene);
};


#endif //HEADACHE_RENDERER_H
