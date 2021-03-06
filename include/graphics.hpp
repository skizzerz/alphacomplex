#pragma once
#include <deque>
#include <vector>
#include <string>
#include "defs.hpp"

using namespace std;

extern const char* white;

#define FONT_HEIGHT 18
#define FONT_WIDTH 10

struct Widget;

/// The graphics adapter is a singleton class that provides target-specific
/// input and output services. Ideally, all I/O that is dependant on the
/// platform should be isolated within a cpp file inheriting and implementing
/// the member methods here.
///
/// Key functions for the main loop are `repaint()`, `destroy()`, and `handle_events()`.
struct Graphics : private debug_policy_t {
  /// The graphics adapter is a singleton and should not be copied.
  Graphics(const Graphics&) = delete;
  /// The graphics adapter is a singleton and should not be copied.
  Graphics& operator=(const Graphics&) = delete;

  /// Used to provide color information to drawing commands.
  ///
  /// May be extend in the future to include things like bold, italic, underline, and font family.
  enum Context {
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    BROWN,
    ORANGE,
    DEFAULT
  };
  /// Draw a string at the given CHARACTER coordinates.
  ///
  /// @param x,y The character coordinates to draw at
  /// @param str The string to be drawn
  /// @param gc  The context describing color/bgcolor/font/etc
  void drawString(int x, int y, const std::string& str, Context gc = DEFAULT);

  /// Draw a char at the given CHARACTER coordinates.
  ///
  /// @param x,y The character coordinates to draw at
  /// @param str The character to be drawn
  /// @param gc  The context describing color/bgcolor/font/etc
  void drawChar(int x, int y, char str, Context gc = DEFAULT);

  /// Iterate through all pending input events
  ///
  /// @param ctrl The controller all user-based events should be redirected to
  void handle_events(struct Controller* ctrl);

  /// Called by the main loop to repaint the screen (do not call this)
  void repaint();
  /// Called by the destructor or by a 'quit' action
  void destroy();

  /// Fetches the current width from the graphics context
  ///
  /// @return Current width in pixels
  inline int getWidth() { return width; }

  /// Fetches the current height from the graphics context
  ///
  /// @return Current height in pixels
  inline int getHeight() { return height; }

  deque<Widget*> c;
  bool destroyed = false;

protected:
  Graphics() { }
  ~Graphics() { destroy(); }

  int width, height;
};

Graphics* new_graphics();
