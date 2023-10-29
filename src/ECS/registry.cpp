#include "registry.h"
#include "../Logger/logger.h"
#include "ecs.h"
#include <memory>

Entity Registry::CreateEntity() {
  int id = len++;
  if (id >= signatures.size()) {
    signatures.resize(id + 1);
  }

  auto entity = std::make_shared<Entity>(id);
  toAdd.insert(*entity);
  Logger::log("Entity created with id: " + std::to_string(id));

  return *entity;
};

void Registry::AddEntityToSystem(Entity entity) {
  const auto entityId = entity.GetId();
  const auto entitySignature = signatures[entityId];

  for (auto &[system_type, system] : systems) {
    const auto systemSignature = system->GetSignature();
    if ((systemSignature & entitySignature) == systemSignature) {
      system->AddEntity(entity);
      Logger::log("Entity added to " + std::string(system_type.name()) +
                  " system");
    }
  }
};

void Registry::Update() {
  for (auto entity : toAdd) {
    AddEntityToSystem(entity);
  }
  toAdd.clear();
}
