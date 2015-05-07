class Game;

#ifndef HEADACHE_GAME_H
#define HEADACHE_GAME_H

#include "Graphics/Renderer.h"
#include "Graphics/TextureManager.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <Audio/AudioManager.h>
#include "Helper/types.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

class Game {
private:

    bool running_;
    std::chrono::high_resolution_clock::time_point update_chrono_start;
    std::chrono::duration<int64_t, std::micro> update_chrono_accumulator;
    std::chrono::duration<long, std::ratio<1, 120> > update_chrono_delta;
    std::time_t update_time_start;
    long update_tick;
    long render_tick;
public:
    LPDIRECT3DDEVICE9 g_device;
    int g_width;
    int g_height;
    Position* g_mouse_position;

    Scene* g_scene;
    Renderer* g_renderer;
    TextureManager* g_texture_manager;
    AudioManager* g_audio;
    //Input* p_input;

    Game();
    static Game* GetInstance();
    void SetDeviceOptions();
    void Loop();
    void Initialize(HWND hWindow);
    bool isRunning() {return running_;}
    void StopRunning(){running_ =  false;}
    LPDIRECT3DDEVICE9 InitializeDevice(HWND hWnd);
};


#endif //HEADACHE_GAME_H
