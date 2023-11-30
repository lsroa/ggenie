#pragma once

#include "SDL2/SDL_render.h"
#include <map>
#include <vector>

class Store {
    std::map<std::string, SDL_Texture *> textures;
    // fonts
    // audio
  public:
    Store();
    ~Store();
    void AddTexture(const std::string &assetId, const std::string &path);
    SDL_Texture *GetTexture(const std::string &id);
};
