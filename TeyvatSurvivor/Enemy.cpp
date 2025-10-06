#include "Enemy.h"

Enemy::Enemy()
  :BaseRole(0, 0, Enemy::WIDTH, Enemy::HEIGHT, 3, 3, 1) {

  // 加载阴影
  loadimage(&img_shadow, L"img/shadow_enemy.png");
  anim_left = std::make_shared<Animation>(L"img/enemy_left_%d.png", 6, 45);
  anim_right = std::make_shared<Animation>(L"img/enemy_right_%d.png", 6, 45);

  // 将敌人放置在地图外边界处的随机位置
  enum class SpawnEdge { Up, Down, Left, Right };
  SpawnEdge edge = SpawnEdge(rand() % 4);
  switch (edge) {
  case SpawnEdge::Up:
    position.x = rand() % WINDOW_WIDTH;
    position.y = -Enemy::HEIGHT;
    break;
  case SpawnEdge::Down:
    position.x = rand() % WINDOW_WIDTH;
    position.y = WINDOW_HEIGHT;
    break;
  case SpawnEdge::Left:
    position.y = rand() % WINDOW_HEIGHT;
    position.x = -Enemy::WIDTH;
    break;
  case SpawnEdge::Right:
    position.y = rand() % WINDOW_HEIGHT;
    position.x = WINDOW_WIDTH;
    break;
  default:break;
  }
}

void Enemy::draw(int delta) {
  // 计算阴影位置(水平居中, 垂直底部偏下)
  int pos_shadow_x = position.x + (Enemy::WIDTH / 2 - Enemy::SHADOW_WIDTH / 2);
  int pos_shadow_y = position.y + Enemy::HEIGHT - 20;
  // 绘制阴影效果 
  putimageAlpha(pos_shadow_x, pos_shadow_y, &img_shadow);

  if (facing_left) {
    anim_left->play(position.x, position.y, delta);
  } else {
    anim_right->play(position.x, position.y, delta);
  }
}

// 敌人移动(随机移动 方便后续拓展: 进入指定范围触发仇恨系统, 也就是拉怪)
void Enemy::move() {
  // 随机移动, 复用写好的追踪移动
  // 先构造一个目标, 目标位置随机
  // 让敌人朝着随机目标移动
  const GameObject2D& obj2
    = EmptyObject2D{ rand() % (WINDOW_WIDTH / 2), rand() % (WINDOW_HEIGHT / 2) };
  this->move(obj2);
}
// 敌人移动(自动追踪 目标物体)
void Enemy::move(const GameObject2D& object) {
  int dir_x = object.getPosition().x - position.x; // x方向的移动单位
  int dir_y = object.getPosition().y - position.y; // y方向的移动单位
  double len_dir = std::sqrt(dir_x * dir_x + dir_y * dir_y); // 移动的实际单位
  if (len_dir != 0) {
    double normalized_x = dir_x / len_dir;
    double normalized_y = dir_y / len_dir;
    position.x += (int)(xspeed * normalized_x);
    position.y += (int)(yspeed * normalized_y);
  }

  if (dir_x < 0) facing_left = true;
  else if (dir_x > 0) facing_left = false;
}

bool Enemy::checkCollision(const GameObject2D& object) const {
  // 在进行2D碰撞检测时，将敌人看作一个矩形，将其它物体看作一个点，检查点是否位于矩形内即可
  std::pair<int, int> this_x_projection
    = { position.x ,position.x + Enemy::WIDTH };
  std::pair<int, int> this_y_projection
    = { position.y, position.y + Enemy::HEIGHT };

  int obj_center_x = object.getPosition().x + object.getSize().cx / 2;
  int obj_center_y = object.getPosition().y + object.getSize().cy / 2;

  return this_x_projection.first <= obj_center_x
    && obj_center_x <= this_x_projection.second
    && this_y_projection.first <= obj_center_y
    && obj_center_y <= this_y_projection.second;
}

void Enemy::hurt(int attack) {
  this->hp -= attack;
  alive = (hp > 0);   // 存活状态根据血量评判
}

bool Enemy::isAlive() const { return this->alive; }

size_t Enemy::getValue() const { return this->value; }


// 静态方法
void Enemy::tryGenerateEnemy(std::vector<std::shared_ptr<Enemy>>& enemies) {
  const int INTERVAL = 100;
  static int counter = 0;
  if ((++counter) % INTERVAL == 0) {
    enemies.push_back(std::move(std::make_shared<Enemy>()));
  }
}
