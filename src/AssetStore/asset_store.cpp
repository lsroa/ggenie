#include "asset_store.h"
#include "Graphics/texture.h"
#include "Utils/logger.h"

#include <SDL2/SDL_render.h>
#include <SDL_image.h>
#include <string>

template <>
void SDLStore::AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::filesystem::path &path) {
  Logger::log("Adding texture from: " + path.string());
  SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

  this->textures.emplace(assetId, texture);
};

template <>
SDL_Texture *SDLStore::GetTexture(const std::string &id) {
  return this->textures[id];
};

template <>
void SDLStore::ClearTextures() {
  for (auto texture : textures) {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();
};

template <>
void GLStore::AddTexture(Renderer *renderer, const std::string &assetId, const std::filesystem::path &path) {
  Texture *texture = new Texture(path.c_str());
  this->textures.emplace(assetId, texture);
}

template <>
void GLStore::ClearTextures() {
  for (auto texture : textures) {
    delete texture.second;
  }
  this->textures.clear();
}

template <>
Texture *GLStore::GetTexture(const std::string &id) {
  return this->textures[id];
}
