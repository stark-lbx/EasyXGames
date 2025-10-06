#pragma once
#include "BaseWeapon.h"
#include "BaseRole.h"
#include <atomic>

class Bullet :public BaseWeapon {
public:
  Bullet();
  Bullet(const BaseRole* prole);
  Bullet(const Bullet& oth);
  ~Bullet() = default;

  void bind(const BaseRole* prole) override;
  void draw() const override;
  void update() override;

private:
  constexpr static const int RADIUS = 10;     // Բ���ӵ��뾶
  static std::atomic<int> M_count;            // Բ���ӵ�����
private:
  const BaseRole* bind_role;            // �󶨵Ľ�ɫ

  // TODO: ����ĵڼ���Ӧ�ø�bind_role��, Ҳ�����γ�һ��ӳ�������M_countҲ��Ӧ����bind_role���, ���ڸ�
  // Ҫôֱ�ӽ�Player��Ϊ�����࣬Ȼ�󽫾�����ӳ����, ��ֻ����ôһ����ɫ������ֱ�Ӽ�¼�ľ�����֮��Ӧ��
  int this_id;                          // ��ǰ�ǵڼ�������
};

