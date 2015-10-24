#include "renderer.h"

Renderer::Renderer() {
  SetUpCamera();
}

void Renderer::SetUpCamera() {
  D3DXMATRIX matOrtho;
  D3DXMATRIX matIdentity;

  D3DXMatrixOrthoLH(&matOrtho, Game::instance()->width(), Game::instance()->height(), 0.0f, 1.0f);
  D3DXMatrixIdentity(&matIdentity);

  Game::instance()->device_->SetTransform(D3DTS_PROJECTION, &matOrtho);
  Game::instance()->device_->SetTransform(D3DTS_WORLD, &matIdentity);
  Game::instance()->device_->SetTransform(D3DTS_VIEW, &matIdentity);
}


void Renderer::DrawScene(std::shared_ptr<Scene> scene) {
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

  for (auto layer : *scene->GetLayers()) {
    UINT index = 0;

    // Generate Vertex Buffer
    switch (layer->type()) {
      case Layer::STATIC: {
        if (layer->reload_) {
          layer->reload_ = false;
          if (layer->vertex_buffer_ != NULL) {
            layer->vertex_buffer_->Release();
          }
          layer->vertex_buffer_ = GenerateVertexBuffer(STATIC, layer->drawable_list_);
        }
        break;
      }
      case Layer::DYNAMIC: {
        layer->vertex_buffer_ = GenerateVertexBuffer(DYNAMIC, layer->drawable_list_);
        break;
      }
    }

    // Setup and draw
    if (layer->vertex_buffer_ != NULL) {
      Game::instance()->device_->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
      Game::instance()->device_->SetStreamSource(0, layer->vertex_buffer_, 0, sizeof(v_3ct));

      for (auto obj : layer->drawable_list_) {
        if (auto complex_obj = dynamic_cast<Complex *>(obj)) {
          Draw(complex_obj, index, true);
        } else {
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
    }

    // Release dynamic buffers
    if (layer->type() == Layer::DYNAMIC && layer->vertex_buffer_ != nullptr) {
      layer->vertex_buffer_->Release();
      layer->vertex_buffer_ = NULL;
    }
  }

  device->EndScene();
  device->Present(NULL, NULL, NULL, NULL);
}

void Renderer::Draw(Complex* complex_obj, UINT &index, bool parent_visible){
  auto device = Game::instance()->device_;
  if(!(complex_obj->visible() && parent_visible)){
    for (auto drawable_obj : complex_obj->complex_list_) {
      if(auto obj = dynamic_cast<Complex*>(drawable_obj)){
        Draw(obj, index, (complex_obj->visible() && parent_visible));
      }
      else if (dynamic_cast<TexturedQuad *>(drawable_obj)) {
        index++;
      }
    }
    return;
  }
  for (auto drawable_obj : complex_obj->complex_list_) {
    if(auto complex = dynamic_cast<Complex*>(drawable_obj)){
      Draw(complex, index, true);
      continue;
    }
    // World transformation
    D3DXVECTOR2 pivot = {drawable_obj->size().width / 2, drawable_obj->size().height / 2};
    D3DXVECTOR2 scaling = {drawable_obj->scale().width, drawable_obj->scale().height};
    D3DXVECTOR2 moving = {drawable_obj->position().x - Game::instance()->width() / 2,
                          drawable_obj->position().y - Game::instance()->height() / 2};
    D3DXMATRIX matFinal;
    D3DXMatrixTransformation2D(&matFinal, &pivot, 1.0f, &scaling, &pivot, drawable_obj->rotation(),
                               &moving);

    device->SetTransform(D3DTS_WORLD, &matFinal);

    // Draw
    Draw(drawable_obj, index);


    // Reset world transformation
    D3DXMatrixIdentity(&matFinal);
    device->SetTransform(D3DTS_WORLD, &matFinal);
  }
}

uint32_t GetComplexVBObjectCount(Complex* obj){
  uint32_t count = 0;
  for(auto drawable : obj->complex_list_){
    if(auto complex = dynamic_cast<Complex*>(drawable)){
      count += GetComplexVBObjectCount(complex);
    }else if(dynamic_cast<TexturedQuad*>(drawable)){
      count++;
    }
  }
  return count;
}

void Renderer::Draw(Drawable *drawable, UINT &index) {
  if (auto obj = dynamic_cast<TexturedQuad *>(drawable)) {
    if (!drawable->visible()) {
      index++;
      return;
    }
    Game::instance()->device_->SetTexture(0, Game::instance()->texture_manager_->LoadTexture(obj->texture().c_str()));
    Game::instance()->device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * index, 2);
    index++;
  } else if (auto text = dynamic_cast<Text *>(drawable)) {
    if (!drawable->visible())return;
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

void Renderer::GenerateVertices(v_3ct *vertices, UINT &index, Drawable* obj){
  if (auto complex_obj = dynamic_cast<Complex *>(obj)) {
    for (auto drawable : complex_obj->complex_list_) {
      GenerateVertices(vertices, index, drawable);
    }
  } else if (auto textured_quad = dynamic_cast<TexturedQuad *>(obj)) {
    vertices[index * 4] = {0.0f, 0.0f, 0.0f, textured_quad->color(), 0.0f, 1.0f};
    vertices[index * 4 + 1] = {0.0f, textured_quad->size().height, 0.0f, textured_quad->color(), 0.0f, 0.0f};
    vertices[index * 4 + 2] = {textured_quad->size().width, 0.0f, 0.0f, textured_quad->color(), 1.0f, 1.0f};
    vertices[index * 4 + 3] =
        {textured_quad->size().width, textured_quad->size().height, 0.0f, textured_quad->color(), 1.0f, 0.0f};
    index++;
  }
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateVertexBuffer(Renderer::BufferType type, std::list<Drawable *> &list) {
  if (list.size() <= 0) {
    return NULL;
  }
  LPDIRECT3DVERTEXBUFFER9 vertex_buffer = nullptr;
  UINT object_count = 0;
  UINT index = 0;

  for (auto obj : list) {
    if (auto complex_obj = dynamic_cast<Complex *>(obj)) {
      object_count += GetComplexVBObjectCount(complex_obj);
    } else if (dynamic_cast<TexturedQuad*>(obj)){
      object_count++;
    }
  }

  v_3ct vertices[4 * object_count];
  for (Drawable *obj : list) {
    GenerateVertices(vertices,index, obj);
  }
  if(type == DYNAMIC){
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
  }else{
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
  }
  return vertex_buffer;
}
