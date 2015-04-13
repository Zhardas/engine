#include "Renderer.h"

Renderer::Renderer(Game *p_Game) {
    this->p_Game = p_Game;
    p_dx_VB = FillVertices(p_Game->p_Device);
    p_dx_IB = FillIndices(p_Game->p_Device);
    SetUpCamera(p_Game->p_Device);
}


void Renderer::SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device) {
    D3DXVECTOR3 m_EyePos(0, 0, -30);
    D3DXVECTOR3 m_TargetPos(0, 0, 0);
    D3DXVECTOR3 m_UpVector(0, 1, 0);
    D3DXMATRIXA16 m_View;
    D3DXMatrixLookAtLH(&m_View, &m_EyePos, &m_TargetPos, &m_UpVector);
    p_dx_Device->SetTransform(D3DTS_VIEW, &m_View);

    D3DXMATRIX m_Projection;
    D3DXMatrixPerspectiveFovLH(&m_Projection, D3DX_PI / 4, 500 / 500, 1, 50);
    p_dx_Device->SetTransform(D3DTS_PROJECTION, &m_Projection);
}

void Renderer::DrawScene(LPDIRECT3DDEVICE9 p_dx_Device, LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer,
                         LPDIRECT3DINDEXBUFFER9 p_dx_IndexBuffer) {
    p_dx_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(72, 61, 139), 1.0f, 0);
    p_dx_Device->BeginScene();

    p_dx_Device->SetStreamSource(0, p_dx_VertexBuffer, 0, sizeof(v_3c));
    p_dx_Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
    p_dx_Device->SetIndices(p_dx_IndexBuffer);
    p_dx_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 5, 0, 2);

    p_dx_Device->EndScene();
    p_dx_Device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DVERTEXBUFFER9 Renderer::FillVertices(LPDIRECT3DDEVICE9 p_dx_Device) {
    LPDIRECT3DVERTEXBUFFER9 p_dx_VertexBuffer;
    v_3c cv_Vertices[] =
            {
                    {0.0f,  0.0f, 0.0f, 0x00000000},
                    {5.0f,  0.0f, 0.0f, 0xffffffff},
                    {10.0f, 0.0f, 0.0f, 0x00000000},
                    {5.0f,  5.0f, 0.0f, 0xffffffff},
                    {10.0f, 5.0f, 0.0f, 0x00000000},
            };

    if (FAILED(p_dx_Device->CreateVertexBuffer(5 * sizeof(v_3c), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
                                               D3DPOOL_DEFAULT, &p_dx_VertexBuffer, NULL))) {

    }

    VOID *p_Vertices;
    if (FAILED(p_dx_VertexBuffer->Lock(0, 5 * sizeof(v_3c), (void **) &p_Vertices, 0))) {

    } else {
        memcpy(p_Vertices, cv_Vertices, 5 * sizeof(v_3c));
        p_dx_VertexBuffer->Unlock();
    }

    return p_dx_VertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Renderer::FillIndices(LPDIRECT3DDEVICE9 p_dx_Device) {
    short s_Indices[6];
    LPDIRECT3DINDEXBUFFER9 p_dx_IndexBuffer;

    s_Indices[0] = 0;
    s_Indices[1] = 3;
    s_Indices[2] = 1;
    s_Indices[3] = 4;
    s_Indices[4] = 2;
    s_Indices[5] = 1;

    if (FAILED(p_dx_Device->CreateIndexBuffer(6 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED,
                                              &p_dx_IndexBuffer, NULL))) {

    }

    VOID *p_Indices;
    if (FAILED(p_dx_IndexBuffer->Lock(0, 6 * sizeof(short), (void **) &p_Indices, 0))) {

    } else {
        memcpy(p_Indices, s_Indices, 6 * sizeof(short));
        p_dx_IndexBuffer->Unlock();
    }

    return p_dx_IndexBuffer;
}

void Renderer::Draw() {
    DrawScene(p_Game->p_Device, p_dx_VB, p_dx_IB);
}