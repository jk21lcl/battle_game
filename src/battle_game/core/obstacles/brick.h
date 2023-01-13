#pragma once
#include "battle_game/core/game_core.h"
#include "battle_game/core/obstacle.h"

namespace battle_game::obstacle {
class Brick : public Obstacle {
 public:
  Brick(GameCore *game_core,
        uint32_t id,
        glm::vec2 position,
        float rotation = 0.0f,
        glm::vec2 scale = glm::vec2{1.0f, 1.0f});

  [[nodiscard]] float GetMaxHealth() const {
    return 1200.0f;
  }

  [[nodiscard]] float GetHealth() const {
    return health_;
  }

  void SetHealth(float new_health) {
    health_ = std::clamp(new_health, 0.0f, 1.0f);
  }

  void SetLifeBarLength(float new_length);
  void SetLifeBarOffset(glm::vec2 new_offset);
  void SetLifeBarFrontColor(glm::vec4 new_color);
  void SetLifeBarBackgroundColor(glm::vec4 new_color);
  void SetLifeBarFadeoutColor(glm::vec4 new_color);
  [[nodiscard]] float GetLifeBarLength();
  [[nodiscard]] glm::vec2 GetLifeBarOffset();
  [[nodiscard]] glm::vec4 GetLifeBarFrontColor();
  [[nodiscard]] glm::vec4 GetLifeBarBackgroundColor();
  [[nodiscard]] glm::vec4 GetLifeBarFadeoutColor();

  void ShowLifeBar();
  void HideLifeBar();
  void RenderLifeBar();

 private:
  [[nodiscard]] bool IsBlocked(glm::vec2 p) const override;
  void Render() override;
  glm::vec2 scale_{1.0f};

  float health_{1.0f};
  float fadeout_health_;
  bool lifebar_display_{true};
  glm::vec2 lifebar_offset_{};
  float lifebar_length_{2.4f};
  glm::vec4 front_lifebar_color_{};
  glm::vec4 background_lifebar_color_{};
  glm::vec4 fadeout_lifebar_color_{};
};
}  // namespace battle_game::obstacle
