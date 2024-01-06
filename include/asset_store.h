#pragma once

#include "SDL2/SDL_render.h"
#include <map>

/// Store class
class Store {

    /*! @brief Map of textures */
    std::map<std::string, SDL_Texture *> textures;
    // fonts
    // audio
  public:
    Store() = default;
    ~Store() = default;
    /// Register textures
    void AddTexture(SDL_Renderer *renderer, const std::string &assetId,
                    const std::string &path);

    // Get texture by id
    SDL_Texture *GetTexture(const std::string &id);

    // Clear all textures
    void ClearTextures();
};
