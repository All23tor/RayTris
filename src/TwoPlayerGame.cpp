#include "TwoPlayerGame.hpp"
#include "Game.hpp"
#include "HandlingSettings.hpp"
#include <raymath.h>

static DrawingDetails drawing_details_1() {
  float block_length = DrawingDetails::HEIGHT_SCALE_FACTOR * 0.75f *
    GetScreenHeight() / Playfield::VISIBLE_HEIGHT;
  Vector2 position =
    (screen_vector() * Vector2(0.5f, 1.0f) - PLAYFIELD_VECTOR * block_length) /
    2.0f;
  return {block_length, position};
};

static DrawingDetails drawing_details_2() {
  float block_length = DrawingDetails::HEIGHT_SCALE_FACTOR * 0.75f *
    GetScreenHeight() / Playfield::VISIBLE_HEIGHT;
  Vector2 position =
    (screen_vector() * Vector2(1.5f, 1.0f) - PLAYFIELD_VECTOR * block_length) /
    2.0f;
  return {block_length, position};
};

static constexpr Controller CONTROLS_1{
  []() -> bool { return false; },
  []() -> bool { return IsKeyPressed(KEY_E); },
  []() -> bool { return IsKeyPressed(KEY_A); },
  []() -> bool { return IsKeyPressed(KEY_D); },
  []() -> bool { return IsKeyDown(KEY_A); },
  []() -> bool { return IsKeyDown(KEY_D); },
  []() -> bool { return IsKeyPressed(KEY_W); },
  []() -> bool { return IsKeyPressed(KEY_Q); },
  []() -> bool { return IsKeyPressed(KEY_R); },
  []() -> bool { return IsKeyPressed(KEY_Z); },
  []() -> bool { return IsKeyDown(KEY_S); },
  []() -> bool { return false; },
  []() -> bool { return IsKeyPressed(KEY_ENTER); },
  []() -> bool { return IsKeyPressed(KEY_ESCAPE); },
};

static constexpr Controller CONTROLS_2{
  []() -> bool { return false; },
  []() -> bool { return IsKeyPressed(KEY_O); },
  []() -> bool { return IsKeyPressed(KEY_J); },
  []() -> bool { return IsKeyPressed(KEY_L); },
  []() -> bool { return IsKeyDown(KEY_J); },
  []() -> bool { return IsKeyDown(KEY_L); },
  []() -> bool { return IsKeyPressed(KEY_I); },
  []() -> bool { return IsKeyPressed(KEY_U); },
  []() -> bool { return IsKeyPressed(KEY_P); },
  []() -> bool { return IsKeyPressed(KEY_M); },
  []() -> bool { return IsKeyDown(KEY_K); },
  []() -> bool { return false; },
  []() -> bool { return IsKeyPressed(KEY_ENTER); },
  []() -> bool { return IsKeyPressed(KEY_ESCAPE); },
};

TwoPlayerGame::TwoPlayerGame(
  const HandlingSettings& settings1, const HandlingSettings& settings2
) :
  game1(drawing_details_1(), CONTROLS_1, settings1),
  game2(drawing_details_2(), CONTROLS_2, settings2) {}

void TwoPlayerGame::update() {
  game1.update();
  game2.update();
  game2.paused = game1.paused;
}

void TwoPlayerGame::draw() const {
  game1.draw();
  game2.draw();
}

bool TwoPlayerGame::should_stop_running() const {
  return game1.controller.quit() && (game1.paused || game1.playfield.lost());
}
