class Game;

#ifndef HEADACHE_GAME_H
#define HEADACHE_GAME_H

#include "Renderer.h"

#define VERSION_MAJOR @Headache_VERSION_MAJOR@
#define VERSION_MINOR @Headache_VERSION_MINOR@

class Game {
    Renderer *p_Renderer;
public:
    Game(HWND hWindow);

    bool isRunning;
    LPDIRECT3DDEVICE9 p_Device;

    LPDIRECT3DDEVICE9 InitializeDevice(HWND hWnd);

    void SetDeviceOptions();

    void Loop();
};


#endif //HEADACHE_GAME_H
