#include "console.h"
Console::Console() {
  background_ = new TexturedQuad();
//  background_->set_texture("dark_150.png");
  background_->set_size(Game::instance()->width(), Game::instance()->height() / 3);
  background_->set_position(0.0f, Game::instance()->height());

  textbox_ = new TexturedQuad();
//  textbox_->set_texture("dark_150.png");
  textbox_->set_size(Game::instance()->width(), TEXTBOX_HEIGHT);
  textbox_->set_position(0.0f, Game::instance()->height() + Game::instance()->height() / 3 - TEXTBOX_HEIGHT);

  std::cout << "\n" << background_->position().x << "-" << background_->position().y << " " << background_->size().width << "-" << background_->size().height;

  text_ = new Text("Console", 24, false, false);
  text_->set_position((int) textbox_->position().x, (int) textbox_->position().y);
  text_->set_text("Testing!");
}
Console::~Console() {
  delete background_;
  delete textbox_;
  delete text_;
}
void Console::Add(DrawableLayer *drawable_layer, TextLayer *text_layer) {
  drawable_layer->Add(background_);
  drawable_layer->Add(textbox_);
  text_layer->Add(text_);
  std::cout << "\nTest!";
}
