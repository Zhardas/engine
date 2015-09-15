class TextureManager;
#ifndef HEADACHE_TEXTUREMANAGER_H
#define HEADACHE_TEXTUREMANAGER_H

#include <map>
#include <string>
#include <d3dx9.h>
#include <d3d9.h>
#include <sstream>
#include <iostream>
#include "game.h"

class TextureManager {
private:
    std::map<std::string, IDirect3DBaseTexture9 *> *textures_;
public:
    TextureManager();

    IDirect3DBaseTexture9 *LoadTexture(LPCSTR texture_name);
};

#endif //HEADACHE_TEXTUREMANAGER_H
