#include "ECS/Events/event_bus.h"
#include "ECS/Events/types/key_pressed.h"
#include "ECS/ecs.h"

class InputSystem : public System {
  public:
    InputSystem() {
    }
    virtual void SubscribeToEvents(std::unique_ptr<EventBus> &event_bus) override {
      event_bus->Subscribe<KeyPressedEvent, InputSystem>(this, &InputSystem::onKeyPressed);
    }

  private:
    void onKeyPressed(KeyPressedEvent &event) {
      Logger::info("key pressed [" + event.symbol + "] keycode: " + std::to_string(event.key_code));
    }
};
