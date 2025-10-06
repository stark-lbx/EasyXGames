#pragma once
#include <graphics.h>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Msimg32.lib")

// 窗体的尺寸
static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;

// 移动方向强枚举
enum class Direction { UP, DOWN, LEFT, RIGHT };

// 处理带有透明度的图片信息
static void putimageAlpha(int x, int y, IMAGE* img) {
  int w = img->getwidth();
  int h = img->getheight();
  AlphaBlend(
    GetImageHDC(NULL), x, y, w, h,
    GetImageHDC(img), 0, 0, w, h,
    { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

// 绘制用户得分
static void drawPlayerScore(size_t score) {
  static TCHAR text[64];
  _stprintf_s(text, L"当前玩家得分: %lld", score);

  setbkmode(TRANSPARENT);
  settextcolor(RGB(255, 85, 185));
  outtextxy(10, 10, text);
}