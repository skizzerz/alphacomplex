#pragma once

#include "entities/entity.hpp"
#include "ai.hpp"

struct ActivityAI : AIScript {
  ActivityAI(int d) : delay(d) { }

  virtual int start(AI* ai) {
    (void)ai;
    return delay;
  }

  int delay;
};