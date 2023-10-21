#include "registry.h"
#include "../Logger/logger.h"
#include "ecs.h"

Entity Registry::CreateEntity() {
  int id = len++;
  /* if (id >= signatures.size()) { */
  /*   signatures.resize(id + 1); */
  /* } */
  Entity entity(id);
  toAdd.insert(entity);
  Logger::log("Entity created: " + std::to_string(id));
  return entity;
};
