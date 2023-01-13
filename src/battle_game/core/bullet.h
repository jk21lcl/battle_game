#pragma once
#include "battle_game/core/object.h"
#include "battle_game/graphics/assets_manager.h"
#include "cstdint"

namespace battle_game {
enum BulletType  // use lowercase to avoid class name
{
  untracked_bullet,
  cannon_ball,
  // add your bullet here:
  coin,
  crit_bullet,
  electric_ball,
  inhale_bullet,
  mine,
  missile,
  rebounding_ball,
  rocket,
  smoke_bomb,
  sweaty_soybean,
  warning_line,
  water_drop
};

class GameCore;
class Bullet : public Object {
 public:
  Bullet(GameCore *core,
         uint32_t id,
         uint32_t unit_id,
         uint32_t player_id,
         glm::vec2 position,
         float rotation,
         float damage_scale);
  ~Bullet() override;
  [[nodiscard]] BulletType GetBulletType() const {
    return bullet_type_;
  }
  [[nodiscard]] float GetDamage() const {
    return damage_scale_ * 10.0f;
  }

 protected:
  uint32_t unit_id_{};
  uint32_t player_id_{};
  float damage_scale_{1.0f};
  BulletType bullet_type_{untracked_bullet};
};
}  // namespace battle_game
