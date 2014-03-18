#pragma once

struct EventStatus {
  enum {
    SUCCESS = true,
    FAILURE = false,

    KEEP = true,
    DISCARD = false,

    HALT = true,
    CONTINUE = false
  };

  bool success;
  bool keep;
  bool halt;

  EventStatus(bool success = true, bool keep = true, bool halt = false) : success(success), keep(keep), halt(halt) { }
};
