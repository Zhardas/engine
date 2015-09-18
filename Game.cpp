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

LRESULT CALLBACK OurWindowProcedure(HWND window_handle, UINT message, WPARAM parameter1, LPARAM parameter2) {
  Game *game = Game::instance();
  switch (message) {
    case WM_CLOSE: {
      game->stop_running();
      break;
    };
    default: {
      if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) {
        Position pos = Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2));
        pos.y = game->height() - pos.y;
        switch (message) {
          case WM_MOUSEMOVE: {
            game->mouse_position_->x = GET_X_LPARAM(parameter2);
            game->mouse_position_->y = GET_Y_LPARAM(parameter2);
            game->scene_->EventCall(MOUSE_MOVE, MOUSE_LEFT, &pos);
          };
            break;
          case WM_LBUTTONUP: {
            game->scene_->EventCall(MOUSE_UP, MOUSE_LEFT, &pos);
          };
            break;
          case WM_MBUTTONUP: {
            game->scene_->EventCall(MOUSE_UP, MOUSE_MIDDLE, &pos);
          };
            break;
          case WM_RBUTTONUP: {
            game->scene_->EventCall(MOUSE_UP, MOUSE_RIGHT, &pos);
          };
            break;
          case WM_LBUTTONDOWN: {
            game->scene_->EventCall(MOUSE_DOWN, MOUSE_LEFT, &pos);
          };
            break;
          case WM_MBUTTONDOWN: {
            game->scene_->EventCall(MOUSE_DOWN, MOUSE_MIDDLE, &pos);
          };
            break;
          case WM_RBUTTONDOWN: {
            game->scene_->EventCall(MOUSE_DOWN, MOUSE_RIGHT, &pos);
          };
            break;
          default:
            break;
        }
      }
      else if (message >= WM_KEYFIRST && message <= WM_KEYLAST) {
        switch (message) {
          case WM_KEYUP: {
            game->scene_->EventCall(KEYBOARD_UP, static_cast<uint8_t>(parameter1), nullptr);
          };
            break;
          case WM_KEYDOWN: {
            game->scene_->EventCall(KEYBOARD_DOWN, static_cast<uint8_t>(parameter1), nullptr);
          };
            break;
          default:
            break;
        }
      }
      break;
    };
  }
  return DefWindowProc(window_handle, message, parameter1, parameter2);
}

HWND Game::InitializeWindow(std::string title) {
  RECT wnd_size = {0, 0, width(), height()};
  AdjustWindowRectEx(&wnd_size, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, FALSE,
                     WS_EX_CONTROLPARENT);

  WNDCLASSEX wnd_Structure;

  wnd_Structure.cbSize = sizeof(WNDCLASSEX);
  wnd_Structure.style = CS_HREDRAW | CS_VREDRAW;
  wnd_Structure.lpfnWndProc = OurWindowProcedure;
  wnd_Structure.cbClsExtra = 0;
  wnd_Structure.cbWndExtra = 0;
  wnd_Structure.hInstance = GetModuleHandle(NULL);
  wnd_Structure.hIcon = NULL;
  wnd_Structure.hCursor = NULL;
  wnd_Structure.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
  wnd_Structure.lpszMenuName = NULL;
  wnd_Structure.lpszClassName = "Overlord";
  wnd_Structure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  RegisterClassEx(&wnd_Structure);

  return CreateWindowEx(WS_EX_CONTROLPARENT,
                        "Overlord",
                        title.c_str(),
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                        0,
                        0,
                        wnd_size.right - wnd_size.left,
                        wnd_size.bottom - wnd_size.top,
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

  D3DPRESENT_PARAMETERS dx_pres_params;
  ZeroMemory(&dx_pres_params, sizeof(dx_pres_params));
  dx_pres_params.Windowed = TRUE;
  dx_pres_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
  dx_pres_params.BackBufferFormat = D3DFMT_X8R8G8B8;
  dx_pres_params.AutoDepthStencilFormat = D3DFMT_D16;
  dx_pres_params.EnableAutoDepthStencil = true;
  dx_pres_params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

  if (FAILED(dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window_handle_, D3DCREATE_HARDWARE_VERTEXPROCESSING,
                              &dx_pres_params, &device))) {
    if (FAILED(
        dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, window_handle_, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                         &dx_pres_params, &device))) {
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

void Game::Initialize(std::string title) {
  window_handle_ = InitializeWindow(title);

  if (device_ != nullptr)return;
  device_ = InitializeDevice();
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
Game::~Game() {
  DestroyWindow(window_handle());
}
