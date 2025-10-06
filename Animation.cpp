#include "Animation.h"

Animation::Animation(LPCTSTR path, int num, int interval) {
  // ����ͼƬ(·��, ����, ֡���)
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
    // ѭ�����ŵĺ���: ȡ��
    idx_frame = (idx_frame + 1) % frame_list.size();
    timer = 0;
  }

  putimageAlpha(x, y, frame_list[idx_frame].get());
}
