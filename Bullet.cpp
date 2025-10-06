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
  // �� role ��ԭ����ĵ�ַ����, �����һ��ָ�� ԭrole ������ָ��
  bind_role = prole;
}

void Bullet::draw() const {
  setlinecolor(RGB(255, 155, 50));
  setfillcolor(RGB(200, 75, 10));
  fillcircle(position.x, position.y, Bullet::RADIUS);
}

void Bullet::update() {
  if (bind_role == nullptr)return;
  // ֻ�а��˶���, �Ž���λ�ø���
  // ȷ���ӵ�ʵʱ�����ɫ�ƶ�
  static int angle = 0;         // �Ƕ�
  const int angle_interval = 1; // �Ƕȼ��(ÿ�θ��� 4 ���Ƕ�)
  angle = (angle + angle_interval) % 360;
  double radius = 100 + 25 * sin(angle * acos(-1.0) / 180);  // �����뾶����(100 �� 25)

  // �Ƕ�ֵת������
  double radian = ((360.0 / (M_count - 1)) * this_id + angle) * acos(-1.0) / 180;
  // ����������λ��
  this->setPosition(
    bind_role->getPosition().x + bind_role->getSize().cx / 2 + int(radius * cos(radian)),
    bind_role->getPosition().y + bind_role->getSize().cy / 2 - int(radius * sin(radian))
  );

}

