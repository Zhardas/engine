#ifndef Z_INPUT
#define Z_INPUT
enum Event { MOUSE_UP, MOUSE_DOWN, MOUSE_MOVE, KEYBOARD_UP, KEYBOARD_DOWN };
enum MouseButton { MOUSE_LEFT, MOUSE_MIDDLE, MOUSE_RIGHT};

#define Z_0	0x30
#define Z_1	0x31
#define Z_2	0x32
#define Z_3	0x33
#define Z_4	0x34
#define Z_5	0x35
#define Z_6	0x36
#define Z_7	0x37
#define Z_8	0x38
#define Z_9	0x39

#define Z_A	0x041
#define Z_B	0x042
#define Z_C	0x043
#define Z_D	0x044
#define Z_E	0x045
#define Z_F	0x046
#define Z_G	0x047
#define Z_H	0x048
#define Z_I	0x049
#define Z_J	0x04A
#define Z_K	0x04B
#define Z_L	0x04C
#define Z_M	0x04D
#define Z_N	0x04E
#define Z_O	0x04F
#define Z_P	0x050
#define Z_Q	0x051
#define Z_R    0x052
#define Z_S	0x053
#define Z_T	0x054
#define Z_U	0x055
#define Z_V	0x056
#define Z_W	0x057
#define Z_X	0x058
#define Z_Y	0x059
#define Z_Z	0x05A

#define Z_LBUTTON      = 01H
#define Z_RBUTTON      = 02H
#define Z_CANCEL       = 03H
#define Z_BACK         = 08H
#define Z_TAB          = 09H
#define Z_CLEAR        = 0cH
#define Z_RETURN       = 0dH
#define Z_SHIFT        = 10H
#define Z_CONTROL      = 11H   ; CTRL KEY
#define Z_MENU         = 12H	; ALT KEY
#define Z_PAUSE        = 13H
#define Z_CAPITAL      = 14H
#define Z_ESCAPE       = 1bH
#define Z_SPACE        = 20H

#define Z_PRIOR        = 21H
#define Z_NEXT         = 22H
#define Z_END          = 23H
#define Z_HOME         = 24H
#define Z_LEFT         = 25H
#define Z_UP           = 26H
#define Z_RIGHT        = 27H
#define Z_DOWN         = 28H

#define Z_PRINT        = 2aH
#define Z_EXECUTE      = 2bH
#define Z_SNAPSHOT     = 2ch   ; Printscreen key
#define Z_INSERT       = 2dH
#define Z_DELETE       = 2eH
#define Z_HELP         = 2fH

#define Z_NUMPAD0      = 60H
#define Z_NUMPAD1      = 61H
#define Z_NUMPAD2      = 62H
#define Z_NUMPAD3      = 63H
#define Z_NUMPAD4      = 64H
#define Z_NUMPAD5      = 65H
#define Z_NUMPAD6      = 66H
#define Z_NUMPAD7      = 67H
#define Z_NUMPAD8      = 68H
#define Z_NUMPAD9      = 69H
#define Z_MULTIPLY     = 6AH
#define Z_ADD          = 6BH
#define Z_SEPARATER    = 6CH
#define Z_SUBTRACT     = 6DH
#define Z_DECIMAL      = 6EH
#define Z_DIVIDE       = 6FH

#define Z_F1           = 70H
#define Z_F2           = 71H
#define Z_F3           = 72H
#define Z_F4           = 73H
#define Z_F5           = 74H
#define Z_F6           = 75H
#define Z_F7           = 76H
#define Z_F8           = 77H
#define Z_F9           = 78H
#define Z_F10          = 79H
#define Z_F11          = 7aH
#define Z_F12          = 7bH
#define Z_F13          = 7cH
#define Z_F14          = 7dH
#define Z_F15          = 7eH
#define Z_F16          = 7fH
#define Z_F17          = 80H
#define Z_F18          = 81H
#define Z_F19          = 82H
#define Z_F20          = 83H
#define Z_F21          = 84H
#define Z_F22          = 85H
#define Z_F23          = 86H
#define Z_F24          = 87H

#define Z_NUMLOCK      = 90H
#define Z_SCROLL       = 91H

#endif //Z_INPUT
