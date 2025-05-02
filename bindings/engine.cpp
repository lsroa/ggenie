#include "engine.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void register_PySprite(py::module_ &m);
void register_PyEntity(py::module_ &m);
void register_PyTransform(py::module_ &m);

PYBIND11_MODULE(gg, m) {
  m.doc() = "render module";
  m.def("create_entity", &PyGame::CreateEntity);

  py::class_<PyGame>(m, "Game")
      .def(py::init())          //
      .def("run", &PyGame::Run) //
      .def("create_entity", &PyGame::CreateEntity);

  register_PyEntity(m);
  register_PySprite(m);
  register_PyTransform(m);
}
