#pragma once
#include "common.h"

// 图集类
class Atlas {
public:
  // 动画序列帧, frame_list.size(): 动画帧总数
  std::vector<std::shared_ptr<IMAGE>> frame_list;

  // 构造函数
  Atlas(LPCTSTR path, int num) {
    TCHAR path_file[256];
    for (size_t i = 0; i < num; ++i) {
      _stprintf_s(path_file, path, i);

      std::unique_ptr<IMAGE> frame = std::make_unique<IMAGE>();
      loadimage(frame.get(), path_file);
      frame_list.push_back(std::move(frame));
    }
  }
};

// 动画类
class Animation {
public:
  // 构造函数
  ~Animation() = default;
  Animation(const Atlas* atlas, int terval);

  // 播放动画
  void play(int x, int y, int delta);
private:
  int timer = 0;          // 动画计时器
  int idx_frame = 0;      // 动画帧索引
  int interval_ms = 0;    // 帧间隔
private:
  const Atlas* anim_atlas;
};