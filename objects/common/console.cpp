#include "console.h"
Console::Console() {
  float console_height = Game::instance()->height() / 3;
  int font_size = 16;
  set_visible(false);

  background_ = std::make_unique<TexturedQuad>();
  background_->set_texture("dark_150.png");
  background_->set_size(Game::instance()->width(), console_height);
  background_->set_position(0.0f, Game::instance()->height() - console_height);
  Add(background_.get());

  textbox_ = std::make_unique<TextBox>("Consolas", font_size, false, false);
  textbox_->text_->color_red_ = 0;
  textbox_->text_->color_green_ = 128;
  textbox_->text_->color_blue_ = 0;
  textbox_->text_->set_text("testing");
  textbox_->background_->set_texture("dark_150.png");
  textbox_->set_size(Game::instance()->width(), TEXTBOX_HEIGHT);
  textbox_->set_position(0.0f, Game::instance()->height() - console_height);
  Add(textbox_.get());

  events_key_up_.push_back([&](const uint8_t &key){
    if(key == 222){ // carol
      set_visible(!visible_);
      textbox_->is_active_ = visible();
      return true;
    }
    return false;
  });
}