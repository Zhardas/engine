#include <objects/text.h>
#include "renderer.h"

Renderer::Renderer() {
  SetUpCamera(Game::instance()->device_);
}

void Renderer::SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device) {
  D3DXMATRIX matOrtho;
  D3DXMATRIX matIdentity;

  D3DXMatrixOrthoLH(&matOrtho, Game::instance()->width(), Game::instance()->height(), 0.0f, 1.0f);
  D3DXMatrixIdentity(&matIdentity);

  p_dx_Device->SetTransform(D3DTS_PROJECTION, &matOrtho);
  p_dx_Device->SetTransform(D3DTS_WORLD, &matIdentity);
  p_dx_Device->SetTransform(D3DTS_VIEW, &matIdentity);
}


void Renderer::DrawScene(Scene *scene) {
  LPDIRECT3DDEVICE9 device = Game::instance()->device_;
  device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, color_.r, color_.g, color_.b), 1.0f, 0);
  device->BeginScene();

  // Move camera
  auto cam_pos = scene->camera_->position_;
  D3DXMATRIX view_matrix;
  D3DXMatrixIdentity(&view_matrix);
  view_matrix(3, 0) = -cam_pos.x;
  view_matrix(3, 1) = -cam_pos.y;
  view_matrix(3, 2) = cam_pos.z; // TODO: ???
  device->SetTransform(D3DTS_VIEW, &view_matrix);

  for (Layer *layer : *scene->GetLayers()) {
    UINT index = 0;

    // Generate Vertex Buffer
    switch (layer->type()) {
      case Layer::STATIC: {
        if (layer->reload) {
          layer->reload = false;
          if (layer->vertex_buffer_ != NULL) {
            layer->vertex_buffer_->Release();
          }
          layer->vertex_buffer_ = GenerateStaticVertexBuffer(layer->drawable_list_);
        }
        break;
      }
      case Layer::DYNAMIC: {
        layer->vertex_buffer_ = GenerateDynamicVertexBuffer(layer->drawable_list_);
        break;
      }
    }

    // Setup and draw
    if (layer->vertex_buffer_ != NULL) {
      Game::instance()->device_->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
      Game::instance()->device_->SetStreamSource(0, layer->vertex_buffer_, 0, sizeof(v_3ct));

      for (auto *obj : layer->drawable_list_) {
        // World transformation
        D3DXVECTOR2 pivot = {obj->size().width / 2, obj->size().height / 2};
        D3DXVECTOR2 scaling = {obj->scale().width, obj->scale().height};
        D3DXVECTOR2 moving = {obj->position().x - Game::instance()->width() / 2,
                              obj->position().y - Game::instance()->height() / 2};
        D3DXMATRIX matFinal;
        D3DXMatrixTransformation2D(&matFinal, &pivot, 1.0f, &scaling, &pivot, obj->rotation(),
                                   &moving);

        device->SetTransform(D3DTS_WORLD, &matFinal);

        // Draw
        Draw(obj, index);

        // Reset world transformation
        D3DXMatrixIdentity(&matFinal);
        device->SetTransform(D3DTS_WORLD, &matFinal);
      }
    }

    // Release dynamic buffers
    if (layer->type() == Layer::DYNAMIC) {
      layer->vertex_buffer_->Release();
      delete layer->vertex_buffer_;
      layer->vertex_buffer_ = NULL;
    }
  }

  device->EndScene();
  device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateStaticVertexBuffer(std::list<Drawable *> &list) {
  if (list.size() <= 0) {
    return NULL;
  }
  LPDIRECT3DVERTEXBUFFER9 vertex_buffer = nullptr;
  UINT index = 0;

  v_3ct vertices[4 * list.size()];  // TODO: Allocates too much memory if list contains Text objects.
  for (Drawable *obj : list) {
    if(auto textured_quad = dynamic_cast<TexturedQuad*>(obj)){
      vertices[index * 4] = {0.0f, 0.0f, 0.0f, textured_quad->color(), 0.0f, 1.0f};
      vertices[index * 4 + 1] = {0.0f, textured_quad->size().height, 0.0f, textured_quad->color(), 0.0f, 0.0f};
      vertices[index * 4 + 2] = {textured_quad->size().width, 0.0f, 0.0f, textured_quad->color(), 1.0f, 1.0f};
      vertices[index * 4 + 3] = {textured_quad->size().width, textured_quad->size().height, 0.0f, textured_quad->color(), 1.0f, 0.0f};
      index++;
    }
  }
  if (FAILED(Game::instance()->device_->CreateVertexBuffer(4 * index * sizeof(v_3ct), D3DUSAGE_WRITEONLY,
                                                           D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
                                                           D3DPOOL_DEFAULT, &vertex_buffer, NULL))) {
    //TODO: Error handling
  }

  VOID *temp_vertices;
  if (FAILED(vertex_buffer->Lock(0, 4 * index * sizeof(v_3ct), &temp_vertices, 0))) {
    //TODO: Error handling
  } else {
    memcpy(temp_vertices, vertices, 4 * index * sizeof(v_3ct));
    vertex_buffer->Unlock();
  }
  return vertex_buffer;
}

