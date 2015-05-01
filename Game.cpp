#include <c++/iostream>
#include "Game.h"

Game::Game() {
    g_width = 1280;
    g_height = 720;
    updateTimer = time(NULL);
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
    dx_PresParams.BackBufferFormat = D3DFMT_X8R8G8B8;

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
    p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    p_device->SetRenderState(D3DRS_LIGHTING, (DWORD) false);
    p_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    p_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
    p_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
    p_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);   //Ignored
}

void Game::Loop() {
    time_t new_time = time(NULL);
    if(difftime(new_time, updateTimer) > 0.166666f){ // Update 60x/sec
        updateTimer = new_time;
        p_scene->Update();
        std::cout << "Scene update!\n";
    }else{
    }
    p_renderer->DrawScene(p_scene);
}

void Game::InitGraphics(HWND hWindow) {
    p_device = InitializeDevice(hWindow);
    p_renderer = new Renderer(this);
    if (p_device == nullptr)return;
    SetDeviceOptions();

    p_TextureManager = new TextureManager(this);

    p_scene = new Scene(p_renderer);
    p_scene->Update();

    running_ = true;
}
