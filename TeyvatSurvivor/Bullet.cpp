#include "Bullet.h"
#include <iostream>


Bullet::Bullet() : BaseWeapon(0, 0, 0, 0, 1) {}

void Bullet::draw() const {
  setlinecolor(RGB(255, 155, 50));
  setfillcolor(RGB(200, 75, 10));
  fillcircle(position.x, position.y, Bullet::RADIUS);
}

void Bullet::update(const BaseRole& ref_role, int index, int total) {
  // 确保子弹实时跟随角色移动
  static int angle = 0;         // 角度
  const int angle_interval = 1; // 角度间隔(每次更新 4 个角度)
  angle = (angle + angle_interval) % 360;
  double radius = 100 + 25 * sin(angle * acos(-1.0) / 180);  // 浮动半径长度(100 ± 25)

  // 角度值转弧度制
  double radian = ((360.0 / total) * index + angle) * acos(-1.0) / 180;
  // 设置武器新位置
  this->setPosition(
    ref_role.getPosition().x + ref_role.getSize().cx / 2 + int(radius * cos(radian)),
    ref_role.getPosition().y + ref_role.getSize().cy / 2 - int(radius * sin(radian))
  );

}

