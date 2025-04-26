#pragma once

#include "Graphics/sprite_renderer.h"
#include "Graphics/texture.h"

#include <filesystem>
#include <map>
#include <memory>

class Store {
  private:
    std::map<std::string, Texture *> textures;

  public:
    Store() = default;
    ~Store() = default;
    void AddTexture(std::shared_ptr<SpriteRenderer> renderer, const std::string &assetId,
                    const std::filesystem::path &path);
    Texture *GetTexture(const std::string &id);
    void ClearTextures();
};
