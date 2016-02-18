#include "./input_manager.h"

InputManager::InputManager() {
  mouse_position_ = Position(0, 0);
}
void InputManager::ParseMessage(UINT message, WPARAM parameter1, LPARAM parameter2) {
  auto scene = Game::instance()->scene_;
  if (!scene)return;
  if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) {
    mouse_position_ = Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2));
    mouse_position_.y = Game::instance()->height() - mouse_position_.y;
    switch (message) {
      case WM_MOUSEMOVE: {
        scene->EventCall(MOUSE_MOVE, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_LBUTTONUP: {
        scene->EventCall(MOUSE_UP, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_MBUTTONUP: {
        scene->EventCall(MOUSE_UP, MOUSE_MIDDLE, &mouse_position_);
      };
        break;
      case WM_RBUTTONUP: {
        scene->EventCall(MOUSE_UP, MOUSE_RIGHT, &mouse_position_);
      };
        break;
      case WM_LBUTTONDOWN: {
        scene->EventCall(MOUSE_DOWN, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_MBUTTONDOWN: {
        scene->EventCall(MOUSE_DOWN, MOUSE_MIDDLE, &mouse_position_);
      };
        break;
      case WM_RBUTTONDOWN: {
        scene->EventCall(MOUSE_DOWN, MOUSE_RIGHT, &mouse_position_);
      };
        break;
      default:
        break;
    }
  } else if (message >= WM_KEYFIRST && message <= WM_KEYLAST) {
    switch (parameter1) {
      case VK_LEFT:
      case VK_RIGHT:
      case VK_UP:
      case VK_DOWN:
      case VK_DELETE:
        switch (message) {
          case WM_KEYUP: {
            scene->EventCall(KEYBOARD_UP, static_cast<uint8_t>(parameter1), nullptr);
          };
            break;
          case WM_KEYDOWN: {
            scene->EventCall(KEYBOARD_DOWN, static_cast<uint8_t>(parameter1), nullptr);
          };
            break;
          default:
            break;
        }
      case VK_HOME:
      case VK_END:
      case VK_INSERT:
      case Z_CAROL:
      case VK_F1:
      case VK_F2:
      case VK_F3:
      case VK_F4:
      case VK_F5:
      case VK_F6:
      case VK_F7:
      case VK_F8:
      case VK_F9:
      case VK_F10:
      case VK_F11:
      case VK_F12:
        if (message == WM_KEYUP) {
          scene->EventCall(KEYBOARD_UP, static_cast<uint8_t>(parameter1), nullptr);
        }
        break;
      default:
        break;
    }
  }
  if (message == WM_CHAR) {
    if (parameter1 != 142) {
      scene->EventCall(KEYBOARD_DOWN, static_cast<uint8_t>(parameter1), nullptr);
    }
  }
}

