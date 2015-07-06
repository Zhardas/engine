#include "Font.h"

Font::Font(std::string facename, int height, bool bold, bool italic) {
    g_font = NULL;
    DWORD weight = FW_NORMAL;
    if(bold)weight = FW_BOLD;
    D3DXCreateFont(
            Game::GetInstance()->g_device,     //D3D Device
            height,               //Font height
            0,                //Font width
            weight,        //Font Weight
            1,                //MipLevels
            italic,            //Italic
            DEFAULT_CHARSET,  //CharSet
            OUT_TT_ONLY_PRECIS, //OutputPrecision
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
