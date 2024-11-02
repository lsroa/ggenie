#pragma once

#include "SDL2/SDL_render.h"
#include <filesystem>
#include <map>

class Store {
  private:
    std::map<std::string, SDL_Texture *> textures;

  public:
    Store() = default;
    ~Store() = default;
    void AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::filesystem::path &path);
    SDL_Texture *GetTexture(const std::string &id);
    void ClearTextures();
};
