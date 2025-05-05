#include "ECS/Components/animation.h"

#include <pybind11/pybind11.h>
namespace py = pybind11;

void register_PyAnimation(py::module_ &m) {
  py::class_<Animation>(m, "Animation")
      .def(py::init([](int total_frames, int speed) { return Animation(total_frames, speed); }))
      .def_property(
          "current_frame", [](const Animation &self) { return self.current_frame; },
          [](Animation &self, int value) { self.current_frame = value; })
      .def_property_readonly("start_time", [](const Animation &self) { return self.start_time; })
      .def_property_readonly("total_frames", [](const Animation &self) { return self.total_frames; });
}
