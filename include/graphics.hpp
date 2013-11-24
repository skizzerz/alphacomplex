#pragma once
#include <deque>
#include <vector>
#include <string>

using namespace std;

extern const char* white;

enum : char {
  CORNER_SE = 11,
  CORNER_NE = 12,
  CORNER_NW = 13,
  CORNER_SW = 14,
  CROSS = 15,
  HBAR = 18,
  TEE_E = 21,
  TEE_W = 22,
  TEE_N = 23,
  TEE_S = 24,
  VBAR = 25
};

struct Component;
struct _XDisplay;
typedef struct _XDisplay Display;
struct GraphicsInternal;

struct Graphics {
  Graphics(const Graphics&) = delete;
  Graphics& operator=(const Graphics&) = delete;
  Graphics();
  ~Graphics();

  enum Context {
    WHITE,
    DEFAULT
  };
  void drawString(int x, int y, const std::string& str, Context gc = DEFAULT);
  void drawChar(int x, int y, char str, Context gc = DEFAULT);

  Display *display;
  int s;

  deque<Component*> c;

  void handle_events(struct Controller*);
  bool destroyed = false;

  void repaint();
  void destroy();

  int getWidth();
  int getHeight();
  
  GraphicsInternal* pImpl;
};
