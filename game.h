#pragma once
#include "common.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

namespace game {
static void run() {
  srand(time(NULL));  //种下随机数种子, 完成真正的随机
  initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
  ExMessage msg;
  bool running = true;

  IMAGE img_background;
  loadimage(&img_background, L"img/background.png");

  mciSendString(L"open mus/bgm.mp3 alias bgm", NULL, 0, NULL); // 加载背景音乐
  mciSendString(L"play bgm repeat from 0", NULL, 0, NULL);     // 循环播放音乐
  mciSendString(L"open mus/hit.wav alias hit", NULL, 0, NULL); // 加载打击音效

  Player player{ 500,500,4,4 };
  std::vector<Bullet> bullets(3); // 初始3颗子弹
  std::vector<std::shared_ptr<Enemy>> enemies;

  auto frame_time = std::chrono::duration<double, std::milli>(1000.0 / 60.0); //60fps
  BeginBatchDraw();
  while (running) {
    auto start_time = std::chrono::high_resolution_clock::now();
    // 1.获取输入
    while (peekmessage(&msg)) {
      // 控制角色移动方向
      if (msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {
        case VK_UP: player.turnTo(Direction::UP); break;
        case VK_DOWN: player.turnTo(Direction::DOWN); break;
        case VK_LEFT: player.turnTo(Direction::LEFT); break;
        case VK_RIGHT:player.turnTo(Direction::RIGHT); break;
        default:break;
        }
      } else if (msg.message == WM_KEYUP) {
        switch (msg.vkcode) {
        case VK_UP: player.stopMoveOn(Direction::UP); break;
        case VK_DOWN: player.stopMoveOn(Direction::DOWN); break;
        case VK_LEFT: player.stopMoveOn(Direction::LEFT); break;
        case VK_RIGHT: player.stopMoveOn(Direction::RIGHT); break;
        default:break;
        }
      }
    }

    // 2.数据处理    
    player.move();                                  // 角色移动
    for (int i = 0; i < bullets.size(); i++)
      bullets[i].update(player, i, bullets.size()); // 子弹追踪
    Enemy::tryGenerateEnemy(enemies);               // 敌人生成
    for (auto& e : enemies) {
      if (e->checkCollision(player)) {
        // 检测到碰撞事件发生, 结束游戏
        TCHAR result_text[1024];
        _stprintf_s(result_text, L"很不幸, 您被野猪撞 '嘎' 了! ! !\n 您的得分为: %lld", player.getScore());
        MessageBox(GetHWnd(), result_text, L"游戏结束", MB_OK);

        // 释放资源
        EndBatchDraw();
        mciSendString(L"close bgm from 0", NULL, 0, NULL); // 加载打击音效
        closegraph();
        return (void)0;
      }
      e->move(player);  //敌人移动

      for (const Bullet& b : bullets) {
        if (e->checkCollision(b))
          e->hurt(b.getAttack());
      }
    }

    // 敌人移除逻辑: 从后向前移除
    for (int i = enemies.size() - 1; i >= 0; --i) {
      if (enemies[i]->isAlive()) continue;
      // 不存活, 移除
      player.addScore(enemies[i]->getValue());
      enemies.erase(enemies.begin() + i);
      mciSendString(L"play hit from 0", NULL, 0, NULL);            // 播放打击音效
    }

    // 3.绘制界面
    cleardevice();

    putimage(0, 0, &img_background);              // 背景图片绘制
    for (auto& e : enemies)e->draw(1000 / 144);   // 敌人绘制
    player.draw(1000 / 144);                      // 角色绘制
    for (const auto& b : bullets) b.draw();       // 子弹绘制
    drawPlayerScore(player.getScore());           // 分数绘制

    FlushBatchDraw();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto delta_time = end_time - start_time;
    if (delta_time < frame_time) {
      std::this_thread::sleep_for(frame_time - delta_time);
    }
  }
  EndBatchDraw();
  mciSendString(L"close bgm from 0", NULL, 0, NULL); // 加载打击音效
  closegraph();
}

} // namespace game