#pragma once
#include <memory>
#include <exception>

using namespace std;

struct EventRunner;

struct invalid_base_call : exception {
  virtual const char* what() {
    return "Cannot call this method on a base class instance";
  }
};

struct EventInfo {
  unsigned int id;
  EventRunner* object; // todo: make this a weak_ptr somehow

protected:
  friend struct EventRunner;
  
  virtual void get_callback() {
    throw invalid_base_call();
  }

  virtual void get_event() {
    throw invalid_base_call();
  }
};

template<typename Event>
struct EventInfo_t : public EventInfo {
protected:
  typename Event::callback_t callback;

  virtual typename Event::callback_t get_callback() {
    return callback;
  }

  virtual const Event* get_event() {
    return Event::singleton();
  }
};
