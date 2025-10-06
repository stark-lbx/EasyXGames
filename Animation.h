#pragma once
#include "common.h"

// 动画类
class Animation {
public:
  // 构造函数
  Animation(LPCTSTR path, int num, int interval);

  // 播放动画
  void play(int x, int y, int delta);
private:
  int timer = 0;          // 动画计时器
  int idx_frame = 0;      // 动画帧索引
  int interval_ms = 0;    // 帧间隔

  // 动画序列帧, frame_list.size(): 动画帧总数
  std::vector<std::shared_ptr<IMAGE>> frame_list;
};