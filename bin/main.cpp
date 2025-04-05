#include "Graphics/renderer.h"
#include "engine.h"

#include <_stdlib.h>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char *argv[]) {
  if (argc > 1 && std::string(argv[1]) == "py") {
    setenv("PYTHONPATH", ".", 1);
    py::scoped_interpreter guard{};

    try {
      py::module_ main_module = py::module_::import("main");
      py::object setup_func = main_module.attr("setup");

      PyGame game;
      setup_func(py::cast(&game));

      game.Run();

    } catch (const py::error_already_set &e) {
      std::cerr << e.what();
    }
  }

  if (argc > 1 && std::string(argv[1]) == "renderer") {
    Renderer renderer;
    renderer.Init();
    renderer.Run();
  }

  return 0;
}
