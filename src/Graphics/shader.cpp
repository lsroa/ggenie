#include "shader.h"
#include "Utils/files.h"
#include "Utils/logger.h"
#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"
#include <initializer_list>

Shader::Shader(std::initializer_list<std::string> &&shaders) {
  Logger::info("Shader spawn");
  int success;
  char info[512];

  this->renderer_id = glCreateProgram();
  if (this->renderer_id == 0) {
    Logger::err("Failed to create shader program");
    assert(false);
  }

  for (const auto &file_path : shaders) {
    ShaderUnit shader(file_path.c_str());
    shader.Compile();

    Logger::info("Attaching " + shader.file_path.string());
    glAttachShader(this->renderer_id, shader.renderer_id);
  }

  Logger::info("Linking program_" + std::to_string(this->renderer_id));
  glLinkProgram(renderer_id);

  glGetProgramiv(renderer_id, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(renderer_id, 512, NULL, info);
    Logger::err("Error linking program_" + std::to_string(this->renderer_id) + "\n" + std::string(info));
    assert(false);
  }
}

void Shader::Bind() const {
  Logger::info("Binding shader " + std::to_string(this->renderer_id));
  glUseProgram(renderer_id);
}

void Shader::SetMat4(const char *name, const glm::mat4 &matrix) const {
  glUniformMatrix4fv(glGetUniformLocation(this->renderer_id, name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1f(const char *name, float value) const {
  glUniform1f(glGetUniformLocation(this->renderer_id, name), value);
}

void Shader::SetUniformi(const char *name, unsigned int value) const {
  glUniform1i(glGetUniformLocation(this->renderer_id, name), value);
}

Shader::~Shader() {
  Logger::info("Deleting program_" + std::to_string(this->renderer_id));
  glDeleteProgram(renderer_id);
}

ShaderUnit::ShaderUnit(const std::filesystem::path &file_path) {
  if (!std::filesystem::exists(file_path)) {
    Logger::err("File not found" + file_path.string());
    throw "File not found";
  }

  this->file_path = std::filesystem::path(file_path);
  if (this->file_path.extension() == ".vert") {
    this->renderer_id = glCreateShader(GL_VERTEX_SHADER);
  }
  if (this->file_path.extension() == ".frag") {
    this->renderer_id = glCreateShader(GL_FRAGMENT_SHADER);
  }
  Logger::log("Shader created shader_" + std::to_string(this->renderer_id));
}

void ShaderUnit::Compile() {
  int success;
  char info[512];

  std::string sourceCode = readFile(this->file_path.c_str());
  const char *source = sourceCode.c_str();
  glShaderSource(this->renderer_id, 1, &source, NULL);

  Logger::log("Compiling " + this->file_path.string());
  glCompileShader(this->renderer_id);

  glGetShaderiv(this->renderer_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->renderer_id, 512, NULL, info);
    Logger::err("Error compiling " + file_path.string() + "' shader\n" + info);
  }
}

ShaderUnit::~ShaderUnit() {
  Logger::info("Deleting shader_" + std::to_string(this->renderer_id));
  glDeleteShader(renderer_id);
}
