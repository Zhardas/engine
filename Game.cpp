#include "Game.h"

Game::Game(HWND hWindow) {
    p_Device = InitializeDevice(hWindow);
    p_Renderer = new Renderer(this);
    if (p_Device == nullptr)return;
    SetDeviceOptions();
    isRunning = true;
}

LPDIRECT3DDEVICE9 Game::InitializeDevice(HWND hWnd) {
    LPDIRECT3D9 p_dx_Object;
    LPDIRECT3DDEVICE9 p_dx_Device;

    p_dx_Object = Direct3DCreate9(D3D_SDK_VERSION);
    if (p_dx_Object == NULL) {
        MessageBox(hWnd, "DirectX Runtime library not installed!", "InitializeDevice()", MB_OK);
    }

    D3DPRESENT_PARAMETERS dx_PresParams;
    ZeroMemory(&dx_PresParams, sizeof(dx_PresParams));
    dx_PresParams.Windowed = TRUE;
    dx_PresParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    dx_PresParams.BackBufferFormat = D3DFMT_UNKNOWN;

    if (FAILED(p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                         &dx_PresParams, &p_dx_Device))) {
        if (FAILED(
                p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                          &dx_PresParams, &p_dx_Device))) {
            MessageBox(hWnd, "Failed to create even the reference device!", "InitializeDevice()", MB_OK);
            return nullptr;
        }
    }

    return p_dx_Device;
}

void Game::SetDeviceOptions() {
    p_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    p_Device->SetRenderState(D3DRS_LIGHTING, false);
    p_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void Game::Loop() {
    p_Renderer->Draw();
}
