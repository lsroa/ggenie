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
