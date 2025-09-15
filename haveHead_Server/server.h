#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:
    QList<qintptr> socketList;

private:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:


public slots:
};

#endif // SERVER_H
