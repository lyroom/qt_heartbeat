#include "server.h"
#include "clientthread.h"
#include <QThread>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    this->listen(QHostAddress("127.0.0.1"),quint16(66666));
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"has new client connect("<<socketDescriptor<<")";
    socketList.append(socketDescriptor);
    QThread *thread=new QThread();

    ClientThread  *client=new ClientThread(socketDescriptor);
    connect(client,&ClientThread::started,client,&ClientThread::run,Qt::QueuedConnection);
    connect(thread,SIGNAL(finished()),this,SLOT(deleteLater()));
    client->moveToThread(thread);
    thread->start();
    emit client->started();
}
