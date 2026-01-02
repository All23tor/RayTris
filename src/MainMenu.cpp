#include "MainMenu.hpp"
#include "raylib.h"
#include <array>
#include <ranges>
#include <utility>

namespace {
constexpr auto OPTIONS_SIZE = std::to_underlying(MainMenu::Option::Exit) + 1;
constexpr const char* name_option(MainMenu::Option option) {
  static constexpr std::array<const char*, OPTIONS_SIZE> NAMES = {
    "Single Player",
    "Two Players",
    "Settings",
    "Exit",
  };
  return NAMES[std::to_underlying(option)];
}
constexpr auto OPTIONS = [] {
  std::array<MainMenu::Option, OPTIONS_SIZE> res;
  for (int i = 0; i < res.size(); i++)
    res[i] = MainMenu::Option{i};
  return res;
}();

}; // namespace

void MainMenu::draw() const {
  const int width = GetScreenWidth();
  const int height = GetScreenHeight();
  const float font_size = height / 12.0f;
  const float font_size_big = height / 4.0f;

  ClearBackground(LIGHTGRAY);
  DrawText(
    "RAYTRIS",
    (width - MeasureText("RAYTRIS", font_size_big)) / 2.0f,
    height / 2.0f - font_size_big - font_size,
    font_size_big,
    RED
  );

  const float box_width = 8.0f * font_size;
  const float separation = 1.5f * font_size;
  const float box_height = 1.3f * font_size;
  for (auto [i, option] : std::views::enumerate(OPTIONS)) {
    auto option_name = name_option(option);
    const bool is_selected = option == selected_option;
    const Rectangle box = {
      (width - box_width) / 2.0f,
      (height - box_height + font_size) / 2.0f + i * separation,
      box_width,
      box_height
    };
    DrawRectangleRec(box, is_selected ? SKYBLUE : GRAY);
    DrawRectangleLinesEx(box, font_size / 10.0, is_selected ? BLUE : BLACK);
    DrawText(
      option_name,
      (width - MeasureText(option_name, font_size)) / 2.0,
      height / 2.0 + i * separation,
      font_size,
      is_selected ? BLUE : BLACK
    );
  }
}

void MainMenu::update() {
  if (IsKeyPressed(KEY_DOWN))
    selected_option =
      Option{(std::to_underlying(selected_option) + 1) % OPTIONS_SIZE};
  if (IsKeyPressed(KEY_UP))
    selected_option = Option{
      (std::to_underlying(selected_option) - 1 + OPTIONS_SIZE) % OPTIONS_SIZE
    };
}

bool MainMenu::should_stop_running() const {
  return IsKeyPressed(KEY_ENTER);
}

MainMenu::Option MainMenu::get_selected_option() const {
  return selected_option;
}
