#ifndef MOVEPLAYER_H
#define MOVEPLAYER_H

#include <QEntity>
#include <QCamera>
#include <QVector2D>

class MovePlayer
{
public:
    MovePlayer();
    bool UpdatePlayerMovement(Qt3DCore::QEntity *player, Qt3DRender::QCamera *camera);

	// Getters

	// Setters
	bool SetMovePlayer(QPoint mousePos, QPoint centerPos);

private:
	QVector2D m_moveto;
	QVector2D m_move;
	float m_faceto;
	float m_face;
};

#endif // MOVEPLAYER_H
