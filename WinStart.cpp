#include <Z.h>
#include <windowsx.h>

Game *p_Game;

LRESULT CALLBACK OurWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2) {
    switch (uint_Message) {
        case WM_CLOSE: {
            p_Game->StopRunning();
            break;
        };
        default: {
            if (uint_Message >= WM_MOUSEFIRST && uint_Message <= WM_MOUSELAST){
                switch (uint_Message){
                    case WM_LBUTTONUP:{
                        p_Game->p_scene->DoEvnt(MOUSE_UP, Z_MOUSELEFT, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    case WM_MBUTTONUP: {
                        p_Game->p_scene->DoEvnt(MOUSE_UP, Z_MOUSEMIDDLE, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    case WM_RBUTTONUP:{
                        p_Game->p_scene->DoEvnt(MOUSE_UP, Z_MOUSERIGHT, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    case WM_LBUTTONDOWN: {
                        p_Game->p_scene->DoEvnt(MOUSE_DOWN, Z_MOUSELEFT, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    case WM_MBUTTONDOWN: {
                        p_Game->p_scene->DoEvnt(MOUSE_DOWN, Z_MOUSEMIDDLE, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    case WM_RBUTTONDOWN: {
                        p_Game->p_scene->DoEvnt(MOUSE_DOWN, Z_MOUSERIGHT, new Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2)));
                        break;
                    };
                    default:
                        break;
                }
            }
            else if (uint_Message >= WM_KEYFIRST && uint_Message <= WM_KEYLAST) {
                switch (uint_Message) {
                    case WM_KEYUP: {
                        p_Game->p_scene->DoEvnt(KEYBOARD_UP, (uint8_t) parameter1, nullptr);
                    };
                    case WM_KEYDOWN: {
                        p_Game->p_scene->DoEvnt(KEYBOARD_DOWN, (uint8_t) parameter1, nullptr);
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpcmdline, int nCmdShow) {
    p_Game = Game::GetInstance();
    RECT wnd_size = {0, 0, (int)p_Game->g_width, (int)p_Game->g_height};
    AdjustWindowRectEx(&wnd_size, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, FALSE, WS_EX_CONTROLPARENT);
    HWND hWindow = NewWindow("Zhardas's DX9 Playground!", 0, 0, wnd_size.right-wnd_size.left, wnd_size.bottom-wnd_size.top);
    p_Game->Initialize(hInstance, hWindow);

    MSG msg_Message;
    while (p_Game->isRunning()) {
        if (PeekMessage(&msg_Message, hWindow, 0, 0, PM_REMOVE)) {
            DispatchMessage(&msg_Message);
        }
        p_Game->Loop();
    }

    DestroyWindow(hWindow);

    return 0;
};