Input::Input(Game *game) {
    p_game = game;

    p_direct_input = 0;
    p_keyboard = 0;
    p_mouse = 0;

    p_mouse_x = p_game->g_width / 2;
    p_mouse_y = p_game->g_height / 2;
}

void Input::Update() {
    ReadKeyboard();
    ReadMouse();
    ProcessInput();

    if (p_keyboard_state[DIK_ESCAPE] & 0x80) {
        std::cout << "Escape Key Down!\n";
    };

}

Input::~Input() {
    // Release the mouse.
    if (p_mouse) {
        p_mouse->Unacquire();
        p_mouse->Release();
        p_mouse = 0;
    }

    // Release the keyboard.
    if (p_keyboard) {
        p_keyboard->Unacquire();
        p_keyboard->Release();
        p_keyboard = 0;
    }

    // Release the main interface to direct input.
    if (p_direct_input) {
        p_direct_input->Release();
        p_direct_input = 0;
    }
}

void Input::ReadKeyboard() {
    HRESULT result = p_keyboard->GetDeviceState(sizeof(p_keyboard_state), (LPVOID) &p_keyboard_state);
    if (FAILED(result)) {
        // If the keyboard lost focus or was not acquired then try to get control back.
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            p_keyboard->Acquire();
        }
    }
}

void Input::ReadMouse() {
    HRESULT result = p_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID) &p_mouse_state);
    if (FAILED(result)) {
        // If the mouse lost focus or was not acquired then try to get control back.
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
            p_mouse->Acquire();
        }
    }
}

Position *Input::GetMousePosition() {
    return new Position(p_mouse_x, p_mouse_y);
}

void Input::ProcessInput() {
    // Update the location of the mouse cursor based on the change of the mouse location during the frame.
    p_mouse_x += p_mouse_state.lX;
    p_mouse_y += p_mouse_state.lY;

    // Ensure the mouse location doesn't exceed the screen width or height.
    if (p_mouse_x < 0) { p_mouse_x = 0; }
    if (p_mouse_y < 0) { p_mouse_y = 0; }

    if (p_mouse_x > p_game->g_width) { p_mouse_x = p_game->g_width; }
    if (p_mouse_y > p_game->g_height) { p_mouse_y = p_game->g_height; }

    return;
}

void Input::Initialize(HINSTANCE hinstance, HWND hwnd) {
    DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **) &p_direct_input, NULL);

    // Keyboard
    p_direct_input->CreateDevice(GUID_SysKeyboard, &p_keyboard, NULL);
    p_keyboard->SetDataFormat(&c_dfDIKeyboard);
    p_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    p_keyboard->Acquire();

    // Mouse
    p_direct_input->CreateDevice(GUID_SysMouse, &p_mouse, NULL);
    p_mouse->SetDataFormat(&c_dfDIMouse);
    p_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    p_mouse->Acquire();
}
