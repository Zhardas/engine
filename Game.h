class Game;

#ifndef GAME_H_
#define GAME_H_

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include "input/input_manager.h"
#include "graphics/renderer.h"
#include "graphics/texture_manager.h"
#include "scene/scene.h"
#include "audio/audio_manager.h"
#include "helper/types.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

LRESULT CALLBACK WindowsMessageCallback(HWND window_handle, UINT message, WPARAM parameter1, LPARAM parameter2);

class Game {
 private:
  bool running_;
  int width_;
  int height_;
  HWND window_handle_;
  std::chrono::high_resolution_clock::time_point update_chrono_start_;
  std::chrono::duration<int64_t, std::micro> update_chrono_accumulator_;
  std::chrono::duration<int64_t, std::ratio<1, 120> > update_chrono_delta_;
  std::time_t update_time_start_;
  int64_t update_tick_;
  int64_t render_tick_;


  LPDIRECT3DDEVICE9 InitializeDevice();

  HWND InitializeWindow(std::string title);

 public:
  LPDIRECT3DDEVICE9 device_;
  Scene *scene_;
  Renderer *renderer_;
  TextureManager *texture_manager_;
  AudioManager *audio_manager_;
  InputManager *input_manager_;

  Game();
  ~Game();

  static Game *instance();

  void SetDeviceOptions();

  void Initialize(std::string title, Scene* scene);

  int width() { return width_; }
  int height() { return height_; }
  bool running() { return running_; }
  void stop_running() { running_ = false; }
  void Loop();
  HWND window_handle() {return window_handle_;}
};


#endif  // GAME_H_
