#pragma once
#include "event.h"
#include "logger.h"
#include <list>
#include <map>
#include <memory>
#include <string>
#include <typeindex>

class IEventCallback {
  private:
    virtual void Call(Event &e) = 0;

  public:
    virtual ~IEventCallback() = default;
    void Execute(Event &e) {
      Call(e);
    }
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
  private:
    typedef void (TOwner::*CallbackFunction)(TEvent &);
    TOwner *owner;
    CallbackFunction callback;
    void Call(Event &e) override {
      std::invoke(callback, owner, static_cast<TEvent>(e));
    }

  public:
    EventCallback(TOwner *owner, CallbackFunction cb) {
      this->owner = owner;
      this->callback = cb;
    }
    ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
  private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

  public:
    EventBus() {
      Logger::info("EventBus spawned");
    }
    ~EventBus() {
      Logger::info("EventBus despawned");
    }

    template <typename EventType, typename TOwner>
    void Subscribe(TOwner *owner, void (TOwner::*cb)(EventType &e)) {
      if (!subscribers[typeid(EventType)].get()) {
        subscribers[typeid(EventType)] = std::make_unique<HandlerList>();
      }
      auto subscriber = std::make_unique<EventCallback<TOwner, EventType>>(owner, cb);
      subscribers[typeid(EventType)]->push_back(std::move(subscriber));
    };

    template <typename EventType, typename... TArgs>
    void Emit(TArgs &&...args) {
      EventType event(std::forward<TArgs>(args)...);
      for (const auto &handler : *subscribers[typeid(EventType)]) {
        handler->Execute(event);
      }
    };
};
