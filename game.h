#pragma once
#include "common.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

namespace game {
static void run() {
  srand(time(NULL));  //�������������, ������������
  initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
  ExMessage msg;
  bool running = true;

  IMAGE img_background;
  loadimage(&img_background, L"img/background.png");

  mciSendString(L"open mus/bgm.mp3 alias bgm", NULL, 0, NULL); // ���ر�������
  mciSendString(L"play bgm repeat from 0", NULL, 0, NULL);     // ѭ����������
  mciSendString(L"open mus/hit.wav alias hit", NULL, 0, NULL); // ���ش����Ч

  Player player{ 500,500,4,4 };
  std::vector<Bullet> bullets(3); // ��ʼ3���ӵ�
  std::vector<std::shared_ptr<Enemy>> enemies;

  auto frame_time = std::chrono::duration<double, std::milli>(1000.0 / 60.0); //60fps
  BeginBatchDraw();
  while (running) {
    auto start_time = std::chrono::high_resolution_clock::now();
    // 1.��ȡ����
    while (peekmessage(&msg)) {
      // ���ƽ�ɫ�ƶ�����
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

    // 2.���ݴ���    
    player.move();                                  // ��ɫ�ƶ�
    for (int i = 0; i < bullets.size(); i++)
      bullets[i].update(player, i, bullets.size()); // �ӵ�׷��
    Enemy::tryGenerateEnemy(enemies);               // ��������
    for (auto& e : enemies) {
      if (e->checkCollision(player)) {
        // ��⵽��ײ�¼�����, ������Ϸ
        TCHAR result_text[1024];
        _stprintf_s(result_text, L"�ܲ���, ����Ұ��ײ '��' ��! ! !\n ���ĵ÷�Ϊ: %lld", player.getScore());
        MessageBox(GetHWnd(), result_text, L"��Ϸ����", MB_OK);

        // �ͷ���Դ
        EndBatchDraw();
        mciSendString(L"close bgm from 0", NULL, 0, NULL); // ���ش����Ч
        closegraph();
        return (void)0;
      }
      e->move(player);  //�����ƶ�

      for (const Bullet& b : bullets) {
        if (e->checkCollision(b))
          e->hurt(b.getAttack());
      }
    }

    // �����Ƴ��߼�: �Ӻ���ǰ�Ƴ�
    for (int i = enemies.size() - 1; i >= 0; --i) {
      if (enemies[i]->isAlive()) continue;
      // �����, �Ƴ�
      player.addScore(enemies[i]->getValue());
      enemies.erase(enemies.begin() + i);
      mciSendString(L"play hit from 0", NULL, 0, NULL);            // ���Ŵ����Ч
    }

    // 3.���ƽ���
    cleardevice();

    putimage(0, 0, &img_background);              // ����ͼƬ����
    for (auto& e : enemies)e->draw(1000 / 144);   // ���˻���
    player.draw(1000 / 144);                      // ��ɫ����
    for (const auto& b : bullets) b.draw();       // �ӵ�����
    drawPlayerScore(player.getScore());           // ��������

    FlushBatchDraw();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto delta_time = end_time - start_time;
    if (delta_time < frame_time) {
      std::this_thread::sleep_for(frame_time - delta_time);
    }
  }
  EndBatchDraw();
  mciSendString(L"close bgm from 0", NULL, 0, NULL); // ���ش����Ч
  closegraph();
}

} // namespace game