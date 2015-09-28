#include "console.h"
Console::Console() {
  float console_height = Game::instance()->height() / 3;
  int font_size = 16;
  auto padding = 5;

  background_ = new TexturedQuad();
  background_->set_texture("dark_150.png");
  background_->set_size(Game::instance()->width(), console_height);
  background_->set_position(0.0f, Game::instance()->height() - console_height);

  textbox_ = new TexturedQuad();
  textbox_->set_texture("dark_150.png");
  textbox_->set_size(Game::instance()->width(), TEXTBOX_HEIGHT);
  textbox_->set_position(0.0f, Game::instance()->height() - console_height);

  text_ = new Text("Consolas", font_size, false, false);
  text_->set_position((int) textbox_->position().x + padding, (int) (console_height - font_size - padding/2));
  text_->set_text("Testing!");
  text_->color_red_ = 0;
  text_->color_blue_ = 0;
  text_->color_green_ = 128;
  text_->reset_size();
}
Console::~Console() {
  delete background_;
  delete textbox_;
  delete text_;
}