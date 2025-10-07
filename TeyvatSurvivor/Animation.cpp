#include "Animation.h"


Animation::Animation(const Atlas* atlas, int terval)
  : anim_atlas(const_cast<Atlas*>(atlas))
  , interval_ms(terval) {}

void Animation::play(int x, int y, int delta) {
  timer += delta;
  if (timer >= interval_ms) {
    // 循环播放的核心: 取余
    idx_frame = (idx_frame + 1) % anim_atlas->frame_list.size();
    timer = 0;
  }

  putimageAlpha(x, y, anim_atlas->frame_list[idx_frame].get());
}
