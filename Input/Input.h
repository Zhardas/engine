
a class Input;
#ifndef HEADACHE_INPUT_H
#define HEADACHE_INPUT_H

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif // DIRECTINPUT_VERSION

#include <dx/dinput.h>
#include <Helper/Types/Position.h>
#include <Game.h>
#include <iostream>

class Input {
private:
    LPDIRECTINPUTDEVICE8 p_keyboard;
    LPDIRECTINPUTDEVICE8 p_mouse;
    LPDIRECTINPUT8 p_direct_input;

    unsigned char p_keyboard_state[256];
    DIMOUSESTATE p_mouse_state;

    int p_mouse_x, p_mouse_y;

    Game* p_game;

    void ReadKeyboard();
    void ReadMouse();
    void ProcessInput();
public:
    Input(Game*);
    ~Input();
    void Update();
    void Initialize(HINSTANCE, HWND);
    Position* GetMousePosition();
};


#endif //HEADACHE_INPUT_H
