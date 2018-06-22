#include "MovePlayer.h"

#include <QtMath>
#include <QTransform>

MovePlayer::MovePlayer()
{
    m_moveto = QVector2D(15.0f, 15.0f); // initial location of player
    m_move = QVector2D(0.0f, 0.0f); // normal move speed
    m_faceto = 0.0f;
    m_face = 0.0f;
}

bool MovePlayer::SetMovePlayer(QPoint mousePos, QPoint centerPos)
{
    bool movement = false;

    float dx = mousePos.x() - centerPos.x();
    float dy = mousePos.y() - centerPos.y();
    float rotation = qAtan2(dy, dx);
    float rdeg = qRadiansToDegrees(rotation);

    if(rdeg >= -180 && rdeg <= -157.5) // Back + Left
    {
        m_moveto.setX(m_moveto.x() + 1.0f);
        m_move.setX(+0.05f);
        m_moveto.setY(m_moveto.y() - 1.0f);
        m_move.setY(-0.05f);
        m_faceto = 135;
        movement = true;
    }
    else if(rdeg >= -157.5 && rdeg <= -112.5) // Left
    {
        m_moveto.setX(m_moveto.x() + 1.0f);
        m_move.setX(+0.05f);
        m_faceto = 90;
        movement = true;
    }
    else if(rdeg >= -112.5 && rdeg <= -67.5) // Forward + left
    {
        m_moveto.setX(m_moveto.x() + 1.0f);
        m_move.setX(+0.05f);
        m_moveto.setY(m_moveto.y() + 1.0f);
        m_move.setY(+0.05f);
        m_faceto = 45;
        movement = true;
    }
    else if(rdeg >= -67.5 && rdeg <= -22.5) // Forward
    {
        m_moveto.setY(m_moveto.y() + 1.0f);
        m_move.setY(+0.05f);
        m_faceto = 0;
        movement = true;
    }
    else if(rdeg >= -22.5 && rdeg <= 22.5) // Forward + right
    {
        m_moveto.setX(m_moveto.x() - 1.0f);
        m_move.setX(-0.05f);
        m_moveto.setY(m_moveto.y() + 1.0f);
        m_move.setY(+0.05f);
        m_faceto = -45;
        movement = true;
    }
    else if(rdeg >= 22.5 && rdeg <= 67.5) // Right
    {
        m_moveto.setX(m_moveto.x() - 1.0f);
        m_move.setX(-0.05f);
        m_faceto = -90;
        movement = true;
    }
    else if(rdeg >= 67.5 && rdeg <= 112.5) // Back + right
    {
        m_moveto.setX(m_moveto.x() - 1.0f);
        m_move.setX(-0.05f);
        m_moveto.setY(m_moveto.y() - 1.0f);
        m_move.setY(-0.05f);
        m_faceto = -135;
        movement = true;
    }
    else if(rdeg >= 112.5 && rdeg <= 157.5) // Backward
    {
        m_moveto.setY(m_moveto.y() - 1.0f);
        m_move.setY(-0.05f);
        m_faceto = 180;
        movement = true;
    }
    else // Back + left
    {
        m_moveto.setX(m_moveto.x() + 1.0f);
        m_move.setX(+0.05f);
        m_moveto.setY(m_moveto.y() - 1.0f);
        m_move.setY(-0.05f);
        m_faceto =135;
        movement = true;
    }
    return movement;
}

bool MovePlayer::UpdatePlayerMovement(Qt3DCore::QEntity *player, Qt3DRender::QCamera *camera)
{
    bool movement = true;
    Qt3DCore::QComponentVector playerVector;
    Qt3DCore::QTransform *playerTransform;
    QVector3D playerPos;

    playerVector = player->components();
    playerTransform = qobject_cast<Qt3DCore::QTransform *>(playerVector.at(2));
    playerPos = playerTransform->translation();

    if(m_face != m_faceto)
    {
        m_face = m_faceto;
        playerTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), m_face));
    }
    // if player has not reached moveto - move player
    if((playerPos.x() != m_moveto.x()) || (playerPos.z() != m_moveto.y()))
    {
        playerTransform->setTranslation(QVector3D(playerPos.x() + m_move.x(), playerPos.y(), playerPos.z() + m_move.y()));
        camera->translateWorld(QVector3D(m_move.x(), 0.0f, m_move.y()));
        //qDebug() << "Player : " << playerPos;
       // qDebug() << "Camera : " << camera->transform()->translation();
    }
    else movement = false;

    if((playerPos.z() <= m_moveto.y() + 0.04f) && (playerPos.z() >= m_moveto.y() - 0.04f)) m_move.setY(0.0f);
    if((playerPos.x() <= m_moveto.x() + 0.04f) && (playerPos.x() >= m_moveto.x() - 0.04f)) m_move.setX(0.0f);

    if((m_move.x() == 0.0f) && (m_move.y() == 0.0f))
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
