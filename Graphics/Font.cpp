#include "font.h"

Font::Font(std::string facename, int height, bool bold, bool italic) {
  font_ = NULL;
  DWORD weight = FW_NORMAL;
  if (bold)weight = FW_BOLD;
  D3DXCreateFont(
      Game::instance()->device_,     //D3D Device
      height,               //font height
      0,                //font width
      weight,        //font Weight
      1,                //MipLevels
      italic,            //Italic
      DEFAULT_CHARSET,  //CharSet
      OUT_TT_ONLY_PRECIS, //OutputPrecision
      ANTIALIASED_QUALITY, //Quality
      DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
      facename.c_str(),          //pFacename,
      &font_);         //ppFont
}

Font::~Font() {
  if (font_) {
    font_->Release();
    font_ = NULL;
  }
}
