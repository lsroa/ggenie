#pragma once
#include <filesystem>

class Texture {
  public:
    unsigned int renderer_id;
    unsigned int width;
    unsigned int height;
    std::filesystem::path file_path;

    Texture(const char *file_path);
    ~Texture();
    void Bind(unsigned int v = 0) const;

  private:
    void Load();
};

inline auto operator<<(std::ostream &os, const Texture &texture) -> std::ostream & {
  std::string texture_str =
      std::format(" Texture{{ id: {}, ({}x{}) }} ", texture.renderer_id, texture.width, texture.height);
  os << texture_str;
  return os;
}
