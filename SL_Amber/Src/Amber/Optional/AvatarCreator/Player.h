#ifndef PLAYER_H
#define PLAYER_H


#include <QEntity>
#include <QTransform>

class Player : public Qt3DCore::QEntity
{

    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_player;
public:
    explicit Player(QEntity *rootEntity);
    virtual ~Player();

	void updatePlayer();

	// getters
	Player * getPlayer();
	QVector3D getPlayerPosition();
	float getRotY();
	float getRotZ();

	//setters
	void setPlayerPosition(QVector3D playerPosition);
	void setDeltaTime(float dt);

private:
	Qt3DCore::QTransform *m_playerTransform;
	float m_deltaTime;
	float m_runSpeed;
	float m_turnSpeed;
	float m_currentSpeed;
	float m_currentTurnSpeed;
};

#endif // PLAYER_H
