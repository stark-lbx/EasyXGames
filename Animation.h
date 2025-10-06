#pragma once
#include "common.h"

// ������
class Animation {
public:
  // ���캯��
  Animation(LPCTSTR path, int num, int interval);

  // ���Ŷ���
  void play(int x, int y, int delta);
private:
  int timer = 0;          // ������ʱ��
  int idx_frame = 0;      // ����֡����
  int interval_ms = 0;    // ֡���

  // ��������֡, frame_list.size(): ����֡����
  std::vector<std::shared_ptr<IMAGE>> frame_list;
};