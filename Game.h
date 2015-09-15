class Game;

#ifndef GAME_H_
#define GAME_H_

#include <ctime>
#include <chrono>
#include <iostream>
#include <d3d9.h>
#include "graphics/renderer.h"
#include "graphics/texture_manager.h"
#include "scene/scene.h"
#include "audio/audio_manager.h"
#include "helper/types.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

class Game {
 private:
  bool running_;
  int width_;
  int height_;
  std::chrono::high_resolution_clock::time_point update_chrono_start_;
  std::chrono::duration<int64_t, std::micro> update_chrono_accumulator_;
  std::chrono::duration<int64_t, std::ratio<1, 120> > update_chrono_delta_;
  std::time_t update_time_start_;
  int64_t update_tick_;
  int64_t render_tick_;
  LPDIRECT3DDEVICE9 InitializeDevice(HWND hWnd);

 public:
  LPDIRECT3DDEVICE9 device_;
  Position *mouse_position_;
  Scene *scene_;
  Renderer *renderer_;
  TextureManager *texture_manager_;
  AudioManager *audio_manager_;

  Game();

  static Game *instance();

  void SetDeviceOptions();

  void Loop();

  void Initialize(HWND hWindow);

  int width() { return width_; }
  int height() { return height_; }
  bool running() { return running_; }
  void stop_running() { running_ = false; }
  LPDIRECT3DDEVICE9 device() { return device_; };
};


#endif  // GAME_H_
