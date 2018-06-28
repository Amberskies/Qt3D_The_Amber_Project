#include "Player.h"

#include <Utils/Input.h>
#include <Utils/ModelLoader.h>
#include <QDiffuseSpecularMaterial>
#include <QMesh>
#include <QTextureMaterial>
#include <QtMath>

Player::Player(QEntity *rootEntity) 
	: QEntity(rootEntity)
	, m_deltaTime(0.0f)
    , m_runSpeed(100.0f)
    , m_turnSpeed(100.0f)
    , m_currentSpeed(0.0f)
    , m_currentTurnSpeed(0.0f) {
  Qt3DRender::QMesh *testMesh =
      ModelLoader::LoadMesh("../Assets/Player/Person.obj");
  Qt3DExtras::QTextureMaterial *testMaterial =
      ModelLoader::Texture("../Assets/Player/playerTexture.png");

  m_playerTransform = new Qt3DCore::QTransform();
  m_playerTransform->setTranslation(QVector3D(0.0f, 0.5f, 0.5f));

  //this = new Qt3DCore::QEntity(m_rootEntity);
  this->addComponent(testMesh);
  this->addComponent(testMaterial);
  this->addComponent(m_playerTransform);

  qWarning("Player Created");
}

Player::~Player() { qWarning("Player Shutdown"); }

void Player::updatePlayer() {
  if (Input::keyPressed(Qt::Key_W)) {
	  qDebug() << "W has been pressed";
    m_currentSpeed = m_runSpeed;
  } else if (Input::keyPressed(Qt::Key_S)) {
    m_currentSpeed = -m_runSpeed;

  } else {
    m_currentSpeed = 0.0f;
  }

  if (Input::keyPressed(Qt::Key_A)) {
    m_currentTurnSpeed = -m_turnSpeed;
  } else if (Input::keyPressed(Qt::Key_D)) {
    m_currentTurnSpeed = m_turnSpeed;

  } else {
    m_currentTurnSpeed = 0.0f;
  }

  m_playerTransform->setRotationY(m_currentTurnSpeed * m_deltaTime);

  float distance = m_currentSpeed * m_deltaTime;
  float dx = distance * qSin(qDegreesToRadians(this->getRotY()));
  float dz = distance * qCos(qDegreesToRadians(this->getRotZ()));

  QVector3D currentTranslation = m_playerTransform->translation();
  m_playerTransform->setTranslation(QVector3D(
      currentTranslation.x() + (dx * m_deltaTime), currentTranslation.y(),
      currentTranslation.z() + (dz * m_deltaTime)));
}

// ************Getters***********************

Player *Player::getPlayer() { return this; }

QVector3D Player::getPlayerPosition() {
  return m_playerTransform->translation();
}

float Player::getRotY() { return m_playerTransform->rotationY(); }

float Player::getRotZ() { return m_playerTransform->rotationZ(); }

// **************Setters************************

void Player::setPlayerPosition(QVector3D playerPosition) {
  m_playerTransform->setTranslation(playerPosition);
}

void Player::setDeltaTime(float dt) { m_deltaTime = dt; }
