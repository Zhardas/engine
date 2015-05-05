class Game;

#ifndef HEADACHE_GAME_H
#define HEADACHE_GAME_H

#include "Graphics/Renderer.h"
#include "Graphics/TextureManager.h"
#include <ctime>
#include <chrono>
#include "Input/Input.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

class Game {
private:

    bool running_;
    std::chrono::high_resolution_clock::time_point update_chrono_start;
    std::chrono::duration<int64_t, std::micro> update_chrono_accumulator = std::chrono::microseconds(0);
    std::chrono::duration<long, std::ratio<1, 120>> update_chrono_delta = std::chrono::duration<long,std::ratio<1,120>>(1);
    std::time_t update_time_start;
    long update_tick = 0;
    long render_tick = 0;
public:
    LPDIRECT3DDEVICE9 p_device;
    FLOAT g_width;
    FLOAT g_height;

    Scene* p_scene;
    Renderer* p_renderer;
    TextureManager* p_texture_manager;
    //Input* p_input;

    Game();
    void SetDeviceOptions();
    void Loop();
    void Initialize(HINSTANCE hInstance, HWND hWindow);
    bool isRunning() {return running_;};
    void StopRunning(){running_ =  false;};
    LPDIRECT3DDEVICE9 InitializeDevice(HWND hWnd);
};


#endif //HEADACHE_GAME_H
