#pragma once

#include <QObject>
#include <QUdpSocket>

class NetworkManager : public QObject
{
	Q_OBJECT

public:
	NetworkManager(QObject *parent = nullptr);
	~NetworkManager();

	void Test();

public slots:
	void readyRead();

private:
	QUdpSocket * socket = nullptr;

};
