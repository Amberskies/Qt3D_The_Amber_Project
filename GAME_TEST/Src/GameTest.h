#pragma once


#include <QObject>
#include <QTime>
#include <QTimer>
#include <Window3D.h>
#include <WorldManager.h>

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
  void TestGameLoop();
  void CleanUpAfterTest();

  Window3D& m_window3D;
  WorldManager *m_worldManager;
  QTimer m_timer;
  QTime m_frameTime;
  float m_deltaTime = 0.0f;
  int m_gameState = 0;
};
