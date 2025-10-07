#pragma once
#include "BaseWeapon.h"
#include "BaseRole.h"
#include <atomic>

class Bullet :public BaseWeapon {
private:
  constexpr static const int RADIUS = 10;     // Ô²Çò×Óµ¯°ë¾¶
public:
  Bullet();
  ~Bullet() = default;

  void draw() const override;
  void update(const BaseRole& ref_role, int index, int total) override;
};

