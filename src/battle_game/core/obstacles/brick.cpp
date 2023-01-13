#include "battle_game/core/obstacles/brick.h"

namespace battle_game::obstacle {

namespace {
uint32_t life_bar_model_index = 0xffffffffu;
}  // namespace

Brick::Brick(GameCore *game_core,
             uint32_t id,
             glm::vec2 position,
             float rotation,
             glm::vec2 scale)
    : Obstacle(game_core, id, position, rotation) {
  lifebar_offset_ = {0.0f, 1.0f};
  background_lifebar_color_ = {1.0f, 0.0f, 0.0f, 0.9f};
  front_lifebar_color_ = {0.0f, 1.0f, 0.0f, 0.9f};
  fadeout_lifebar_color_ = {1.0f, 1.0f, 1.0f, 0.5f};
  fadeout_health_ = 1;
  if (!~life_bar_model_index) {
    auto mgr = AssetsManager::GetInstance();
    life_bar_model_index = mgr->RegisterModel(
        {{{-0.5f, 0.08f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
         {{-0.5f, -0.08f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
         {{0.5f, 0.08f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
         {{0.5f, -0.08f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}},
        {0, 1, 2, 1, 2, 3});
  }
  obstacle_type_ = brick;
}

bool Brick::IsBlocked(glm::vec2 p) const {
  p = WorldToLocal(p);
  return p.x <= scale_.x && p.x >= -scale_.x && p.y <= scale_.y &&
         p.y >= -scale_.y;
}

void Brick::Render() {
  battle_game::SetColor(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
  battle_game::SetTexture("../../textures/brick.png");
  battle_game::SetTransformation(position_, rotation_, scale_);
  battle_game::DrawModel(0);
  RenderLifeBar();
}

void Brick::SetLifeBarLength(float new_length) {
  lifebar_length_ = std::min(new_length, 0.0f);
}
void Brick::SetLifeBarOffset(glm::vec2 new_offset) {
  lifebar_offset_ = new_offset;
}
void Brick::SetLifeBarFrontColor(glm::vec4 new_color) {
  front_lifebar_color_ = new_color;
}
void Brick::SetLifeBarBackgroundColor(glm::vec4 new_color) {
  background_lifebar_color_ = new_color;
}
void Brick::SetLifeBarFadeoutColor(glm::vec4 new_color) {
  fadeout_lifebar_color_ = new_color;
}
float Brick::GetLifeBarLength() {
  return lifebar_length_;
}
glm::vec2 Brick::GetLifeBarOffset() {
  return lifebar_offset_;
}
glm::vec4 Brick::GetLifeBarFrontColor() {
  return front_lifebar_color_;
}
glm::vec4 Brick::GetLifeBarBackgroundColor() {
  return background_lifebar_color_;
}
glm::vec4 Brick::GetLifeBarFadeoutColor() {
  return fadeout_lifebar_color_;
}

void Brick::ShowLifeBar() {
  lifebar_display_ = true;
}
void Brick::HideLifeBar() {
  lifebar_display_ = false;
}

void Brick::RenderLifeBar() {
  if (lifebar_display_) {
    auto pos = GetPosition() + lifebar_offset_;
    auto health = GetHealth();
    SetTransformation(pos, 0.0f, {lifebar_length_, 1.0f});
    SetColor(background_lifebar_color_);
    SetTexture(0);
    DrawModel(life_bar_model_index);
    glm::vec2 shift = {(float)lifebar_length_ * (1 - health) / 2, 0.0f};
    SetTransformation(pos - shift, 0.0f, {lifebar_length_ * health, 1.0f});
    SetColor(front_lifebar_color_);
    DrawModel(life_bar_model_index);
    if (std::fabs(health - fadeout_health_) >= 0.01f) {
      fadeout_health_ = health + (fadeout_health_ - health) * 0.93;
      shift = {lifebar_length_ * (health + fadeout_health_ - 1) / 2, 0.0f};
      SetTransformation(pos + shift, 0.0f,
                        {lifebar_length_ * (health - fadeout_health_), 1.0f});
      SetColor(fadeout_lifebar_color_);
      DrawModel(life_bar_model_index);
    } else {
      fadeout_health_ = health;
    }
  }
}

}  // namespace battle_game::obstacle
