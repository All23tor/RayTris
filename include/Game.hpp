#ifndef GAME_HPP
#define GAME_HPP

#include "Playfield.hpp"

struct Game {
  const DrawingDetails drawing_details;
  const Controller controller;
  const HandlingSettings settings;
  Playfield playfield;
  bool paused = false;

  Game(const DrawingDetails&, const Controller&, const HandlingSettings&);
  void draw() const;
  bool update();
};

static inline Vector2 screen_vector() {
  return Vector2(GetScreenWidth(), GetScreenHeight());
};

constexpr Vector2 PLAYFIELD_VECTOR(Playfield::WIDTH, Playfield::VISIBLE_HEIGHT);

#endif
