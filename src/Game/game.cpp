#include "game.h"
#include "GLFW/glfw3.h"
#include "Graphics/sprite_renderer.h"
#include "Utils/logger.h"

#include <glad/glad.h>

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

static void handle_error(int id, const char *description) {
  Logger::err(description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  /* if (key == GLFW_KEY_X && action == GLFW_PRESS) { */
  /*   this->wireframe_mode = !wireframe_mode; */
  /* } */
}

void Game::Init() {
  Logger::log("Game init");
  this->width = 320 * SCALE;
  this->height = 192 * SCALE;
  glfwSetErrorCallback(handle_error);
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  window = glfwCreateWindow(WIDTH, HEIGHT, "GG engine", NULL, NULL);

  if (window == NULL) {
    Logger::err("Failed to create GLFW window");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::err("Failed to initialize GLAD");
  }

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  renderer = std::make_shared<SpriteRenderer>();
  state = State::debug;
}

Game::Game() {
  Logger::info("Game spawn");
  registry = std::make_shared<Registry>();
  store = std::make_shared<Store>();
  event_bus = std::make_unique<EventBus>();
}

void Game::Run() {
  Setup();
  while (state == State::running || state == State::debug) {
    ProccessInput();
    Update();
    Render();
  }
}

void Game::Setup() {
  Logger::info("Game Setup");
  LoadLevel(0);
}
