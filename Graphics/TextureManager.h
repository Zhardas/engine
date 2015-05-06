#ifndef HEADACHE_TEXTUREMANAGER_H
#define HEADACHE_TEXTUREMANAGER_H
#include <map>
#include <string>
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include <sstream>
#include <iostream>

class TextureManager {
private:
    Game*g_game;
    std::map<std::string, IDirect3DBaseTexture9*>* textures;
public:
    TextureManager(Game* parent);
    IDirect3DBaseTexture9 * GetTexture(LPCSTR texture_name);
};

#else
class TextureManager;
#endif //HEADACHE_TEXTUREMANAGER_H
