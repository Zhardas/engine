#ifndef HEADACHE_Z_H
#define HEADACHE_Z_H
#include <windows.h>
#include <windowsx.h>
#include "Game.h"
#include "Helper/input.h"
static Game* g_game;

LRESULT CALLBACK OurWindowProcedure(HWND han_Wind, UINT uint_Message, WPARAM parameter1, LPARAM parameter2);
HWND NewWindow(LPCTSTR str_Title, int int_XPos, int int_YPos, int int_Width, int int_Height);
#endif //HEADACHE_Z_H
