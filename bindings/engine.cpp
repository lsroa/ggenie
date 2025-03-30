#include "ECS/ecs.h"
#include "Game/sdl_game.h"
#include "Python.h"

static PyObject *create_tank(PyObject *self, PyObject *args) {
  return Py_None;
}

static PyMethodDef module_methods[]{{"create_tank", create_tank, METH_NOARGS, "Creates an Entity"},
                                    {NULL, NULL, 0, NULL}};

static PyModuleDef gg2 = {PyModuleDef_HEAD_INIT, "gg2", NULL, -1, module_methods, NULL, NULL, NULL, NULL};

static PyObject *PyInitGG(void) {
  return PyModule_Create(&gg2);
}

int main() {
  PyObject *pModule;
  PyObject *pFunc;

  /* PyImport_AppendInittab("gg2", &PyInitGG); */
  Py_Initialize();

  pModule = PyImport_ImportModule("main");
  if (pModule == NULL) {
    PyErr_Print();
    return 1;
  }

  pFunc = PyObject_GetAttrString(pModule, "setup");
  if (!PyCallable_Check(pFunc) || !pFunc) {
    PyErr_Print();
    return 1;
  }

  PyObject_CallObject(pFunc, NULL);

  Py_Finalize();
  return 0;
}
