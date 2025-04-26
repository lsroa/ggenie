#include "asset_store.h"
#include "Graphics/texture.h"
#include "Utils/logger.h"

#include <string>

void Store::AddTexture(std::shared_ptr<SpriteRenderer> renderer, const std::string &assetId,
                       const std::filesystem::path &path) {
  Logger::log("Adding texture from: " + path.string());
  Texture *texture = new Texture(path.c_str());
  this->textures.emplace(assetId, texture);
}

void Store::ClearTextures() {
  for (auto texture : textures) {
    delete texture.second;
  }
  this->textures.clear();
}

Texture *Store::GetTexture(const std::string &id) {
  return this->textures[id];
}
