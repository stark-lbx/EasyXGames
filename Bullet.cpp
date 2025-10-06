#include "Bullet.h"
#include <iostream>


Bullet::Bullet() : BaseWeapon(0, 0, 0, 0, 1) {}

void Bullet::draw() const {
  setlinecolor(RGB(255, 155, 50));
  setfillcolor(RGB(200, 75, 10));
  fillcircle(position.x, position.y, Bullet::RADIUS);
}

void Bullet::update(const BaseRole& ref_role, int index, int total) {
  // ȷ���ӵ�ʵʱ�����ɫ�ƶ�
  static int angle = 0;         // �Ƕ�
  const int angle_interval = 1; // �Ƕȼ��(ÿ�θ��� 4 ���Ƕ�)
  angle = (angle + angle_interval) % 360;
  double radius = 100 + 25 * sin(angle * acos(-1.0) / 180);  // �����뾶����(100 �� 25)

  // �Ƕ�ֵת������
  double radian = ((360.0 / total) * index + angle) * acos(-1.0) / 180;
  // ����������λ��
  this->setPosition(
    ref_role.getPosition().x + ref_role.getSize().cx / 2 + int(radius * cos(radian)),
    ref_role.getPosition().y + ref_role.getSize().cy / 2 - int(radius * sin(radian))
  );

}

