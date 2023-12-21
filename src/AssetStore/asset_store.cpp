#include "asset_store.h"
#include "../Logger/logger.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include <string>

void Store::AddTexture(
    /// Sdl renderer
    SDL_Renderer *renderer,
    /// Uniqure id
    const std::string &assetId,
    /// Path to the asset
    const std::string &path) {

  Logger::log("Adding texture from: " + path);
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  this->textures.emplace(assetId, texture);
};

SDL_Texture *Store::GetTexture(
    /// Unique id
    const std::string &id) {
  return this->textures[id];
};

void Store::ClearTextures() {
  for (auto texture : textures) {
    // remove the texture from memory
    SDL_DestroyTexture(texture.second);
  }
  // clear the map
  textures.clear();
};
