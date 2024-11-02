#include "asset_store.h"
#include "Utils/logger.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <string>

void Store::AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::filesystem::path &path) {
  Logger::log("Adding texture from: " + path.string());
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  this->textures.emplace(assetId, texture);
};

SDL_Texture *Store::GetTexture(const std::string &id) {
  return this->textures[id];
};

void Store::ClearTextures() {
  for (auto texture : textures) {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();
};
