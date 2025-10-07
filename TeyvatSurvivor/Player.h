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

  // ��ɫת��
  void turnTo(Direction direction);
  // ֹͣ��ɫ��ĳ������ƶ���Ϊ
  void stopMoveOn(Direction direction);

  // �ӻ���
  void addScore(size_t s);
  // ȡ����
  const size_t getScore() const;
private:
  // �Ƿ��� up��down��left��right �������ƶ�
  bool is_move_up = false;
  bool is_move_down = false;
  bool is_move_left = false;
  bool is_move_right = false;

  // ��ɫ��ǰ�÷�
  size_t score = 0;
};

