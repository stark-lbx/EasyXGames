#pragma once
#include "BaseRole.h"
class Enemy : public BaseRole {

public:
  explicit Enemy();

  void draw(int delta) override;
  void move() override;
  // 朝着目标移动
  void move(const GameObject2D& object);

  // 检测与其它物体的碰撞
  bool checkCollision(const GameObject2D& object) const;
  // 受伤
  void hurt(int attack);
  // 检测是否存活
  bool isAlive() const;
  // 获取价值
  size_t getValue() const;

  // 静态方法, 向容器中添加一个敌人
  static void tryGenerateEnemy(std::vector<std::shared_ptr<Enemy>>& enemies);
private:
  constexpr static const int WIDTH = 80;        // 敌人宽度
  constexpr static const int HEIGHT = 80;       // 敌人高度
  constexpr static const int SHADOW_WIDTH = 48; // 阴影宽度
private:
  bool facing_left = false; // 是否朝向左
  size_t value = 1;         // 作为敌人的价值
};

