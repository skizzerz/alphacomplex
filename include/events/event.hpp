#pragma once
#include <cstdlib>
#include <functional>
#include "event_status.hpp"

struct EventRunner;

namespace Event {
  template<typename... Arguments>
  struct EventBase {
    EventRunner* target = nullptr; // filled out when passed to an event handler, do not fill this out yourself

    using callback_t = function<EventStatus(const EventBase&, Arguments...)>;

    const EventBase* singleton() {
      if (_singleton == nullptr) {
        _singleton = new EventBase();
      }

      return _singleton;
    }

  protected:
    EventBase* _singleton = nullptr;
  };

  // example event, click passes in the x and y coords of where it was clicked
  struct click : public EventBase<int, int> { };
}
