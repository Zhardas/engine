class Game;

#ifndef GAME_H_
#define GAME_H_

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#define D3D_DEBUG_INFO
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <networking/network_manager.h>
#include "input/input_manager.h"
#include "graphics/renderer.h"
#include "graphics/texture_manager.h"
#include "scene/scene.h"
#include "audio/audio_manager.h"
#include "helper/types.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

LRESULT CALLBACK WindowsMessageCallback(
    HWND window_handle, 
    UINT message, 
    WPARAM parameter1, 
    LPARAM parameter2);

class Game {
 private:
  int64_t update_tick_ = 0;
  int64_t render_tick_ = 0;
  bool running_;
  int width_;
  int height_;
  bool online_;
  HWND window_handle_;
  DWORD window_parameters_ = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
  std::chrono::high_resolution_clock::time_point update_chrono_start_;
  std::chrono::duration<float, std::ratio<1, 60> >
      update_chrono_accumulator_ = std::chrono::duration
      <float, std::ratio<1, 60>>(0);
  // TODO(Zhardas): update_chrono_delta_ should be equal to monitor refresh rate (or should it?). NB! Check header too.
  const std::chrono::duration<float, std::ratio<1, 60> >
      update_chrono_delta_ = std::chrono::duration<float, std::ratio<1, 60>>(1);
  std::time_t update_time_start_;

  LPDIRECT3DDEVICE9 InitializeDevice();

  HWND InitializeWindow(std::string title);

 public:
  int64_t updates_per_second_ = 0;
  int64_t frames_per_second_ = 0;
  LPDIRECT3DDEVICE9 device_ = nullptr;
  Scene *scene_ = nullptr;
  Renderer *renderer_ = nullptr;
  TextureManager *texture_manager_ = nullptr;
  AudioManager *audio_manager_ = nullptr;
  InputManager *input_manager_ = nullptr;
  NetworkManager *network_manager_ = nullptr;

  Game();
  ~Game();

  static Game *instance();

  void SetDeviceOptions();

  void Initialize(std::string title);

  int width() { return width_; }
  int height() { return height_; }
  bool running() { return running_; }
  void stop_running() { running_ = false; }
  void Loop();
  HWND window_handle() { return window_handle_; }
  Position window_position();
  bool online() { return online_; }
  void set_online(bool online) { online_ = online; }
};

#endif  // GAME_H_
