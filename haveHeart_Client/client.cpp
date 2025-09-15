#include "client.h"
#include <QDebug>


Client::Client(QObject *parent) : QObject(parent)
{
    qDebug()<<"初始化客户端";
    timer_heart=new QTimer(this);
    timer_reConn=new QTimer(this);
    socket=new QTcpSocket(this);
    timer_heart->setInterval(15000);//设置定时器间隔15秒
    connect(timer_heart,SIGNAL(timeout()),this,SLOT(doHeart()));//定时器超时发送心跳
    connect(socket,SIGNAL(connected()),this,SLOT(isConnection()));//连接
    connect(socket,SIGNAL(disconnected()),this,SLOT(isDisConnection()));//断线
}

void Client::Toconnect(QString ip, quint16 port)
{
    this->ip=ip;
    this->port=port;
    socket->connectToHost(ip,port);
}

void Client::doHeart()
{
    qDebug()<<"15s了，发送心跳包";
    QString heart="heartPackage$";
    QByteArray ba=heart.toLocal8Bit();
    socket->write(ba);
}

void Client::isConnection()
{
    qDebug()<<"连接服务器成功";
    count=100;//心跳设置为100(大于10即可)，让重连函数停止
    timer_heart->start();//开始心跳
}

void Client::isDisConnection()
{
    count=0;
    qDebug()<<"*******断开*******";
    timer_heart->stop();//断开连接后心跳停止
    timer_reConn->setInterval(5000);//每5秒钟自动重连 10次后停止
    connect(timer_reConn,SIGNAL(timeout()),this,SLOT(reConnection()));
    timer_reConn->start();
}

void Client::reConnection()
{
    count++;
    if(count<=10)
    {
        qDebug()<<"断开连接,准备重连...(第"<<count<<"次)";
        socket->connectToHost(ip,port);
    }
    else {
        timer_reConn->stop();//超过10次停止重连
    }
}




