#pragma once
#include "BaseWeapon.h"
#include "BaseRole.h"
#include <atomic>

class Bullet :public BaseWeapon {
public:
  Bullet();
  Bullet(const BaseRole* prole);
  Bullet(const Bullet& oth);
  ~Bullet() = default;

  void bind(const BaseRole* prole) override;
  void draw() const override;
  void update() override;

private:
  constexpr static const int RADIUS = 10;     // 圆球子弹半径
  static std::atomic<int> M_count;            // 圆球子弹个数
private:
  const BaseRole* bind_role;            // 绑定的角色

  // TODO: 这里的第几个应该跟bind_role绑定, 也就是形成一个映射表，包括M_count也是应该与bind_role相关, 后期改
  // 要么直接将Player作为单例类，然后将就无需映射了, 就只有那么一个角色，所以直接记录的就是与之对应的
  int this_id;                          // 当前是第几个武器
};

