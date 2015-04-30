class Game;

#ifndef HEADACHE_GAME_H
#define HEADACHE_GAME_H

#include "Graphics/Renderer.h"
#include "Graphics/TextureManager.h"
#include <ctime>

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

class Game {
private:
    Renderer* p_renderer;
    bool running_;
    time_t timer;
    long tick;
public:
    Game();

    LPDIRECT3DDEVICE9 p_Device;

    LPDIRECT3DDEVICE9 InitializeDevice(HWND hWnd);

    void SetDeviceOptions();

    void Loop();

    FLOAT g_width;
    FLOAT g_height;

    void InitGraphics(HWND hWindow);

    TextureManager* p_TextureManager;
    bool isRunning() {return running_;};

    void StopRunning();
};


#endif //HEADACHE_GAME_H
