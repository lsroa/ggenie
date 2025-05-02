#include "ECS/Components/sprite.h"
#include <pybind11/pybind11.h>

#include <glm/vec2.hpp>

namespace py = pybind11;

void register_PySprite(py::module_ &m) {
  py::class_<Sprite>(m, "Sprite")
      .def(py::init([](py::kwargs kwargs) {
        auto rect = kwargs["rect"].cast<py::tuple>();
        auto id = kwargs["id"].cast<std::string>();
        auto scale = kwargs["scale"].cast<py::tuple>();

        return Sprite(id, rect[0].cast<int>(), rect[1].cast<int>(), rect[2].cast<int>(), rect[3].cast<int>(),
                      glm::vec2(scale[0].cast<float>(), scale[1].cast<float>()));
      }))
      .def(py::init([](std::string id, py::tuple rect) {
        if (rect.size() != 4) {
          throw std::runtime_error("rect must have 4 values");
        }

        return Sprite(id, rect[0].cast<int>(), rect[1].cast<int>(), rect[2].cast<int>(), rect[3].cast<int>());
      }))
      .def_property_readonly("id", [](const Sprite &self) { return self.id; })
      .def_property(
          "scale",
          [](const Sprite &self) { //
            return py::make_tuple(self.scale.x, self.scale.y);
          },
          [](Sprite &self, py::tuple scale) { self.scale = glm::vec2(scale[0].cast<float>(), scale[1].cast<float>()); })
      .def_property(
          "rect",
          [](const Sprite &self) {                                 //
            return py::make_tuple(self.x, self.y, self.w, self.h); //
          },
          [](Sprite &self, py::tuple rect) {
            if (rect.size() != 4) {
              std::runtime_error("rect must have 4 values");
            }
            self.x = rect[0].cast<int>();
            self.y = rect[1].cast<int>();
            self.w = rect[2].cast<int>();
            self.h = rect[3].cast<int>();
          });
}
