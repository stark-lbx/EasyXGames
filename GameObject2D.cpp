#include "GameObject2D.h"

// 即时析构是纯虚函数, 也必须要提供实现
GameObject2D::~GameObject2D() {}

GameObject2D::GameObject2D(int x, int y, int w, int h)
  : position{ x,y }, size{ w,h } {}

const POINT& GameObject2D::getPosition() const { return position; }

void GameObject2D::setPosition(int x, int y) { position.x = x; position.y = y; }

const SIZE& GameObject2D::getSize() const { return size; }

void GameObject2D::setSize(int w, int h) { size.cx = w, size.cy = h; }
