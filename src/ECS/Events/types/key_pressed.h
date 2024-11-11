#pragma once
#include "ECS/Events/event.h"
#include <string>

class KeyPressedEvent : public Event {
  public:
    int key_code;
    std::string symbol;
    KeyPressedEvent(int key_code, const std::string &symbol) : key_code(key_code), symbol(symbol){};
};
