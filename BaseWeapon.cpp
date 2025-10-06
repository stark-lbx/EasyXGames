#include "BaseWeapon.h"

BaseWeapon::BaseWeapon(int atk)
  :GameObject2D(0, 0, 0, 0), m_attack(atk) {}

BaseWeapon::BaseWeapon(int x, int y)
  :GameObject2D(x, y, 0, 0), m_attack(1) {}

BaseWeapon::BaseWeapon(int x, int y, int atk)
  :GameObject2D(x, y, 0, 0), m_attack(atk) {}

BaseWeapon::BaseWeapon(int x, int y, int w, int h)
  :GameObject2D(x, y, w, h), m_attack(1) {}

BaseWeapon::BaseWeapon(int x, int y, int w, int h, int atk)
  :GameObject2D(x, y, w, h), m_attack(atk) {}

const int BaseWeapon::getAttack() const { return this->m_attack; }

void BaseWeapon::setAttack(int newatk) { this->m_attack = newatk; }
