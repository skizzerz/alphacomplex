#pragma once

#include "graphics.hpp"

struct Entity {
  virtual const char* rawname() const = 0;
  virtual void render(Graphics& g) const { }

  virtual void update() { }
  
  Entity* prev;
  Entity* next;

  Entity* g_prev;
  Entity* g_next;

  Entity(int) : prev(nullptr),
                next(nullptr),
                g_prev(nullptr),
                g_next(nullptr)
    { }
  Entity() : prev(nullptr),
             next(nullptr),
             g_prev(nullptr),
             g_next(GLOB_ENTLIST)
    {
      GLOB_ENTLIST = this;
      if (g_next != nullptr)
        g_next->g_prev = this;
    }

  virtual ~Entity() {
    remove();
    global_remove();
  }

  void insert_after(Entity* e) {
    next = e->next;
    prev = e;
    e->next = this;
    if (next != nullptr)
      next->prev = this;
  }

  void remove() {
    if (next != nullptr)
      next->prev = prev;
    if (prev != nullptr)
      prev->next = next;
  }

  void global_remove() {
    if (GLOB_ENTLIST == this)
      GLOB_ENTLIST = g_next;
    if (g_next != nullptr)
      g_next->g_prev = g_prev;
    if (g_prev != nullptr)
      g_prev->g_next = g_next;
  }

  template<class T>
  T& as() { return (T&)(*this); }
  template<class T>
  const T& as() const { return (T&)(*this); }

  static Entity* GLOB_ENTLIST;
};

struct SmartEntity : Entity {
  SmartEntity(int x_, int y_) : Entity(), x(x_), y(y_) { }

  int x, y;

  void set_loc(int x_, int y_) { x = x_; y = y_; }
};

struct Dwarf : SmartEntity {
  Dwarf(int x_, int y_) : SmartEntity(x_, y_) { }

  static constexpr const char* RAWNAME = "dwarf";
  virtual const char* rawname() const { return RAWNAME; }

  virtual void render(Graphics& g) const {
    //cerr << "rendering dwarf @ " << x << "," << y << endl;
    g.putChar(x, y, '@');
  }

  virtual void update();
};
