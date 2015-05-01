#include "Renderer.h"

Renderer::Renderer(Game *p_game) {
    this->p_Game = p_game;
    SetUpCamera(p_game->p_device);
    p_Game->p_device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
}

void Renderer::SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device) {
    D3DXVECTOR3 m_EyePos(0, 0, -100);
    D3DXVECTOR3 m_TargetPos(0, 0, 0);
    D3DXVECTOR3 m_UpVector(0, 1, 0);
    D3DXMATRIXA16 m_View;
    D3DXMatrixLookAtLH(&m_View, &m_EyePos, &m_TargetPos, &m_UpVector);
    p_dx_Device->SetTransform(D3DTS_VIEW, &m_View);

    D3DXMATRIX m_Projection;
    D3DXMatrixPerspectiveFovLH(&m_Projection, D3DX_PI / 4, p_Game->g_width / p_Game->g_height, 1, 100);
    p_dx_Device->SetTransform(D3DTS_PROJECTION, &m_Projection);
}


void Renderer::DrawScene(Scene *scene) {
    LPDIRECT3DDEVICE9 pDevice9 = p_Game->p_device;
    pDevice9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(72, 31, 39), 1.0f, 0);
    pDevice9->BeginScene();

    p_Game->p_device->SetStreamSource(0, vb_static_background, 0, sizeof(v_3t));
    std::list<TexturedQuad*> *bgList = scene->GetBackgroundDrawables();
    UINT index = 0;
    for (std::list<TexturedQuad *>::iterator it = bgList->begin(); it != bgList->end(); ++it) {
        TexturedQuad *temp = *it;
        Draw(temp, index);
        index++;
    }


    std::list<TexturedQuad*> *dynamicList = scene->GetDynamicDrawables();
    vb_dynamic = GenerateDynamicVertexBuffer(dynamicList);
    p_Game->p_device->SetStreamSource(0, vb_dynamic, 0, sizeof(v_3t));
    index = 0;
    for (std::list<TexturedQuad *>::iterator it = dynamicList->begin(); it != dynamicList->end(); ++it) {
        TexturedQuad *temp = *it;
        Draw(temp, index);
        index++;
    }

    p_Game->p_device->SetStreamSource(0, vb_static_ui, 0, sizeof(v_3t));
    std::list<TexturedQuad*> *uiList = scene->GetUIDrawables();
    index = 0;
    for (std::list<TexturedQuad*>::iterator it = uiList->begin(); it != uiList->end(); ++it) {
        TexturedQuad *temp = *it;
        Draw(temp, index);
        index++;
    }

    pDevice9->EndScene();
    pDevice9->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateStaticVertexBuffer(std::list<TexturedQuad *> *pList){
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3t cv_Vertices[4 * pList->size()];
    for (std::list<TexturedQuad *>::iterator it = pList->begin(); it != pList->end(); ++it) {
        TexturedQuad *temp = *it;
        float x_shift = temp->size().width / 2;
        float y_shift = temp->size().height / 2;

        cv_Vertices[index * 4] = {temp->position().x - x_shift, temp->position().y - y_shift, 0.0f, 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {temp->position().x - x_shift, temp->position().y +
                                                                    y_shift, 0.0f, 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {temp->position().x + x_shift, temp->position().y -
                                                                    y_shift, 0.0f, 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {temp->position().x + x_shift, temp->position().y +
                                                                    y_shift, 0.0f, 1.0f, 0.0f};
        index++;
    }
    if (FAILED(p_Game->p_device->CreateVertexBuffer(4 * index * sizeof(v_3t), D3DUSAGE_WRITEONLY,
                                                    D3DFVF_XYZ | D3DFVF_TEX1,
                                                    D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {
        //TODO: Error handling
    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 4 * index * sizeof(v_3t), (void **) &p_Vertices, 0))) {
        //TODO: Error handling
    } else {
        memcpy(p_Vertices, cv_Vertices, 4 * index * sizeof(v_3t));
        p_dx_VertexBuffer->Unlock();
    }
    return p_dx_VertexBuffer;
}

void Renderer::Reload() {
    vb_static_background = GenerateStaticVertexBuffer(p_Game->p_scene->GetBackgroundDrawables());
    vb_static_ui = GenerateStaticVertexBuffer(p_Game->p_scene->GetUIDrawables());
}

void Renderer::Draw(TexturedQuad *pQuad, UINT index) {
    p_Game->p_device->SetTexture(0, p_Game->p_TextureManager->GetTexture(pQuad->GetTexture().c_str()));
    p_Game->p_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*index, 2);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::GenerateDynamicVertexBuffer(std::list<TexturedQuad *> *pList) {
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer = nullptr;
    UINT index = 0;

    v_3t cv_Vertices[4 * pList->size()];
    for (std::list<TexturedQuad *>::iterator it = pList->begin(); it != pList->end(); ++it) {
        TexturedQuad *temp = *it;
        float x_shift = temp->size().width / 2;
        float y_shift = temp->size().height / 2;

        cv_Vertices[index * 4] = {temp->position().x - x_shift, temp->position().y - y_shift, 0.0f, 0.0f, 1.0f};
        cv_Vertices[index * 4 + 1] = {temp->position().x - x_shift, temp->position().y +
                                                                    y_shift, 0.0f, 0.0f, 0.0f};
        cv_Vertices[index * 4 + 2] = {temp->position().x + x_shift, temp->position().y -
                                                                    y_shift, 0.0f, 1.0f, 1.0f};
        cv_Vertices[index * 4 + 3] = {temp->position().x + x_shift, temp->position().y +
                                                                    y_shift, 0.0f, 1.0f, 0.0f};
        index++;
    }
    if (FAILED(p_Game->p_device->CreateVertexBuffer(4 * index * sizeof(v_3t), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                                    D3DFVF_XYZ | D3DFVF_TEX1,
                                                    D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {
        //TODO: Error handling
    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 4 * index * sizeof(v_3t), (void **) &p_Vertices, D3DLOCK_DISCARD))) {
        //TODO: Error handling
    } else {
        memcpy(p_Vertices, cv_Vertices, 4 * index * sizeof(v_3t));
        p_dx_VertexBuffer->Unlock();
    }
    return p_dx_VertexBuffer;
}
