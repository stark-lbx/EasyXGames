#pragma once
#include "common.h"

class GameObject2D {
public:
  explicit GameObject2D(int x, int y, int w, int h);
  GameObject2D() = default;
  virtual ~GameObject2D() = 0;

  // ��ȡ����λ��
  virtual const POINT& getPosition() const;
  // ���ö���λ��
  virtual void setPosition(int x, int y);

  // ��ȡ����ߴ�
  virtual const SIZE& getSize() const;
  // ���ö���ߴ�
  virtual void setSize(int w, int h);
protected:
  POINT position;   // λ��
  SIZE size;        // �ߴ�
};


// Ŀǰ��;: ����
class EmptyObject2D :public GameObject2D {
public:
  ~EmptyObject2D() = default;
  EmptyObject2D(int x, int y) :GameObject2D(x, y, 0, 0) {}
};
