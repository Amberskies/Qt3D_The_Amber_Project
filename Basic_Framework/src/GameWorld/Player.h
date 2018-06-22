#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QEntity>

class Player : public QObject
{
    Q_OBJECT

public:
	explicit Player(Qt3DCore::QEntity *rootEntity);
	virtual ~Player();

	// getters
	Qt3DCore::QEntity *GetPlayer();
	QVector3D GetPlayerPosition();

	//setters
	void SetPlayerPosition(QVector3D playerPosition);
private:
	Qt3DCore::QEntity *m_rootEntity;
	Qt3DCore::QEntity *m_player;

};

#endif // PLAYER_H
