#include "renderer.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 600
#define HEIGHT 600

bool wireframe_mode = 0;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  if (key == GLFW_KEY_X && action == GLFW_PRESS) {
    wireframe_mode = !wireframe_mode;
  }
}

void Renderer::Init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window = glfwCreateWindow(WIDTH, HEIGHT, "Open GL", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
}

void Renderer::render(VertexArray &vao, IndexBuffer &ebo) {

  if (wireframe_mode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  vao.Bind();
  ebo.Bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::Run() {

  /* Quad */
  float vertices[] = {
      // clang-format off
      // Position         | Texture coordinates
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left  
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right 
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
      // clang-format on
  };

  GLuint indices[] = {0, 1, 3, 0, 2, 3};

  /* Upload the vertices data*/
  VertexBuffer vbo(vertices, sizeof(vertices));
  /* Upload the order of those vertices with indices */
  IndexBuffer ebo(indices, sizeof(indices));

  // Set the attributes and the layout of the data
  VertexBufferLayout layout;

  layout.AddAttribute<float>("position", 3);
  layout.AddAttribute<float>("texture", 2);

  VertexArray vao;
  vao.AddLayout(vbo, layout);

  /* deselect buffer, element_buffer and vertex array
   * by selecting the special 0 id for each target
   * */
  vbo.Unbind();
  ebo.Unbind();
  vao.Unbind();

  Texture profile("profile.jpeg");
  Texture alto("alto.jpeg");

  Shader shader({"./shaders/color.frag", "./shaders/default.vert"});
  shader.Bind();
  shader.SetUniformi("texture_1", 0);
  shader.SetUniformi("texture_2", 1);

  glm::mat4 view(1.0f);
  glm::mat4 projection(1.0f);

  projection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
  shader.SetMat4("projection", projection);
  shader.SetMat4("view", view);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.64, 0.64, 0.65, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = (float)glfwGetTime();
    shader.SetUniform1f("iTime", time);

    renderTexture(profile, shader, glm::vec2(100, 100));
    render(vao, ebo);

    renderTexture(alto, shader, glm::vec2(200, 100));
    render(vao, ebo);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
}

void renderTexture(const Texture &texture, const Shader &shader, const glm::vec2 &position) {
  texture.Bind(0);
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(position, 0));
  model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
  model = glm::scale(model, glm::vec3(texture.width, texture.height, 0));

  shader.SetMat4("model", model);
}
