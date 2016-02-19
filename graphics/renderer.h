class Renderer;

#ifndef GRAPHICS_RENDERER_H_
#define GRAPHICS_RENDERER_H_

#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <list>
#include <algorithm>
#include "game.h"
#include "texture_manager.h"
//#include "objects/text.h"
//#include "objects/textured_quad.h"
#include "graphics/layers/layer.h"
#include "scene/scene.h"

class Renderer {
 public:
  // TODO(Zhardas): Make use of these avaliable vertex structures.
  struct v_3c {
    float x, y, z;
    DWORD color;
  };
  struct v_3 {
    float x, y, z;
  };
  struct v_3t {
    float x, y, z;
    float tu, tv;
  };
  struct color {
    byte r, g, b;
  };
  enum BufferType {
    STATIC,
    DYNAMIC
  };

 private:
  std::unique_ptr<TextureManager> texture_manager_;
  LPDIRECT3DDEVICE9 device_;

  void SetUpCamera();
  LPDIRECT3DVERTEXBUFFER9 GenerateVertexBuffer(BufferType type, std::list<std::unique_ptr<Drawable>> *list);
  void DrawComplex(Drawable* complex_obj, UINT &index, bool parent_visible);
  void GenerateVertices(v_3ct *vertices, uint32_t *index, Drawable* obj);
  uint32_t GetComplexVBObjectCount(Drawable* obj);

 public:

  // Clear color.
  color color_ = {72, 31, 39};
  Renderer(LPDIRECT3DDEVICE9 device);

  void DrawScene(std::shared_ptr<Scene> scene);
  void DrawTexture(uint32_t *index, std::string texture);
};


#endif // GRAPHICS_RENDERER_H_
