#include "Player.h"

#include <QTransform>
#include <QMesh>
#include <QDiffuseSpecularMaterial> 
#include <Utils/ModelLoader.h>

Player::Player(Qt3DCore::QEntity *rootEntity) :
    m_rootEntity(rootEntity)
{
    Qt3DRender::QMesh *testMesh = ModelLoader::LoadMesh("../Assets/Player/Player1.ply");
	Qt3DExtras::QDiffuseSpecularMaterial *testMaterial = ModelLoader::Material(QColor(QRgb(0xDD10EE)));

    Qt3DCore::QTransform *testTransform = new Qt3DCore::QTransform();
    testTransform->setTranslation(QVector3D(0.0f, 0.5f, 0.5f));

    m_player = new Qt3DCore::QEntity(m_rootEntity);
    m_player->addComponent(testMesh);
    m_player->addComponent(testMaterial);
    m_player->addComponent(testTransform);

	qWarning("Player Created");
}

Player::~Player()
{
    qWarning("Player Shutdown");
}

Qt3DCore::QEntity *Player::getPlayerEntity()
{
    return m_player;
}

Player * Player::getPlayer()
{
	return this;
}

QVector3D Player::getPlayerPosition()
{
	Qt3DCore::QComponentVector playerVector;
	Qt3DCore::QTransform *playerTransform;
	
	playerVector = m_player->components();
	playerTransform = qobject_cast<Qt3DCore::QTransform *>(playerVector.at(2));
	return playerTransform->translation();
}

void Player::setPlayerPosition(QVector3D playerPosition)
{
	Qt3DCore::QComponentVector playerVector;
	Qt3DCore::QTransform *playerTransform;

	playerVector = m_player->components();
	playerTransform = qobject_cast<Qt3DCore::QTransform *>(playerVector.at(2));
	playerTransform->setTranslation(playerPosition);
}

