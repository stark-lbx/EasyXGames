#pragma once
#include "GameObject2D.h"
#include "Animation.h"

class BaseRole : public GameObject2D {
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
  ~BaseRole() = default;
  BaseRole() = default;
  explicit BaseRole(int x, int y, int w, int h);
  explicit BaseRole(int x, int y, int w, int h, int xs, int ys);
  explicit BaseRole(int x, int y, int w, int h, int xs, int ys, int _hp);

  virtual void move() = 0;            // ��ɫ�ƶ�
  virtual void draw(int delta) = 0;   // ��ɫ����
protected:
  bool alive;         // ���״̬
  int hp;             // ��ɫ����ֵ
  int xspeed;         // ˮƽ�ƶ��ٶ�
  int yspeed;         // ��ֱ�ƶ��ٶ�

  IMAGE img_shadow;   // ��ɫ��ӰЧ��
  std::shared_ptr<Animation> anim_left;   // ����������ƶ�����
  std::shared_ptr<Animation> anim_right;  // ����������ƶ�����
  std::shared_ptr<Animation> anim_up;     // ����������ƶ�����
  std::shared_ptr<Animation> anim_down;   // ����������ƶ�����
};

