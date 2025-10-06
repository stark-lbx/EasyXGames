#pragma once
#include "GameObject2D.h"
#include "BaseRole.h"
// 手绘武器, 没有图片
class BaseWeapon : public GameObject2D {
  /*
  * GameObject2D:
  * public:
  *   // 获取对象位置
  *   virtual const POINT& getPosition() const = 0;
  *   // 设置对象位置
  *   virtual void setPosition(int x, int y) = 0;
  * protected:
  *   POINT position;  //位置
  */
public:
  BaseWeapon() = default;
  ~BaseWeapon() = default;
  explicit BaseWeapon(int atk);
  explicit BaseWeapon(int x, int y);
  explicit BaseWeapon(int x, int y, int atk);
  explicit BaseWeapon(int x, int y, int w, int h);
  explicit BaseWeapon(int x, int y, int w, int h, int atk);

  const int getAttack() const;
  void setAttack(int newatk);

  virtual void draw() const = 0;
  virtual void update(const BaseRole& prole, int index, int total) = 0;

  // WHY: 这里不知道为什么，在做碰撞检测时, 从父类的接口获取的值不是 {0,0} 
  const SIZE& getSize() const override {
    static SIZE s{ 0,0 };
    return s;
  }
protected:
  int m_attack;   // 攻击力
};

