#include "Enemy.h"

const Atlas Enemy::ATLAS_LEFT = { L"img/enemy_left_%d.png",6 };
const Atlas Enemy::ATLAS_RIGHT = { L"img/enemy_right_%d.png",6 };

Enemy::Enemy()
  :BaseRole(0, 0, Enemy::WIDTH, Enemy::HEIGHT, 3, 3, 1) {

  // ������Ӱ
  loadimage(&img_shadow, L"img/shadow_enemy.png");
  anim_left = std::make_shared<Animation>(&Enemy::ATLAS_LEFT, 45);
  anim_right = std::make_shared<Animation>(&Enemy::ATLAS_RIGHT, 45);

  // �����˷����ڵ�ͼ��߽紦�����λ��
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
  // ������Ӱλ��(ˮƽ����, ��ֱ�ײ�ƫ��)
  int pos_shadow_x = position.x + (Enemy::WIDTH / 2 - Enemy::SHADOW_WIDTH / 2);
  int pos_shadow_y = position.y + Enemy::HEIGHT - 20;
  // ������ӰЧ�� 
  putimageAlpha(pos_shadow_x, pos_shadow_y, &img_shadow);

  if (facing_left) {
    anim_left->play(position.x, position.y, delta);
  } else {
    anim_right->play(position.x, position.y, delta);
  }
}

// �����ƶ�(����ƶ� ���������չ: ����ָ����Χ�������ϵͳ, Ҳ��������)
void Enemy::move() {
  // ����ƶ�, ����д�õ�׷���ƶ�
  // �ȹ���һ��Ŀ��, Ŀ��λ�����
  // �õ��˳������Ŀ���ƶ�
  const GameObject2D& obj2
    = EmptyObject2D{ rand() % (WINDOW_WIDTH / 2), rand() % (WINDOW_HEIGHT / 2) };
  this->move(obj2);
}
// �����ƶ�(�Զ�׷�� Ŀ������)
void Enemy::move(const GameObject2D& object) {
  int dir_x = object.getPosition().x - position.x; // x������ƶ���λ
  int dir_y = object.getPosition().y - position.y; // y������ƶ���λ
  double len_dir = std::sqrt(dir_x * dir_x + dir_y * dir_y); // �ƶ���ʵ�ʵ�λ
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
  // �ڽ���2D��ײ���ʱ�������˿���һ�����Σ����������忴��һ���㣬�����Ƿ�λ�ھ����ڼ���
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
  alive = (hp > 0);   // ���״̬����Ѫ������
}

bool Enemy::isAlive() const { return this->alive; }

size_t Enemy::getValue() const { return this->value; }


// ��̬����
void Enemy::tryGenerateEnemy(std::vector<std::shared_ptr<Enemy>>& enemies) {
  const int INTERVAL = 100;
  static int counter = 0;
  if ((++counter) % INTERVAL == 0) {
    enemies.push_back(std::move(std::make_shared<Enemy>()));
  }
}
