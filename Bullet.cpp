#include "Bullet.h"
#include <iostream>

std::atomic<int> Bullet::M_count = 0;

Bullet::Bullet()
  : BaseWeapon(0, 0, 0, 0, 1)
  , bind_role(nullptr)
  , this_id(Bullet::M_count++) {}

Bullet::Bullet(const BaseRole* prole)
  : BaseWeapon(0, 0, 0, 0, 1)
  , bind_role(prole)
  , this_id(Bullet::M_count++) {}

Bullet::Bullet(const Bullet& oth) {
  bind_role = oth.bind_role;
  this_id = Bullet::M_count;
  ++Bullet::M_count;
}

void Bullet::bind(const BaseRole* prole) {
  // 将 role 的原对象的地址传入, 构造出一个指向 原role 的智能指针
  bind_role = prole;
}

void Bullet::draw() const {
  setlinecolor(RGB(255, 155, 50));
  setfillcolor(RGB(200, 75, 10));
  fillcircle(position.x, position.y, Bullet::RADIUS);
}

void Bullet::update() {
  if (bind_role == nullptr)return;
  // 只有绑定了对象, 才进行位置更新
  // 确保子弹实时跟随角色移动
  static int angle = 0;         // 角度
  const int angle_interval = 1; // 角度间隔(每次更新 4 个角度)
  angle = (angle + angle_interval) % 360;
  double radius = 100 + 25 * sin(angle * acos(-1.0) / 180);  // 浮动半径长度(100 ± 25)

  // 角度值转弧度制
  double radian = ((360.0 / (M_count - 1)) * this_id + angle) * acos(-1.0) / 180;
  // 设置武器新位置
  this->setPosition(
    bind_role->getPosition().x + bind_role->getSize().cx / 2 + int(radius * cos(radian)),
    bind_role->getPosition().y + bind_role->getSize().cy / 2 - int(radius * sin(radian))
  );

}

