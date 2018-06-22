#pragma once

#include <QObject>
#include <QUdpSocket>

class ServerUDP : public QObject
{
	Q_OBJECT

public:
	explicit ServerUDP(QObject *parent = nullptr);
	~ServerUDP();

	void Test();

public slots:
	void readyRead();

private:
	QUdpSocket * socket = nullptr;
};
