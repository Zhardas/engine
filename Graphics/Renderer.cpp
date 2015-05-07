#include "Renderer.h"

Renderer::Renderer() {
    g_game = Game::GetInstance();
    SetUpCamera(g_game->g_device);
    firstReload = true;
}

void Renderer::SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device) {
    D3DXMATRIX matOrtho;
    D3DXMATRIX matIdentity;

    //Setup orthographic projection matrix
    D3DXMatrixOrthoLH(&matOrtho, g_game->g_width, g_game->g_height, 0.0f, 10.0f);
    D3DXMatrixIdentity(&matIdentity);
    p_dx_Device->SetTransform(D3DTS_PROJECTION, &matOrtho);
    p_dx_Device->SetTransform(D3DTS_WORLD, &matIdentity);
    p_dx_Device->SetTransform(D3DTS_VIEW, &matIdentity);
}


void Renderer::DrawScene(Scene *scene) {
    LPDIRECT3DDEVICE9 pDevice9 = g_game->g_device;
    pDevice9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, clear_color.r, clear_color.g, clear_color.b), 1.0f, 0);
    pDevice9->BeginScene();

    UINT index = 0;
    if (vb_static_background != NULL) {
        g_game->g_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
        g_game->g_device->SetStreamSource(0, vb_static_background, 0, sizeof(v_3t));
        std::list<TexturedQuad *> *bgList = scene->GetBackgroundDrawables();
        for (std::list<TexturedQuad *>::iterator it = bgList->begin(); it != bgList->end(); ++it) {
            Draw(*it, index);
            index++;
        }
    }


    std::list<TexturedQuad *> *dynamicList = scene->GetDynamicDrawables();
    if (vb_dynamic != NULL) {
        vb_dynamic->Release();
    }
    vb_dynamic = GenerateDynamicVertexBuffer(dynamicList);
    if (vb_dynamic != NULL) {
        g_game->g_device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
        g_game->g_device->SetStreamSource(0, vb_dynamic, 0, sizeof(v_3ct));
        index = 0;
        for (std::list<TexturedQuad *>::iterator it = dynamicList->begin(); it != dynamicList->end(); ++it) {
            Draw(*it, index);
            index++;
        }
        delete vb_dynamic;
    }

    if (vb_static_ui != NULL) {
        std::list<TexturedQuad *> *uiList = scene->GetUIDrawables();
        g_game->g_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
        g_game->g_device->SetStreamSource(0, vb_static_ui, 0, sizeof(v_3t));
        index = 0;
        for (std::list<TexturedQuad *>::iterator it = uiList->begin(); it != uiList->end(); ++it) {
            Draw(*it, index);
            index++;
        }
    }
    pDevice9->EndScene();
    pDevice9->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateStaticVertexBuffer(std::list<TexturedQuad *> *pList) {
    if (pList->size() <= 0) {
        return NULL;
    }
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3t cv_Vertices[4 * pList->size()];
    for (std::list<TexturedQuad *>::iterator it = pList->begin(); it != pList->end(); ++it) {
        TexturedQuad *temp = *it;
        float x_shift = temp->GetScaledSize()->width / 2;
        float y_shift = temp->GetScaledSize()->height / 2;

        cv_Vertices[index * 4] = {temp->GetPosition()->x - x_shift - g_game->g_width / 2,
                                  -temp->GetPosition()->y - y_shift + g_game->g_height / 2, 0.0f, 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {temp->GetPosition()->x - x_shift - g_game->g_width / 2, -temp->GetPosition()->y +
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f, 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {temp->GetPosition()->x + x_shift - g_game->g_width / 2, -temp->GetPosition()->y -
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f, 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {temp->GetPosition()->x + x_shift - g_game->g_width / 2, -temp->GetPosition()->y +
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f, 1.0f, 0.0f};
        index++;
    }
    if (FAILED(g_game->g_device->CreateVertexBuffer(4 * index * sizeof(v_3t), D3DUSAGE_WRITEONLY,
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

void Renderer::Reload() {
    if (!firstReload) {
        vb_static_background->Release();
        vb_dynamic->Release();
        vb_static_ui->Release();
    } else {
        vb_dynamic = GenerateDynamicVertexBuffer(g_game->g_scene->GetDynamicDrawables());
    }
    vb_static_background = GenerateStaticVertexBuffer(g_game->g_scene->GetBackgroundDrawables());
    vb_static_ui = GenerateStaticVertexBuffer(g_game->g_scene->GetUIDrawables());
    firstReload = false;
}

void Renderer::Draw(TexturedQuad *pQuad, UINT index) {
    g_game->g_device->SetTexture(0, g_game->g_texture_manager->GetTexture(pQuad->GetTexture().c_str()));
    g_game->g_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * index, 2);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateDynamicVertexBuffer(std::list<TexturedQuad *> *pList) {
    if (pList->size() <= 0) {
        return NULL;
    }
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3ct cv_Vertices[4 * pList->size()];
    for (std::list<TexturedQuad *>::iterator it = pList->begin(); it != pList->end(); ++it) {
        TexturedQuad *temp = *it;
        float x_shift = temp->GetScaledSize()->width / 2;
        float y_shift = temp->GetScaledSize()->height / 2;

        cv_Vertices[index * 4] = {temp->GetPosition()->x - x_shift - g_game->g_width / 2, -temp->GetPosition()->y -
                                                                                          y_shift +
                                                                                          g_game->g_height / 2, 0.0f,
                                  temp->GetColorARGB(), 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {temp->GetPosition()->x - x_shift - g_game->g_width / 2, -temp->GetPosition()->y +
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f,
                                      temp->GetColorARGB(), 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {temp->GetPosition()->x + x_shift - g_game->g_width / 2, -temp->GetPosition()->y -
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f,
                                      temp->GetColorARGB(), 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {temp->GetPosition()->x + x_shift - g_game->g_width / 2, -temp->GetPosition()->y +
                                                                                              y_shift +
                                                                                              g_game->g_height / 2,
                                      0.0f,
                                      temp->GetColorARGB(), 1.0f, 0.0f};
        index++;
    }
    if (FAILED(g_game->g_device->CreateVertexBuffer(4 * index * sizeof(v_3ct), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
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
