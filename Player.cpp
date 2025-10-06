#include "Player.h"

Player::Player(int x, int y, int xs, int ys)
  :BaseRole(x, y, Player::WIDTH, Player::HEIGHT, xs, ys, 1) {
  // ������Ӱ
  loadimage(&img_shadow, L"img/shadow_player.png");
  // ���������ƶ�ʱ����
  anim_left = std::make_shared<Animation>(L"img/player_left_%d.png", 6, 45);
  // ���������ƶ�ʱ����
  anim_right = std::make_shared<Animation>(L"img/player_right_%d.png", 6, 45);
}


void Player::move() {
  // if (is_move_up) pos.y -= yspeed;
  // if (is_move_down)pos.y += yspeed;
  // if (is_move_left) pos.x -= xspeed;
  // if (is_move_right)pos.x += xspeed;
  // �����������б���ƶ�ʱ, ����һ������2���ļ���Ч��(���ɶ���)
  // ������Ҫ��������ۣ����if...else...�����̫��ķ�֧
  // ��ôʹ���������������������

  int dir_x = is_move_right - is_move_left; // x������ƶ���λ
  int dir_y = is_move_down - is_move_up; // y������ƶ���λ
  double len_dir = std::sqrt(dir_x * dir_x + dir_y * dir_y); // �ƶ���ʵ�ʵ�λ
  if (len_dir != 0) {
    double normalized_x = dir_x / len_dir;
    double normalized_y = dir_y / len_dir;
    position.x += (int)(xspeed * normalized_x);
    position.y += (int)(yspeed * normalized_y);
  }

  // �ƶ�ʱ�ı߽��ж�
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
  // ������Ӱλ��(ˮƽ����, ��ֱ�ײ�ƫ��) -> ������ӰЧ�� 
  int pos_shadow_x = position.x + (Player::WIDTH / 2 - Player::SHADOW_WIDTH / 2);
  int pos_shadow_y = position.y + Player::HEIGHT + 8;
  putimageAlpha(pos_shadow_x, pos_shadow_y, &img_shadow);

  // ȷ���ƶ�����
  static bool facing_left = false;
  int dir_x = is_move_right - is_move_left;
  if (dir_x < 0) facing_left = true;
  else if (dir_x > 0) facing_left = false;

  // �����ƶ�����
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
