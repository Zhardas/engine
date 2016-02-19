#include "console.h"
Console::Console() {
  float console_height = Game::instance()->height() / 3;
  set_visible(false);

  set_texture("dark_150.png");
  set_size(Game::instance()->width(), console_height);
  set_position(0.0f, Game::instance()->height() - console_height);

  textbox_ = new TextBox("Consolas", font_size, false, false);
  textbox_->text_->color_red_ = 0;
  textbox_->text_->color_green_ = 128;
  textbox_->text_->color_blue_ = 0;
  textbox_->set_texture("dark_150.png");
  textbox_->set_size(Game::instance()->width(), TEXTBOX_HEIGHT);
  textbox_->set_position(0.0f, Game::instance()->height() - console_height);
  Add(textbox_);

  events_key_up_.push_back([this](const uint8_t &key) {
    if (key == Z_CAROL) {  // carol
      set_visible(!visible_);
      textbox_->is_active_ = visible();
      return true;
    }
    return false;
  });
}
