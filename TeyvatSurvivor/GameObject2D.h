#pragma once
#include "common.h"

class GameObject2D {
public:
  explicit GameObject2D(int x, int y, int w, int h);
  GameObject2D() = default;
  virtual ~GameObject2D() = 0;

  // 获取对象位置
  virtual const POINT& getPosition() const;
  // 设置对象位置
  virtual void setPosition(int x, int y);

  // 获取对象尺寸
  virtual const SIZE& getSize() const;
  // 设置对象尺寸
  virtual void setSize(int w, int h);
protected:
  POINT position;   // 位置
  SIZE size;        // 尺寸
};


// 目前用途: 索敌
class EmptyObject2D :public GameObject2D {
public:
  ~EmptyObject2D() = default;
  EmptyObject2D(int x, int y) :GameObject2D(x, y, 0, 0) {}
};
