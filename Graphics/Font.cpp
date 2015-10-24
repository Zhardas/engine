#include "font.h"

Font::Font(std::string facename, int height, bool bold, bool italic) {
  ID3DXFont *pure_font_ = NULL;
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
      &pure_font_);         //ppFont
  font_ = removable_unique_ptr<ID3DXFont>(
      pure_font_,
      [](ID3DXFont *obj) {
        obj->Release();
      });
}
Size Font::size(std::string text) {
  RECT rcRect = {0, 0, 0, 0};
  // calculate required rect
  font_->DrawText(NULL, text.c_str(), text.length(), &rcRect, DT_CALCRECT,
                  D3DCOLOR_XRGB(0, 0, 0));

  // return size
  return Size(rcRect.right - rcRect.left, rcRect.bottom - rcRect.top);
}