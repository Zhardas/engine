#include "Renderer.h"

Renderer::Renderer(Game *p_Game) {
    this->p_Game = p_Game;
    vb = TestFunction();
    SetUpCamera(p_Game->p_Device);

    p_Game->p_Device->SetStreamSource(0, vb, 0, sizeof(v_3t));
    p_Game->p_Device->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
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

void Renderer::Draw() {
    DrawScene(p_Game->p_Device);
}

void Renderer::DrawScene(LPDIRECT3DDEVICE9 pDevice9) {
    pDevice9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(72, 31, 39), 1.0f, 0);
    pDevice9->BeginScene();


    pDevice9->SetTexture(0, p_Game->p_TextureManager->GetTexture("default.png"));
    pDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 3);

    pDevice9->EndScene();
    pDevice9->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::TestFunction() {
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer;
    v_3t cv_Vertices[] =
            {
                    {0.0f,  -10.0f, 0.0f, 0.0f, 1.0f},
                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
                    {10.0f, -10.0f, 0.0f, 1.0f, 1.0f},
                    {10.0f, 0.0f, 0.0f, 1.0f, 0.0f},
                    {20.0f, 0.0f, 0.0f, 2.0f, 0.0f},
            };

    if (FAILED(p_Game->p_Device->CreateVertexBuffer(5 * sizeof(v_3t), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
                                                    D3DFVF_XYZ | D3DFVF_TEX1,
                                                    D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {

    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 5 * sizeof(v_3t), (void **) &p_Vertices, 0))) {

    } else {
        memcpy(p_Vertices, cv_Vertices, 5 * sizeof(v_3t));
        p_dx_VertexBuffer->Unlock();
    }
    return p_dx_VertexBuffer;
}
