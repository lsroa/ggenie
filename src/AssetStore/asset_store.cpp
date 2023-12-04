#include "asset_store.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include <string>

void Store::AddTexture(
    /// Sdl renderer
    SDL_Renderer *renderer,
    /// Uniqure id
    const std::string &assetId,
    /// Path to the asset
    const std::string &path) {

  SDL_Surface *surface = IMG_Load(path.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

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
