#include <c++/iostream>
#include "Game.h"

Game::Game() {
    g_width = 1280;
    g_height = 720;
    update_chrono_start = std::chrono::high_resolution_clock::now();
    update_time_start = std::time(NULL);
    update_chrono_accumulator = std::chrono::microseconds(0);
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
    auto current = std::chrono::high_resolution_clock::now();
    auto frameTime = current - update_chrono_start;

    update_chrono_accumulator += std::chrono::duration_cast<std::chrono::microseconds>(frameTime);

    //if( update_chrono_accumulator >= update_chrono_delta){
    //    p_input->Update();
    //}
    while ( update_chrono_accumulator >= update_chrono_delta)
    {
        p_scene->Update();
        update_tick++;
        update_chrono_accumulator -= std::chrono::duration_cast<std::chrono::microseconds>(update_chrono_delta);
    }

    p_renderer->DrawScene(p_scene);
    render_tick++;

    update_chrono_start = current;
    std::time_t update_time_current = std::time(NULL);
    if(update_time_current - update_time_start >= 1) {
        update_time_start = update_time_current;
        //std::cout << "UPS: " << update_tick << "\n";
        //std::cout << "FPS: " << render_tick << "\n";
        update_tick = 0;
        render_tick = 0;
    }
}

void Game::Initialize
        (HINSTANCE hInstance, HWND hWindow) {
    p_device = InitializeDevice(hWindow);
    p_renderer = new Renderer(this);
    if (p_device == nullptr)return;
    SetDeviceOptions();

    p_texture_manager = new TextureManager(this);

    //p_input = new Input(this);
    //p_input->Initialize(hInstance, hWindow);

    p_scene = new Scene(this);
    p_scene->Update();

    running_ = true;
}