void Renderer::Draw(Drawable *drawable, UINT &index) {
  if (auto obj = dynamic_cast<TexturedQuad *>(drawable)) {
    if (!drawable->visible_)return;
    Game::instance()->device_->SetTexture(0, Game::instance()->texture_manager_->LoadTexture(obj->texture().c_str()));
    Game::instance()->device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * index, 2);
    index++;
  } else if (auto text = dynamic_cast<Text *>(drawable)) {
    if (!drawable->visible_)return;
    RECT rect = {(LONG) text->position().x, (LONG) text->position().y,
                 (LONG) (text->position().x + text->size().width),
                 (LONG) (text->position().y + text->size().height)};
    text->font_->font()->DrawText(NULL,
                                  text->text().c_str(), -1,
                                  &rect,
                                  DT_CENTER,
                                  D3DCOLOR_ARGB(text->color_alpha_, text->color_red_,
                                                text->color_green_,
                                                text->color_blue_));
  }
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateDynamicVertexBuffer(std::list<Drawable *> &list) {
  if (list.size() <= 0) {
    return NULL;
  }
  LPDIRECT3DVERTEXBUFFER9 vertex_buffer = nullptr;
  UINT index = 0;

  v_3ct vertices[4 * list.size()];  // TODO: Allocates too much memory if list contains Text objects.
  for (Drawable *obj : list) {
    if(auto textured_quad = dynamic_cast<TexturedQuad*>(obj)) {
      vertices[index * 4] = {0.0f, 0.0f, 0.0f, textured_quad->color(), 0.0f, 1.0f};
      vertices[index * 4 + 1] = {0.0f, textured_quad->size().height, 0.0f, textured_quad->color(), 0.0f, 0.0f};
      vertices[index * 4 + 2] = {textured_quad->size().width, 0.0f, 0.0f, textured_quad->color(), 1.0f, 1.0f};
      vertices[index * 4 + 3] = {textured_quad->size().width, textured_quad->size().height, 0.0f, textured_quad->color(), 1.0f,
                                 0.0f};
      index++;
    }
  }
  if (FAILED(Game::instance()->device_->CreateVertexBuffer(4 * index * sizeof(v_3ct),
                                                           D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                                           D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
                                                           D3DPOOL_DEFAULT,
                                                           &vertex_buffer,
                                                           NULL))) {
    //TODO: Error handling
  }

  VOID *temp_vertices;
  if (FAILED(vertex_buffer->Lock(0, 4 * index * sizeof(v_3ct), &temp_vertices, D3DLOCK_DISCARD))) {
    //TODO: Error handling
  } else {
    memcpy(temp_vertices, vertices, 4 * index * sizeof(v_3ct));
    vertex_buffer->Unlock();
  }
  return vertex_buffer;
}
