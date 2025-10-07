#pragma once
#include "BaseRole.h"

class Player : public BaseRole {
  ////////////////////////////////
  // BaseRole:
  //   GameObject2D:
  //      virtual getPosition();
  //      virtual setPosition();
  //      POINT position;
  //   virtual move();
  //   virtual draw();
  //   bool alive;
  //   int hp;
  //   int xspeed;
  //   int yspeed;
  //   IMAGE img_shadow;
  //   Animation* anim_left;
  //   Animation* anim_right;
  //   Animation* anim_up;
  //   Animation* anim_down;
  ////////////////////////////////
private:
  static const int WIDTH = 80;
  static const int HEIGHT = 80;
  static const int SHADOW_WIDTH = 32;

  static const Atlas ATLAS_LEFT;
  static const Atlas ATLAS_RIGHT;
public:
  explicit Player(int x, int y, int xs, int ys);

  void move() override;
  void draw(int delta) override;

  // 角色转向
  void turnTo(Direction direction);
  // 停止角色在某方向的移动行为
  void stopMoveOn(Direction direction);

  // 加积分
  void addScore(size_t s);
  // 取积分
  const size_t getScore() const;
private:
  // 是否在 up、down、left、right 方向上移动
  bool is_move_up = false;
  bool is_move_down = false;
  bool is_move_left = false;
  bool is_move_right = false;

  // 角色当前得分
  size_t score = 0;
};

