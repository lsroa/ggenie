#include "texture.h"
#include "Utils/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <OpenGL/gl.h>
#include <cassert>

Texture::Texture(const char *file_path) {
  if (!std::filesystem::exists(file_path)) {
    Logger::err("File not found: " + std::string(file_path));
    return;
  }
  this->file_path = std::string(file_path);

  unsigned int texture;
  glGenTextures(1, &texture);
  this->renderer_id = texture;

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  this->Load();
}

Texture::~Texture() {
  Logger::info("Deleting texture_" + std::to_string(this->renderer_id));
  glDeleteTextures(1, &this->renderer_id);
}

void Texture::Load() {

  int width, height;
  int depth;

  /* int TYPE = this->file_path.extension() == ".png" ? GL_RGBA : GL_RGB; */
  int TYPE = GL_RGB;

  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(file_path.c_str(), &width, &height, &depth, 0);

  if (data == NULL) {
    Logger::err("error loading image");
  }

  this->height = height;
  this->width = width;

  glTexImage2D(GL_TEXTURE_2D, 0, TYPE, width, height, 0, TYPE, GL_UNSIGNED_BYTE, data);
  Logger::info("freeing image " + this->file_path.filename().string());
  stbi_image_free(data);
}

void Texture::Bind(unsigned int slot) const {

  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, this->renderer_id);
}
