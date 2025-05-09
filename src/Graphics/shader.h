#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include <filesystem>
#include <string>

class ShaderUnit {
  public:
    std::filesystem::path file_path;
    unsigned int renderer_id;
    ShaderUnit(const std::filesystem::path &file_path);
    ~ShaderUnit();

    void Compile();
};

class Shader {
  public:
    unsigned int renderer_id;
    Shader(std::initializer_list<std::string> &&file_path);
    ~Shader();
    void SetUniform1f(const char *name, float value) const;
    void SetUniformi(const char *name, unsigned int slot) const;
    void SetMat4(const char *name, const glm::mat4 &matrix) const;
    void SetVec4(const char *name, const glm::vec4 &value) const;
    void SetVec2(const char *name, const glm::vec2 &value) const;
    void Bind() const;
};
