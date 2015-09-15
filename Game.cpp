#include "./game.h"

Game::Game() {
    update_chrono_accumulator_ = std::chrono::microseconds(0);
    update_chrono_delta_ = std::chrono::duration<int64_t, std::ratio<1, 120>>(1);

    srand(static_cast<unsigned int>(time(NULL)));

    update_tick_ = 0;
    render_tick_ = 0;

    width_ = 1280;
    height_ = 720;
    mouse_position_ = new Position(0, 0);
    update_chrono_start_ = std::chrono::high_resolution_clock::now();
    update_time_start_ = std::time(NULL);
    update_chrono_accumulator_ = std::chrono::microseconds(0);
}

LPDIRECT3DDEVICE9 Game::InitializeDevice(HWND hWnd) {
    LPDIRECT3D9 dx;
    LPDIRECT3DDEVICE9 device;

    dx = Direct3DCreate9(D3D_SDK_VERSION);
    if (dx == NULL) {
        MessageBox(hWnd, "DirectX Runtime library not installed!", "InitializeDevice()", MB_OK);
    }

    D3DPRESENT_PARAMETERS dx_PresParams;
    ZeroMemory(&dx_PresParams, sizeof(dx_PresParams));
    dx_PresParams.Windowed = TRUE;
    dx_PresParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    dx_PresParams.BackBufferFormat = D3DFMT_X8R8G8B8;
    dx_PresParams.AutoDepthStencilFormat = D3DFMT_D16;
    dx_PresParams.EnableAutoDepthStencil = true;
    dx_PresParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (FAILED(dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                         &dx_PresParams, &device))) {
        if (FAILED(
                dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                          &dx_PresParams, &device))) {
            MessageBox(hWnd, "Failed to create even the reference device!", "InitializeDevice()", MB_OK);
            return nullptr;
        }
    }
    return device;
}

void Game::SetDeviceOptions() {
    device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    device_->SetRenderState(D3DRS_LIGHTING, static_cast<DWORD>(false));

    device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    device_->SetRenderState(D3DRS_ALPHABLENDENABLE, static_cast<DWORD>(true));

    device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

    // g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    // g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    // g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    // g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
    // g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
    // g_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
    // g_device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);
}

void Game::Loop() {
    auto current = std::chrono::high_resolution_clock::now();
    auto frameTime = current - update_chrono_start_;

    update_chrono_accumulator_ += std::chrono::duration_cast<std::chrono::microseconds>(frameTime);

    if (update_chrono_accumulator_ >= update_chrono_delta_) {
        //    p_input->Update();
        audio_manager_->Update();
    }
    while (update_chrono_accumulator_ >= update_chrono_delta_) {
        scene_->Update();
        update_tick_++;
        update_chrono_accumulator_ -= std::chrono::duration_cast<std::chrono::microseconds>(update_chrono_delta_);
    }

    renderer_->DrawScene(scene_);
    render_tick_++;

    update_chrono_start_ = current;
    std::time_t update_time_current = std::time(NULL);
    if (update_time_current - update_time_start_ >= 1) {
        update_time_start_ = update_time_current;
        // std::cout << "UPS: " << update_tick_ << "\n";
        // std::cout << "FPS: " << render_tick_ << "\n";
        update_tick_ = 0;
        render_tick_ = 0;
    }
}

void Game::Initialize(HWND hWindow) {
    device_ = InitializeDevice(hWindow);
    renderer_ = new Renderer();
    if (device_ == nullptr)return;
    SetDeviceOptions();

    texture_manager_ = new TextureManager();
    audio_manager_ = new AudioManager();
    audio_manager_->InitializeAudio();

    running_ = true;
}

Game *Game::instance() {
    static Game *instance;
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}
