#pragma once

#include <Window3D.h>
#include <QObject>
#include <QTime>
#include <QTimer>

class GameTest : public QObject {
  Q_OBJECT

 public:
  GameTest(class Window3D& window3D);
  ~GameTest();

  void Go();

  // Getters
  // Setters

 private slots:
  void MainGameLoop();

 private:
  void Test();
  void TestGameLoop();
  void CleanUpAfterTest();

  Window3D& m_window3D;
  QTimer m_timer;
  QTime m_frameTime;
  float m_deltaTime = 0.0f;
  int m_gameState = 1;
};
