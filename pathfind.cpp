#include "pathfind.hpp"

#include <algorithm>
#include <iomanip>

vector<point> pathfind(City& c, int x1, int y1, int x2, int y2) {
  constexpr size_t XCOORD = 2;
  constexpr size_t YCOORD = 3;
  constexpr size_t DIST = 1;
  vector<waypoint> pheap{ waypoint( -(abs(x1-x2) + abs(y1-y2) + 1), 1, x1, y1 ) };

  vector<int> dist(c.getXSize() * c.getYSize());
  int ysz = c.getYSize();

  while (pheap.size() > 0 && dist[y2 * ysz + x2] == 0) {
    pop_heap(pheap.begin(), pheap.end());
    tuple<int,int,int,int> p = pheap.back();
    pheap.pop_back();
    // cout << "(" << pheap.size() << ") Popped: "
    //      << get<0>(p) << ","
    //      << get<1>(p) << ","
    //      << get<2>(p) << ","
    //      << get<3>(p) << endl;
    int& d = dist[get<YCOORD>(p) * ysz + get<XCOORD>(p)];

    if (d != 0) continue;

    d = get<DIST>(p);
    for (int i=0;i<4;++i) {
      int x = get<XCOORD>(p) + offs[i].first;
      int y = get<YCOORD>(p) + offs[i].second;
      if (x >= 0 && x < c.getXSize() && y >= 0 && y < c.getYSize()) {
        if (c.tile(x,y).type != '.') continue;

        int& d2 = dist[y * ysz + x];
        if (d2 > d + 1 || d2 == 0) {
          pheap.push_back(waypoint(-abs(x-x2) - abs(y-y2) - d - 1, d + 1, x, y));
          push_heap(pheap.begin(), pheap.end());
        }
        //cout << "A " << x << " " << y << " " << d2 << endl;
      }
    }
  }

  for (int y = 0; y < c.getYSize(); ++y) {
    for (int x = 0; x < c.getXSize(); ++x)
      cout << setw(2) << dist[y*ysz + x] << " ";
    cout << endl;
  }

  int d = dist[y2 * ysz + x2];

  vector<point> r;
  r.reserve(d);

  if (d != 0) {
    int x = x2;
    int y = y2;
    while (x != x1 || y != y1) {
      for (int i=0;i<4;++i) {
        if (c.check(x+offs[i].first, y+offs[i].second))
          if (dist[(y+offs[i].second)*ysz+x+offs[i].first] == d - 1) {
            d = d - 1;
            r.push_back({x, y});
            x = x + offs[i].first;
            y = y + offs[i].second;
            break;
          }
      }
    }
  }
  
  return r;
}

