#include <Z.h>

LRESULT CALLBACK OurWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2) {
    switch (uint_Message) {
        case WM_CLOSE: {
            g_game->StopRunning();
            break;
        };
        default: {
            if (uint_Message >= WM_MOUSEFIRST && uint_Message <= WM_MOUSELAST){
                Position pos = {GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)};
                switch (uint_Message){
                    case WM_MOUSEMOVE: {
                        g_game->g_mouse_position = &pos;
                        g_game->g_scene->DoEvnt(MOUSE_MOVE, MOUSE_LEFT, &pos);
                        break;
                    };
                    case WM_LBUTTONUP:{
                        g_game->g_scene->DoEvnt(MOUSE_UP, MOUSE_LEFT, &pos);
                        break;
                    };
                    case WM_MBUTTONUP: {
                        g_game->g_scene->DoEvnt(MOUSE_UP, MOUSE_MIDDLE, &pos);
                        break;
                    };
                    case WM_RBUTTONUP:{
                        g_game->g_scene->DoEvnt(MOUSE_UP, MOUSE_RIGHT, &pos);
                        break;
                    };
                    case WM_LBUTTONDOWN: {
                        g_game->g_scene->DoEvnt(MOUSE_DOWN, MOUSE_LEFT, &pos);
                        break;
                    };
                    case WM_MBUTTONDOWN: {
                        g_game->g_scene->DoEvnt(MOUSE_DOWN, MOUSE_MIDDLE, &pos);
                        break;
                    };
                    case WM_RBUTTONDOWN: {
                        g_game->g_scene->DoEvnt(MOUSE_DOWN, MOUSE_RIGHT, &pos);
                        break;
                    };
                    default:
                        break;
                }
            }
            else if (uint_Message >= WM_KEYFIRST && uint_Message <= WM_KEYLAST) {
                switch (uint_Message) {
                    case WM_KEYUP: {
                        g_game->g_scene->DoEvnt(KEYBOARD_UP, static_cast<uint8_t>(parameter1), nullptr);
                        break;
                    };
                    case WM_KEYDOWN: {
                        g_game->g_scene->DoEvnt(KEYBOARD_DOWN, static_cast<uint8_t>(parameter1), nullptr);
                        break;
                    };
                    default:
                        break;
                }
            }
            break;
        };
    }
    return DefWindowProc(han_Wind, uint_Message, parameter1, parameter2);
}

HWND NewWindow(LPCTSTR str_Title, int int_XPos, int int_YPos, int int_Width, int int_Height) {
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
    wnd_Structure.lpszClassName = "WindowClassName";
    wnd_Structure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wnd_Structure);

    return CreateWindowEx(WS_EX_CONTROLPARENT, "WindowClassName", str_Title,
                          WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, int_XPos, int_YPos,
                          int_Width, int_Height, NULL, NULL, GetModuleHandle(NULL), NULL);
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
    g_game = Game::GetInstance();
    RECT wnd_size = {0, 0, g_game->g_width, g_game->g_height};
    AdjustWindowRectEx(&wnd_size, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, FALSE, WS_EX_CONTROLPARENT);
    HWND hWindow = NewWindow("Zhardas's DX9 Playground!", 0, 0, wnd_size.right-wnd_size.left, wnd_size.bottom-wnd_size.top);
    g_game->Initialize(hWindow);

    MSG msg_Message;
    while (g_game->isRunning()) {
        if (PeekMessage(&msg_Message, hWindow, 0, 0, PM_REMOVE)) {
            DispatchMessage(&msg_Message);
        }
        g_game->Loop();
    }

    DestroyWindow(hWindow);

    return 0;
}
