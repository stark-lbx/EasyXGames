#pragma once
#include "GameObject2D.h"
#include "BaseRole.h"
// �ֻ�����, û��ͼƬ
class BaseWeapon : public GameObject2D {
  /*
  * GameObject2D:
  * public:
  *   // ��ȡ����λ��
  *   virtual const POINT& getPosition() const = 0;
  *   // ���ö���λ��
  *   virtual void setPosition(int x, int y) = 0;
  * protected:
  *   POINT position;  //λ��
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

  // WHY: ���ﲻ֪��Ϊʲô��������ײ���ʱ, �Ӹ���Ľӿڻ�ȡ��ֵ���� {0,0} 
  const SIZE& getSize() const override {
    static SIZE s{ 0,0 };
    return s;
  }
protected:
  int m_attack;   // ������
};

