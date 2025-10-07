#pragma once
#include "common.h"

// ͼ����
class Atlas {
public:
  // ��������֡, frame_list.size(): ����֡����
  std::vector<std::shared_ptr<IMAGE>> frame_list;

  // ���캯��
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

// ������
class Animation {
public:
  // ���캯��
  ~Animation() = default;
  Animation(const Atlas* atlas, int terval);

  // ���Ŷ���
  void play(int x, int y, int delta);
private:
  int timer = 0;          // ������ʱ��
  int idx_frame = 0;      // ����֡����
  int interval_ms = 0;    // ֡���
private:
  const Atlas* anim_atlas;
};