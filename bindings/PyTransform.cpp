#include "ECS/Components/transform.h"
#include "glm/ext/vector_float2.hpp"
#include <pybind11/cast.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void register_PyTransform(py::module_ &m) {
  py::class_<Transform>(m, "Transform")
      .def(py::init([](py::kwargs kwargs) {
        auto x = kwargs["x"].cast<float>();
        auto y = kwargs["y"].cast<float>();
        return Transform(glm::vec2(x, y));
      }))
      .def(py::init([](py::tuple position) {
        if (position.size() != 2) {
          throw std::runtime_error("position must have 2 values");
        }
        float x = position[0].cast<float>();
        float y = position[1].cast<float>();
        return Transform(glm::vec2(x, y));
      }))
      .def_property(
          "x", [](const Transform &self) { return self.position.x; },
          [](Transform &self, float x) { self.position.x = x; })
      .def_property(
          "y", [](const Transform &self) { return self.position.y; },
          [](Transform &self, float y) { self.position.y = y; });
};
