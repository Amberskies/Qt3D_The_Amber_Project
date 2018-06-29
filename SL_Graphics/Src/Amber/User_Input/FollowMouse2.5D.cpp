#include "FollowMouse2.5D.h"

#include <QtMath>
#include <QTransform>

Move25D::Move25D()
{
    moveto = QVector2D(15.0f, 15.0f); // initial location of player
    move = QVector2D(0.0f, 0.0f); // normal move speed
    faceto = 0.0f;
    face = 0.0f;
}

bool Move25D::setMove25D(QPoint mousePos, QPoint centerPos)
{
    bool movement = false;

    float dx = mousePos.x() - centerPos.x();
    float dy = mousePos.y() - centerPos.y();

    float rotation = qAtan2(dy, dx);
    float rdeg = qRadiansToDegrees(rotation);

    if(rdeg >= -180 && rdeg <= -157.5) // Back + Left
    {
        moveto.setX(moveto.x() + 1.0f);
        move.setX(+0.05f);
        moveto.setY(moveto.y() - 1.0f);
        move.setY(-0.05f);
        faceto = 135;
        movement = true;
    }
    else if(rdeg >= -157.5 && rdeg <= -112.5) // Left
    {
        moveto.setX(moveto.x() + 1.0f);
        move.setX(+0.05f);
        faceto = 90;
        movement = true;
    }
    else if(rdeg >= -112.5 && rdeg <= -67.5) // Forward + left
    {
        moveto.setX(moveto.x() + 1.0f);
        move.setX(+0.05f);
        moveto.setY(moveto.y() + 1.0f);
        move.setY(+0.05f);
        faceto = 45;
        movement = true;
    }
    else if(rdeg >= -67.5 && rdeg <= -22.5) // Forward
    {
        moveto.setY(moveto.y() + 1.0f);
        move.setY(+0.05f);
        faceto = 0;
        movement = true;
    }
    else if(rdeg >= -22.5 && rdeg <= 22.5) // Forward + right
    {
        moveto.setX(moveto.x() - 1.0f);
        move.setX(-0.05f);
        moveto.setY(moveto.y() + 1.0f);
        move.setY(+0.05f);
        faceto = -45;
        movement = true;
    }
    else if(rdeg >= 22.5 && rdeg <= 67.5) // Right
    {
        moveto.setX(moveto.x() - 1.0f);
        move.setX(-0.05f);
        faceto = -90;
        movement = true;
    }
    else if(rdeg >= 67.5 && rdeg <= 112.5) // Back + right
    {
        moveto.setX(moveto.x() - 1.0f);
        move.setX(-0.05f);
        moveto.setY(moveto.y() - 1.0f);
        move.setY(-0.05f);
        faceto = -135;
        movement = true;
    }
    else if(rdeg >= 112.5 && rdeg <= 157.5) // Backward
    {
        moveto.setY(moveto.y() - 1.0f);
        move.setY(-0.05f);
        faceto = 180;
        movement = true;
    }
    else // Back + left
    {
        moveto.setX(moveto.x() + 1.0f);
        move.setX(+0.05f);
        moveto.setY(moveto.y() - 1.0f);
        move.setY(-0.05f);
        faceto =135;
        movement = true;
    }

    return movement;
}

bool Move25D::updateMove25D(Qt3DCore::QEntity *player, Qt3DRender::QCamera *camera)
{
    bool movement = true;
    Qt3DCore::QComponentVector playerVector;
    Qt3DCore::QTransform *playerTransform;
    QVector3D playerPos;

    playerVector = player->components();
    playerTransform = qobject_cast<Qt3DCore::QTransform *>(playerVector.at(2));
    playerPos = playerTransform->translation();

    if(face != faceto)
    {
        face = faceto;
        playerTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), face));
    }
    // if player has not reached moveto - move player
    if((playerPos.x() != moveto.x()) || (playerPos.z() != moveto.y()))
    {
        playerTransform->setTranslation(QVector3D(playerPos.x() + move.x(), playerPos.y(), playerPos.z() + move.y()));
        camera->translateWorld(QVector3D(move.x(), 0.0f, move.y()));
        //qDebug() << "Player : " << playerPos;
       // qDebug() << "Camera : " << camera->transform()->translation();
    }
    else movement = false;

    if((playerPos.z() <= moveto.y() + 0.04f) && (playerPos.z() >= moveto.y() - 0.04f)) move.setY(0.0f);
    if((playerPos.x() <= moveto.x() + 0.04f) && (playerPos.x() >= moveto.x() - 0.04f)) move.setX(0.0f);

    if((move.x() == 0.0f) && (move.y() == 0.0f))
    {
        movement = false; // sanity check.

        // DO : reset positions to tile center to avoid the diagonal error in distance move ... etc.
        //reset player position to tile center
        int t;
        t = playerPos.x();
        playerPos.setX((float)t);
        t = playerPos.z();
        playerPos.setZ((float)t);
    }
    return movement;
}
