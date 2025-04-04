#include "Graphics/pyrenderer.h"

#include <_stdlib.h>
#include <pybind11/embed.h>

namespace py = pybind11;

int main() {
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

  return 0;
}
