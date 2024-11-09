#include "ECS/Events/event.h"

class KeyPressedEvent : public Event {
  public:
    int key_code;
    KeyPressedEvent(int key_code) : key_code(key_code){};
};
