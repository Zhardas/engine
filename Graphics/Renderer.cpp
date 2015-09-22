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
        switch (layer->GetType()) {
            case Layer::STATIC: {
                DrawableLayer *cast_layer = static_cast<DrawableLayer *>(layer);
                if (cast_layer->reload) {
                    cast_layer->reload = false;
                    if (cast_layer->vertex_buffer_ != NULL) {
                        cast_layer->vertex_buffer_->Release();
                    }
                    cast_layer->vertex_buffer_ = GenerateStaticVertexBuffer(cast_layer->drawable_list_);
                }
                if (cast_layer->vertex_buffer_ != NULL) {
                    Game::instance()->device_->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
                    Game::instance()->device_->SetStreamSource(0, cast_layer->vertex_buffer_, 0, sizeof(v_3t));
                    for (TexturedQuad *obj : *cast_layer->drawable_list_) {
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
                        index++;

                        // Reset world transformation
                        D3DXMatrixIdentity(&matFinal);
                        device->SetTransform(D3DTS_WORLD, &matFinal);
                    }
                }
            }
                break;
            case Layer::DYNAMIC: {
                DrawableLayer *cast_layer = static_cast<DrawableLayer *>(layer);
                cast_layer->vertex_buffer_ = GenerateDynamicVertexBuffer(cast_layer->drawable_list_);
                if (cast_layer->vertex_buffer_ != NULL) {
                    Game::instance()->device_->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
                    Game::instance()->device_->SetStreamSource(0, cast_layer->vertex_buffer_, 0, sizeof(v_3ct));
                    index = 0;
                    for (TexturedQuad *obj : *cast_layer->drawable_list_) {
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
                        index++;

                        // Reset world transformation
                        D3DXMatrixIdentity(&matFinal);
                        device->SetTransform(D3DTS_WORLD, &matFinal);
                    }
                    cast_layer->vertex_buffer_->Release();
                    delete cast_layer->vertex_buffer_;
                    cast_layer->vertex_buffer_ = NULL;
                }
            }
                break;
            case Layer::TEXT: {
                TextLayer *cast_layer = static_cast<TextLayer *>(layer);
                for (Text *text_item : *cast_layer->text_list_) {
                    Position pos = text_item->position();
                    Size size = text_item->size();
                    RECT r = {(LONG) pos.x, (LONG) pos.y,
                              (LONG) (pos.x + size.width),
                              (LONG) (pos.y + size.height)};
                    text_item->font_->font()->DrawText(NULL,
                                                          text_item->text().c_str(), -1,
                                                          &r,
                                                          DT_CENTER,
                                                          D3DCOLOR_ARGB(text_item->color_alpha_, text_item->color_red_,
                                                                       text_item->color_green_,
                                                                       text_item->color_blue_));
                }
            }
                break;
        }
    }

    device->EndScene();
    device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateStaticVertexBuffer(std::list<TexturedQuad *> *object_list) {
    if (object_list->size() <= 0) {
        return NULL;
    }
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3t cv_Vertices[4 * object_list->size()];
    for (TexturedQuad *obj : *object_list) {
        cv_Vertices[index * 4] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {0.0f, obj->size().height, 0.0f, 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {obj->size().width, 0.0f, 0.0f, 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {obj->size().width, obj->size().height, 0.0f, 1.0f, 0.0f};
        index++;
    }
    if (FAILED(Game::instance()->device_->CreateVertexBuffer(4 * index * sizeof(v_3t), D3DUSAGE_WRITEONLY,
                                                   D3DFVF_XYZ | D3DFVF_TEX1,
                                                   D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {
        //TODO: Error handling
    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 4 * index * sizeof(v_3t), &p_Vertices, 0))) {
        //TODO: Error handling
    } else {
        memcpy(p_Vertices, cv_Vertices, 4 * index * sizeof(v_3t));
        p_dx_VertexBuffer->Unlock();
    }
    return p_dx_VertexBuffer;
}

void Renderer::Draw(TexturedQuad *pQuad, UINT index) {
    Game::instance()->device_->SetTexture(0, Game::instance()->texture_manager_->LoadTexture(pQuad->texture().c_str()));
    Game::instance()->device_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * index, 2);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateDynamicVertexBuffer(std::list<TexturedQuad *> *object_list) {
    if (object_list->size() <= 0) {
        return NULL;
    }
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3ct cv_Vertices[4 * object_list->size()];
    for (TexturedQuad *obj : *object_list) {
        cv_Vertices[index * 4] = {0.0f, 0.0f, 0.0f, obj->color(), 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {0.0f, obj->size().height, 0.0f, obj->color(), 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {obj->size().width, 0.0f, 0.0f, obj->color(), 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {obj->size().width, obj->size().height, 0.0f, obj->color(), 1.0f,
                                      0.0f};
        index++;
    }
    if (FAILED(Game::instance()->device_->CreateVertexBuffer(4 * index * sizeof(v_3ct), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                                   D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
                                                   D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {
        //TODO: Error handling
    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 4 * index * sizeof(v_3ct), &p_Vertices, D3DLOCK_DISCARD))) {
        //TODO: Error handling
    } else {
        memcpy(p_Vertices, cv_Vertices, 4 * index * sizeof(v_3ct));
        p_dx_VertexBuffer->Unlock();
    }
    return p_dx_VertexBuffer;
}
