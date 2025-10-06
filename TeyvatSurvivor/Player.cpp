#include "Player.h"

Player::Player(int x, int y, int xs, int ys)
  :BaseRole(x, y, Player::WIDTH, Player::HEIGHT, xs, ys, 1) {
  // 加载阴影
  loadimage(&img_shadow, L"img/shadow_player.png");
  // 加载向左移动时动画
  anim_left = std::make_shared<Animation>(L"img/player_left_%d.png", 6, 45);
  // 加载向右移动时动画
  anim_right = std::make_shared<Animation>(L"img/player_right_%d.png", 6, 45);
}


void Player::move() {
  // if (is_move_up) pos.y -= yspeed;
  // if (is_move_down)pos.y += yspeed;
  // if (is_move_left) pos.x -= xspeed;
  // if (is_move_right)pos.x += xspeed;
  // 上述代码如果斜着移动时, 会有一个根号2倍的加速效果(勾股定理)
  // 所以需要分情况讨论，如果if...else...则会有太多的分支
  // 那么使用向量来解决这个问题就行

  int dir_x = is_move_right - is_move_left; // x方向的移动单位
  int dir_y = is_move_down - is_move_up; // y方向的移动单位
  double len_dir = std::sqrt(dir_x * dir_x + dir_y * dir_y); // 移动的实际单位
  if (len_dir != 0) {
    double normalized_x = dir_x / len_dir;
    double normalized_y = dir_y / len_dir;
    position.x += (int)(xspeed * normalized_x);
    position.y += (int)(yspeed * normalized_y);
  }

  // 移动时的边界判断
  if (position.x < 0)
    position.x = 0;
  if (position.y < 0)
    position.y = 0;
  if (position.x + Player::WIDTH > WINDOW_WIDTH)
    position.x = WINDOW_WIDTH - Player::WIDTH;
  if (position.y + Player::HEIGHT > WINDOW_HEIGHT)
    position.y = WINDOW_HEIGHT - Player::HEIGHT;
}

void Player::draw(int delta) {
  // 计算阴影位置(水平居中, 垂直底部偏下) -> 绘制阴影效果 
  int pos_shadow_x = position.x + (Player::WIDTH / 2 - Player::SHADOW_WIDTH / 2);
  int pos_shadow_y = position.y + Player::HEIGHT + 8;
  putimageAlpha(pos_shadow_x, pos_shadow_y, &img_shadow);

  // 确定移动朝向
  static bool facing_left = false;
  int dir_x = is_move_right - is_move_left;
  if (dir_x < 0) facing_left = true;
  else if (dir_x > 0) facing_left = false;

  // 播放移动动画
  if (facing_left) {
    anim_left->play(position.x, position.y, delta);
  } else {
    anim_right->play(position.x, position.y, delta);
  }
}

void Player::turnTo(Direction direction) {
  switch (direction) {
  case Direction::UP:
    is_move_up = true;
    is_move_down = false;
    break;
  case Direction::DOWN:
    is_move_up = false;
    is_move_down = true;
    break;
  case Direction::LEFT:
    is_move_left = true;
    is_move_right = false;
    break;
  case Direction::RIGHT:
    is_move_left = false;
    is_move_right = true;
    break;
  default: break;
  }
}

void Player::stopMoveOn(Direction direction) {
  switch (direction) {
  case Direction::UP:
    is_move_up = false; break;
  case Direction::DOWN:
    is_move_down = false; break;
  case Direction::LEFT:
    is_move_left = false; break;
  case Direction::RIGHT:
    is_move_right = false; break;
  default:break;
  }
}

void Player::addScore(size_t s) { this->score += s; }

const size_t Player::getScore() const { return this->score; }
