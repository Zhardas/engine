#include "renderer.h"

Renderer::Renderer(LPDIRECT3DDEVICE9 device) {
  device_ = device;

  std::cout << "\nTexture manager initialization: ";
  texture_manager_ = std::make_unique<TextureManager>();
  std::cout << "success!";

  SetUpCamera();
}

void Renderer::SetUpCamera() {
  D3DXMATRIX matOrtho;
  D3DXMATRIX matIdentity;

  D3DXMatrixOrthoLH(&matOrtho, Game::instance()->width(), Game::instance()->height(), 0.0f, 1.0f);
  D3DXMatrixIdentity(&matIdentity);

  device_->SetTransform(D3DTS_PROJECTION, &matOrtho);
  device_->SetTransform(D3DTS_WORLD, &matIdentity);
  device_->SetTransform(D3DTS_VIEW, &matIdentity);
}

// TODO(Zhardas): Make a template for vertex buffer structure.
void Renderer::DrawScene(std::shared_ptr<Scene> scene) {
  LPDIRECT3DDEVICE9 device = device_;
  device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, color_.r, color_.g, color_.b), 1.0f, 0);
  device->BeginScene();

  // Move camera
  auto cam_pos = scene->camera_->position_;
  D3DXMATRIX view_matrix;
  D3DXMatrixIdentity(&view_matrix);
  view_matrix(3, 0) = -cam_pos.x;
  view_matrix(3, 1) = -cam_pos.y;
  view_matrix(3, 2) = cam_pos.z; // TODO(Zhardas): 3D: Check the assigned value.
  device->SetTransform(D3DTS_VIEW, &view_matrix);

  for (auto layer : scene->GetLayers()) {
    // NOTE: Scene has a limit of 256 layers.
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
      device_->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
      device_->SetStreamSource(0, layer->vertex_buffer_, 0, sizeof(v_3ct));

      for (auto obj : layer->drawable_list_) {
        DrawComplex(obj, index, layer->visible_);
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

void Renderer::DrawComplex(std::shared_ptr<Drawable> complex_obj, UINT &index, bool parent_visible) {
  if (!parent_visible) {
    index++;
  } else {
    // World transformation
    D3DXVECTOR2 pivot = {complex_obj->size().width / 2, 0};
    D3DXVECTOR2 scaling = {complex_obj->scale().width, complex_obj->scale().height};
    D3DXVECTOR2 moving = {complex_obj->position().x - Game::instance()->instance()->width() / 2,
                          complex_obj->position().y - Game::instance()->instance()->height() / 2};
    D3DXMATRIX matFinal;
    D3DXMatrixTransformation2D(&matFinal, &pivot, 1.0f, &scaling, &pivot, complex_obj->rotation(),
                               &moving);

    device_->SetTransform(D3DTS_WORLD, &matFinal);

    // Draw
    complex_obj->Draw(this, &index);

    // Reset world transformation
    D3DXMatrixIdentity(&matFinal);
    device_->SetTransform(D3DTS_WORLD, &matFinal);
  }
  for (auto drawable_obj : complex_obj->complex_list_) {
    DrawComplex(drawable_obj, index, (complex_obj->visible() && parent_visible));
  }
}

uint32_t Renderer::GetComplexVBObjectCount(std::shared_ptr<Drawable> obj) {
  uint32_t count = 1;
  for (auto complex : obj->complex_list_) {
    count += GetComplexVBObjectCount(complex);
  }
  return count;
}

void Renderer::GenerateVertices(v_3ct *vertices, uint32_t *index, std::shared_ptr<Drawable> obj) {
  obj->PrepareVertices(this, vertices, index);

  for (auto drawable : obj->complex_list_) {
    GenerateVertices(vertices, index, drawable);
  }
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateVertexBuffer(Renderer::BufferType type,
                                                       std::list<std::shared_ptr<Drawable>> list) {
  if (list.size() <= 0) {
    return NULL;
  }
  LPDIRECT3DVERTEXBUFFER9 vertex_buffer = nullptr;
  uint32_t object_count = 0;
  uint32_t index = 0;

  for (auto obj : list) {
    object_count += GetComplexVBObjectCount(obj);
  }

  v_3ct vertices[4 * object_count];
  for (std::shared_ptr<Drawable> obj : list) {
    GenerateVertices(vertices, &index, obj);
  }
  if (type == DYNAMIC) {
    if (FAILED(device_->CreateVertexBuffer(4 * index * sizeof(v_3ct),
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
  } else {
    if (FAILED(device_->CreateVertexBuffer(4 * index * sizeof(v_3ct), D3DUSAGE_WRITEONLY,
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
void Renderer::DrawTexture(uint32_t *index, std::string texture) {
  device_->SetTexture(0, texture_manager_->LoadTexture(texture.c_str()));
  device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * (*index), 2);
}