#pragma once

#include "defs.hpp"
#include "windows.hpp"
#include "ai.hpp"
#include "components/clearance.hpp"

#include <cassert>
#include <vector>

struct Job {
  Job(string d, Clearance c, AIScript* ais)
    : desc(d), clear(c), scr(ais), state(UNRESERVED) { }
  ~Job() { if (scr) delete scr; }

  inline const string& description() const {
    return desc;
  }
  inline Clearance clearance() const { return clear; }

  inline AIScript* script() {
    assert(scr != nullptr);
    AIScript* r = scr;
    scr = nullptr;
    return r;
  }

  inline bool available() const { return state == UNRESERVED; }
  inline bool unavailable() const { return state != UNRESERVED; }
  inline bool completed() const { return state == COMPLETED; }

  inline void reserve() { assert(state == UNRESERVED); state = RESERVED; }
  inline void complete() { assert(state == RESERVED); state = COMPLETED; }

  string desc;
  Clearance clear;
  AIScript* scr;

  enum State {
    UNRESERVED,
    RESERVED,
    COMPLETED
  } state;
};