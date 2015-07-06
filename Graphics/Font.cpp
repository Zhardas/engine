#include "Font.h"

Font::Font(std::string facename, int height) {
    g_font = NULL;

    D3DXCreateFont(
            Game::GetInstance()->g_device,     //D3D Device
            height,               //Font height
            0,                //Font width
            FW_NORMAL,        //Font Weight
            1,                //MipLevels
            false,            //Italic
            DEFAULT_CHARSET,  //CharSet
            OUT_DEFAULT_PRECIS, //OutputPrecision
            ANTIALIASED_QUALITY, //Quality
            DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
            facename.c_str(),          //pFacename,
            &g_font);         //ppFont
}

Font::~Font() {
    if(g_font){
        g_font->Release();
        g_font=NULL;
    }
}
