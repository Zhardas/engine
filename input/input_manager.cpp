#include "./input_manager.h"

InputManager::InputManager() {
  mouse_position_ = Position(0, 0);
}
void InputManager::ParseMessage(UINT message, WPARAM parameter1, LPARAM parameter2) {
  if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) {
    mouse_position_ = Position(GET_X_LPARAM(parameter2), GET_Y_LPARAM(parameter2));
    mouse_position_.y = Game::instance()->height() - mouse_position_.y;
    switch (message) {
      case WM_MOUSEMOVE: {
        Game::instance()->scene_->EventCall(MOUSE_MOVE, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_LBUTTONUP: {
        Game::instance()->scene_->EventCall(MOUSE_UP, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_MBUTTONUP: {
        Game::instance()->scene_->EventCall(MOUSE_UP, MOUSE_MIDDLE, &mouse_position_);
      };
        break;
      case WM_RBUTTONUP: {
        Game::instance()->scene_->EventCall(MOUSE_UP, MOUSE_RIGHT, &mouse_position_);
      };
        break;
      case WM_LBUTTONDOWN: {
        Game::instance()->scene_->EventCall(MOUSE_DOWN, MOUSE_LEFT, &mouse_position_);
      };
        break;
      case WM_MBUTTONDOWN: {
        Game::instance()->scene_->EventCall(MOUSE_DOWN, MOUSE_MIDDLE, &mouse_position_);
      };
        break;
      case WM_RBUTTONDOWN: {
        Game::instance()->scene_->EventCall(MOUSE_DOWN, MOUSE_RIGHT, &mouse_position_);
      };
        break;
      default:
        break;
    }
  } else if (message >= WM_KEYFIRST && message <= WM_KEYLAST) {
    switch (message) {
      case WM_KEYUP: {
        Game::instance()->scene_->EventCall(KEYBOARD_UP, static_cast<uint8_t>(parameter1), nullptr);
      };
        break;
      case WM_KEYDOWN: {
        Game::instance()->scene_->EventCall(KEYBOARD_DOWN, static_cast<uint8_t>(parameter1), nullptr);
      };
        break;
      default:
        break;
    }
  }
}
