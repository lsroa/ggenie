#include "renderer.h"
#include "index_buffer.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <glad/glad.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIDTH 800
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

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
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
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left  
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right 
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
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

  Texture tilemap("./assets/tilemap_1.png");

  Shader shader({"./assets/shaders/color.frag", "./assets/shaders/default.vert"});
  shader.Bind();
  shader.SetUniformi("texture_1", 0);

  glm::mat4 projection(1.0f);

  projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
  shader.SetMat4("projection", projection);

  glm::vec3 cameraConfig(0, 0, 0);

  while (!glfwWindowShouldClose(window)) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    {
      ImGui::NewFrame();
      ImGui::Begin("Settings");
      ImGui::Text("Camera");
      ImGui::InputFloat3("translation", &cameraConfig.x);
      ImGui::End();
    }

    ImGui::Render();

    glClearColor(0.64, 0.64, 0.65, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = (float)glfwGetTime();

    glm::mat4 view = glm::translate(glm::mat4(1), cameraConfig);
    shader.SetUniform1f("iTime", time);
    shader.SetMat4("view", view);

    renderTexture(tilemap, shader, glm::vec2(WIDTH / 2, HEIGHT / 2));
    render(vao, ebo);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
}

void Renderer::renderTexture(const Texture &texture, const Shader &shader, const glm::vec2 &position) {
  texture.Bind(0);
  glm::mat4 model(1.0f);
  model = glm::translate(model, glm::vec3(position, 0));
  model = glm::scale(model, glm::vec3(texture.width, texture.height, 0));

  shader.SetMat4("model", model);
}
