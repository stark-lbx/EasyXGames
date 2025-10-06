#pragma once
#include "GameObject2D.h"
#include "Animation.h"

class BaseRole : public GameObject2D {
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
  ~BaseRole() = default;
  BaseRole() = default;
  explicit BaseRole(int x, int y, int w, int h);
  explicit BaseRole(int x, int y, int w, int h, int xs, int ys);
  explicit BaseRole(int x, int y, int w, int h, int xs, int ys, int _hp);

  virtual void move() = 0;            // 角色移动
  virtual void draw(int delta) = 0;   // 角色绘制
protected:
  bool alive;         // 存活状态
  int hp;             // 角色生命值
  int xspeed;         // 水平移动速度
  int yspeed;         // 垂直移动速度

  IMAGE img_shadow;   // 角色阴影效果
  std::shared_ptr<Animation> anim_left;   // 朝向左面的移动动画
  std::shared_ptr<Animation> anim_right;  // 朝向右面的移动动画
  std::shared_ptr<Animation> anim_up;     // 朝向上面的移动动画
  std::shared_ptr<Animation> anim_down;   // 朝向下面的移动动画
};

