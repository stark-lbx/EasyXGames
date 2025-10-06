#pragma once
#include "BaseRole.h"
class Enemy : public BaseRole {

public:
  explicit Enemy();

  void draw(int delta) override;
  void move() override;
  // ����Ŀ���ƶ�
  void move(const GameObject2D& object);

  // ����������������ײ
  bool checkCollision(const GameObject2D& object) const;
  // ����
  void hurt(int attack);
  // ����Ƿ���
  bool isAlive() const;
  // ��ȡ��ֵ
  size_t getValue() const;

  // ��̬����, �����������һ������
  static void tryGenerateEnemy(std::vector<std::shared_ptr<Enemy>>& enemies);
private:
  constexpr static const int WIDTH = 80;        // ���˿��
  constexpr static const int HEIGHT = 80;       // ���˸߶�
  constexpr static const int SHADOW_WIDTH = 48; // ��Ӱ���
private:
  bool facing_left = false; // �Ƿ�����
  size_t value = 1;         // ��Ϊ���˵ļ�ֵ
};

