#include "texture_manager.h"

TextureManager::TextureManager() {
    textures_ = new std::map<std::string, IDirect3DBaseTexture9 *>();
}

IDirect3DBaseTexture9 *TextureManager::LoadTexture(LPCSTR texture_name) {
    std::stringstream path;
    path << "resources\\textures\\" << texture_name;
    std::map<std::string, IDirect3DBaseTexture9 *>::iterator it = textures_->find(texture_name);
    if (it != textures_->end()) {
        return textures_->at(texture_name);
    } else {
        IDirect3DTexture9 *texture = NULL;
        HRESULT result = D3DXCreateTextureFromFile(Game::instance()->device_, path.str().c_str(), &texture);
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
        textures_->insert(std::pair<std::string, IDirect3DBaseTexture9 *>(texture_name, texture));
        return texture;
    }
}
