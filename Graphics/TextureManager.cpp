#include "TextureManager.h"

TextureManager::TextureManager() {
    g_game = Game::GetInstance();
    textures = new std::map<std::string, IDirect3DBaseTexture9 *>();
}

IDirect3DBaseTexture9 *TextureManager::GetTexture(LPCSTR texture_name) {
    std::stringstream path;
    path << "resources\\textures\\" << texture_name;
    std::map<std::string, IDirect3DBaseTexture9 *>::iterator it = textures->find(texture_name);
    if (it != textures->end()) {
        return textures->at(texture_name);
    } else {
        IDirect3DTexture9 *texture = NULL;
        HRESULT result = D3DXCreateTextureFromFile(g_game->g_device, path.str().c_str(), &texture);
        switch (result) {
            case D3D_OK:
                break;
            case D3DERR_NOTAVAILABLE:
                std::cout << "Not available!\n";
                break;
            case D3DERR_OUTOFVIDEOMEMORY:
                std::cout << "Out of video memory!\n";
                break;
            case D3DERR_INVALIDCALL:
                std::cout << "Invalid call!\n";
                break;
            case D3DXERR_INVALIDDATA:
                std::cout << "Invalid data!\n";
                break;
            case E_OUTOFMEMORY:
                std::cout << "Out of memory!!\n";
                break;
            default:
                std::cout << "Something went really wrong with texture initialization!\n";
                break;
        }
        textures->insert(std::pair<std::string, IDirect3DBaseTexture9 *>(texture_name, texture));
        return texture;
    }
}
