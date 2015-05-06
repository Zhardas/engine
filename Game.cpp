#include "Game.h"

Game::Game() {
    update_chrono_accumulator = std::chrono::microseconds(0);
    update_chrono_delta = std::chrono::duration<long,std::ratio<1,120>>(1);

    update_tick = 0;
    render_tick = 0;

    g_width = 1280;
    g_height = 720;
    g_mouse_position = new Position(0,0);
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
    g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    g_device->SetRenderState(D3DRS_LIGHTING, static_cast<DWORD>(false));
    g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    g_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
    g_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
    g_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);   //Ignored
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
        g_scene->Update();
        update_tick++;
        update_chrono_accumulator -= std::chrono::duration_cast<std::chrono::microseconds>(update_chrono_delta);
    }

    g_renderer->DrawScene(g_scene);
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

void Game::Initialize(HWND hWindow) {
    g_device = InitializeDevice(hWindow);
    g_renderer = new Renderer(this);
    if (g_device == nullptr)return;
    SetDeviceOptions();

    g_texture_manager = new TextureManager(this);

    //p_input = new Input(this);
    //p_input->Initialize(hInstance, hWindow);

    g_scene = new Scene(this);
    g_scene->Update();

    running_ = true;
}

Game *Game::GetInstance() {
    static Game* instance;
    if(instance == nullptr){
        instance = new Game();
    }
    return instance;
}
