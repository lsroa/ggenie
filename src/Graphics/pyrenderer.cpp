#include "ECS/Components/sprite.h"
#include "ECS/ecs.h"
#include "Game/sdl_game.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

class PyGame {
  public:
    std::shared_ptr<SDLGame> m_Game;
    PyGame() {
      m_Game = std::make_shared<SDLGame>();
      m_Game->Init();
    }

    void Run() {
      m_Game->Run();
    }

    Entity CreateEntity() {
      return m_Game->registry->CreateEntity();
    }
};

PYBIND11_MODULE(gg, m) {
  m.doc() = "render module";
  m.def("create_entity", &PyGame::CreateEntity);

  py::class_<PyGame>(m, "Game")
      .def(py::init())          //
      .def("run", &PyGame::Run) //
      .def("create_entity", &PyGame::CreateEntity);

  py::class_<Sprite>(m, "Sprite")
      .def(py::init([](py::kwargs kwargs) {
        auto rect = kwargs["rect"].cast<py::tuple>();
        auto id = kwargs["id"].cast<std::string>();
        return Sprite(id, rect[0].cast<int>(), rect[1].cast<int>(), rect[2].cast<int>(), rect[3].cast<int>());
      }))
      .def(py::init([](std::string id, py::tuple rect) {
        if (rect.size() != 4) {
          throw std::runtime_error("rect must have 4 values");
        }

        return Sprite(id, rect[0].cast<int>(), rect[1].cast<int>(), rect[2].cast<int>(), rect[3].cast<int>());
      }))
      .def_property_readonly("id", [](const Sprite &self) { return self.id; })
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

  py::class_<Entity>(m, "Entity")
      .def(py::init(                              //
          []() -> std::unique_ptr<Entity> {       //
            throw "Don't instance this directly"; //
          }))                                     //
      .def_property_readonly("id", &Entity::GetId)
      .def("add", [](Entity &self, py::object component) {
        if (py::isinstance<Sprite>(component)) {
          self.AddComponent<Sprite>(component.cast<Sprite>());
        }
      });
}
