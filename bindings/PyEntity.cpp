#include "ECS/Components/sprite.h"
#include "ECS/ecs.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

void register_PyEntity(py::module_ &m) {
  py::class_<Entity>(m, "Entity")
      .def(py::init(                              //
          []() -> std::unique_ptr<Entity> {       //
            throw "Don't instance this directly"; //
          }))                                     //
      .def_property_readonly("id", &Entity::GetId)
      .def("add", [](Entity &self, py::object &component) -> Entity & {
        if (py::isinstance<Sprite>(component)) {
          self.AddComponent<Sprite>(component.cast<Sprite>());
        }
        return self;
      });
}
