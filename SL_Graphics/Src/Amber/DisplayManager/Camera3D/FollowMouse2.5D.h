#ifndef MOVEPLAYER_H
#define MOVEPLAYER_H

#include <QEntity>
#include <QCamera>
#include <QVector2D>



class Move25D
{
    QVector2D moveto;
    QVector2D move;
    float faceto;
    float face;
public:
	Move25D();
    bool setMove25D(QPoint mousePos, QPoint centerPos);
    bool updateMove25D(Qt3DCore::QEntity *player, Qt3DRender::QCamera *camera);
};

#endif // MOVEPLAYER_H
