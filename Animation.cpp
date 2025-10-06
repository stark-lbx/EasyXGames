#include "Animation.h"

Animation::Animation(LPCTSTR path, int num, int interval) {
  // 加载图片(路径, 数量, 帧间隔)
  interval_ms = interval;

  TCHAR path_file[256];
  for (size_t i = 0; i < num; ++i) {
    _stprintf_s(path_file, path, i);

    std::shared_ptr<IMAGE> frame = std::make_shared<IMAGE>();
    loadimage(frame.get(), path_file);
    frame_list.push_back(frame);
  }
}

void Animation::play(int x, int y, int delta) {
  timer += delta;
  if (timer >= interval_ms) {
    // 循环播放的核心: 取余
    idx_frame = (idx_frame + 1) % frame_list.size();
    timer = 0;
  }

  putimageAlpha(x, y, frame_list[idx_frame].get());
}
