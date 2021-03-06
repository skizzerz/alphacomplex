#pragma once

#include <utility>

typedef std::pair<int, int> point;

struct Point {
  inline point as_point() const { return{ x, y }; }

  struct City* city;
  int x, y;

  bool operator==(const Point& o) { return o.city == city && o.x == x && o.y == y; }
  bool operator!=(const Point& o) { return !(*this == o); }
};

struct rect {
  int x, y, w, h;

  inline bool overlaps(rect o) {
    return x < (o.x + o.w) && (x + w) > o.x
      && y < (o.y + o.h) && (y + h) > o.y;
  }
};

struct Rect {
  inline rect as_rect() const { return{ x, y, w, h }; }

  struct City* city;
  int x, y, w, h;
};
