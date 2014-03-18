#pragma once
#include <memory>
#include <map>
#include <deque>
#include <exception>
#include "event.hpp"
#include "event_info.hpp"

using namespace std;

struct EventStatus;

struct wrong_object : public exception {
  virtual const char* what() {
    return "Attempting to deregister an event on a different object than where it was registered";
  }
};

struct EventRunner {
  template<typename Event>
  EventInfo on(typename Event::callback_t callback) {
    EventInfo_t<Event> info;
    ++_next_event_id;
    info.id = _next_event_id;
    info.object = this;
    info.callback = callback;
    _registered_callbacks.push_back(info);
  }

  void off() {
    _registered_callbacks.clear();
  }

  template<typename Event>
  void off() {
    _registered_callbacks[Event::singleton()].clear();
  }

  template<typename Event>
  void off(EventInfo event_info) {
    if (event_info.object != this) {
      throw wrong_object();
    }

    const Event* evt = Event::singleton();

    for (auto it = _registered_callbacks[evt].begin(); it != _registered_callbacks[evt].end(); ++it) {
      if (event_info.id == it->id) {
        _registered_callbacks[evt].erase(it);
        break;
      }
    }
  }

  template<typename Event, typename... Arguments>
  EventStatus trigger(Arguments...) {
    const Event* sing = Event::singleton();
    Event evt;
    evt.target = this;

    // iterate through a copy of _registered_callbacks[sing] so we can modify the original with impunity
    deque<EventInfo> callbacks = { _registered_callbacks[sing].begin(), _registered_callbacks[sing].end() };

    bool success = true;

    for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
      EventStatus status = (it->get_callback())(evt, Arguments...);
      
      if (!status.keep) {
        for (auto it2 = _registered_callbacks[sing].begin(); it2 != _registered_callbacks[sing].end(); ++it2) {
          if (it->id == it2->id) {
            _registered_callbacks[sing].erase(it2);
            break;
          }
        }
      }
      
      if (!status.success) {
        success = false;
      }

      if (status.halt) {
        break;
      }
    }

    return EventStatus(success);
  }

private:
  map<void*, deque<EventInfo> > _registered_callbacks;
  unsigned int _next_event_id = 0;
};
