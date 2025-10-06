#include "BaseRole.h"

BaseRole::BaseRole(int x, int y, int w, int h)
  : GameObject2D(x, y, w, h)
  , alive(true), hp(1)
  , xspeed(1), yspeed(1)
  , img_shadow()
  , anim_left(nullptr)
  , anim_right(nullptr)
  , anim_up(nullptr)
  , anim_down(nullptr) {}

BaseRole::BaseRole(int x, int y, int w, int h, int xs, int ys)
  : GameObject2D(x, y, w, h)
  , alive(true), hp(1)
  , xspeed(xs), yspeed(ys)
  , img_shadow()
  , anim_left(nullptr)
  , anim_right(nullptr)
  , anim_up(nullptr)
  , anim_down(nullptr) {}

BaseRole::BaseRole(int x, int y, int w, int h, int xs, int ys, int _hp)
  : GameObject2D(x, y, w, h)
  , alive(true), hp(_hp)
  , xspeed(xs), yspeed(ys)
  , img_shadow()
  , anim_left(nullptr)
  , anim_right(nullptr)
  , anim_up(nullptr)
  , anim_down(nullptr) {}
