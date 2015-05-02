#include <Z.h>

Game *p_Game;

LRESULT CALLBACK OurWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2) {
    switch (uint_Message) {
        case WM_KEYDOWN:
        case WM_CLOSE: {
            p_Game->StopRunning();
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
    p_Game = new Game();
    HWND hWindow = NewWindow("Zhardas's DX9 Playground!", 100, 100, (int) p_Game->g_width, (int) p_Game->g_height);
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
}