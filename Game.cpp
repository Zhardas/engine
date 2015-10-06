#include "./game.h"

Game::Game() {
  width_ = 1280;
  height_ = 720;

  srand(static_cast<unsigned int>(time(NULL)));
  update_chrono_start_ = std::chrono::high_resolution_clock::now();
  update_time_start_ = std::time(NULL);
}

LRESULT CALLBACK WindowsMessageCallback(HWND window_handle, UINT message, WPARAM parameter1, LPARAM parameter2) {
  switch (message) {
    case WM_CLOSE: {
      Game::instance()->stop_running();
      break;
    };
    default: {
      if ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) || (message >= WM_KEYFIRST && message <= WM_KEYLAST)) {
        Game::instance()->input_manager_->ParseMessage(message, parameter1, parameter2);
      }
      break;
    };
  }
  return DefWindowProc(window_handle, message, parameter1, parameter2);
}

HWND Game::InitializeWindow(std::string title) {
  RECT window_size = {0, 0, width(), height()};
  AdjustWindowRectEx(&window_size, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, FALSE,
                     WS_EX_CONTROLPARENT);

  WNDCLASSEX window_structure;

  window_structure.cbSize = sizeof(WNDCLASSEX);
  window_structure.style = CS_HREDRAW | CS_VREDRAW;
  window_structure.lpfnWndProc = WindowsMessageCallback;
  window_structure.cbClsExtra = 0;
  window_structure.cbWndExtra = 0;
  window_structure.hInstance = GetModuleHandle(NULL);
  window_structure.hIcon = NULL;
  window_structure.hCursor = NULL;
  window_structure.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
  window_structure.lpszMenuName = NULL;
  window_structure.lpszClassName = "headache";
  window_structure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  RegisterClassEx(&window_structure);

  return CreateWindowEx(WS_EX_CONTROLPARENT,
                        "headache",
                        title.c_str(),
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                        0,
                        0,
                        window_size.right - window_size.left,
                        window_size.bottom - window_size.top,
                        NULL,
                        NULL,
                        GetModuleHandle(NULL),
                        NULL);
}

LPDIRECT3DDEVICE9 Game::InitializeDevice() {
  LPDIRECT3D9 dx;
  LPDIRECT3DDEVICE9 device;

  dx = Direct3DCreate9(D3D_SDK_VERSION);
  if (dx == NULL) {
    MessageBox(window_handle_, "DirectX Runtime library not installed!", "InitializeDevice()", MB_OK);
  }

  D3DPRESENT_PARAMETERS dx_presentation_parameters;
  ZeroMemory(&dx_presentation_parameters, sizeof(dx_presentation_parameters));
  dx_presentation_parameters.Windowed = TRUE;
  dx_presentation_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
  dx_presentation_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
  dx_presentation_parameters.AutoDepthStencilFormat = D3DFMT_D16;
  dx_presentation_parameters.EnableAutoDepthStencil = true;
  dx_presentation_parameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

  if (FAILED(dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window_handle_, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                              &dx_presentation_parameters, &device))) {
    if (FAILED(
        dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, window_handle_, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                         &dx_presentation_parameters, &device))) {
      MessageBox(window_handle_, "Failed to create even the reference device!", "InitializeDevice()", MB_OK);
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

  device_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
  device_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
  device_->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

  device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

//  device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
//  device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
//  device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

//  device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
//  device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
//  device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
//  device_->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16);
}

void Game::Loop() {
  auto new_time = std::chrono::high_resolution_clock::now();
  auto frame_time = new_time - update_chrono_start_;
  update_chrono_start_ = new_time;
  update_chrono_accumulator_ += std::chrono::duration_cast<std::chrono::microseconds>(frame_time);

  if (update_chrono_accumulator_ >= update_chrono_delta_) {
    audio_manager_->Update();
    scene_->Update();
    update_tick_++;
    update_chrono_accumulator_.zero();
  }
  renderer_->DrawScene(scene_);
  render_tick_++;

  // counter updates
  std::time_t update_time_current = std::time(NULL);
  if (update_time_current - update_time_start_ >= 1) {
    update_time_start_ = update_time_current;
    frames_per_second_ = render_tick_;
    updates_per_second_ = update_tick_;
    update_tick_ = 0;
    render_tick_ = 0;
  }
}

void Game::Initialize(std::string title) {
  if (device_ != nullptr)return;
  std::cout << "\nWindow initialization: ";
  window_handle_ = InitializeWindow(title);
  std::cout << "success!";

  std::cout
      << "\nDevice initialization: "; // TODO: Fix weird bug with std::cout repeating this line or use in-engine console.
  device_ = InitializeDevice();
  if (device_ != nullptr) {
    std::cout << "success!";
  } else {
    std::cout << "FAILED!";
  }

  std::cout << "\nRenderer initialization: ";
  renderer_ = new Renderer();
  std::cout << "success!";

  std::cout << "\nSetting device options: ";
  SetDeviceOptions();
  std::cout << "success!";

  std::cout << "\nTexture manager initialization: ";
  texture_manager_ = new TextureManager();
  std::cout << "success!";
  std::cout
      << "\nAudio manager initialization: "; // TODO: Fix weird bug with std::cout repeating this line or use in-engine console.
  audio_manager_ = new AudioManager();
  if (audio_manager_->InitializeAudio()) {
    std::cout << "success!";
  } else {
    std::cout << "FAIL!";
  }
  std::cout << "\nInput manager initialization: ";
  input_manager_ = new InputManager();
  std::cout << "success!";

  std::cout << "\nMiscellaneous initialization: ";
  // initialize random seed
  srand(static_cast<unsigned int>(time(NULL)));
  std::cout << "success!";

  running_ = true;
  std::cout << "\nEngine started.";
}

Game *Game::instance() {
  static Game *instance;
  if (instance == nullptr) {
    instance = new Game();
  }
  return instance;
}
Game::~Game() {
  device_->Release();
  delete device_;
  delete renderer_;
  delete texture_manager_;
  delete audio_manager_;
  delete scene_;
  DestroyWindow(window_handle());
}
