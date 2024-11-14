#pragma once

#include "Graphics/renderer.h"

#include "SDL2/SDL_render.h"

#include <filesystem>
#include <map>

template <typename TextureType, typename Renderer>
class Store {
  private:
    std::map<std::string, TextureType *> textures;

  public:
    Store() = default;
    ~Store() = default;
    void AddTexture(Renderer *renderer, const std::string &assetId, const std::filesystem::path &path);
    TextureType *GetTexture(const std::string &id);
    void ClearTextures();
};

typedef Store<Texture, Renderer> GLStore;
typedef Store<SDL_Texture, SDL_Renderer> SDLStore;
