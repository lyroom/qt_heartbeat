#include "clientthread.h"

ClientThread::ClientThread(qintptr socketDescriptor, QObject *parent) : QObject(parent)
{
    m_socketDescriptor=socketDescriptor;

}

void ClientThread::run()
{
    m_socket=new QTcpSocket(this);
    m_timer=new QTimer(this);
    m_timer->setInterval(1000);
    m_socket->setSocketDescriptor(m_socketDescriptor);
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readSlot()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(doheart()));
    m_timer->start();
}

void ClientThread::readSlot()
{
    count=0;//有数据包时，重置心跳数
    QByteArray ricvByte=m_socket->readAll();
    QString str=ricvByte.toStdString().c_str();
    qDebug()<<str;
    QStringList strlist=str.split("$");
    if(strlist[0]=="heartPackage")//区分消息类型
    {
        qDebug()<<"this is heart Package";
    }
    else {
        qDebug()<<"this is msg Package";
    }
}

//心跳执行与判断，30秒无数据包判断为断开连接
void ClientThread::doheart()
{
    count++;
    qDebug()<<count;
    if(count>30)
    {
        qDebug()<<"客户端断开连接,准备重连...（"<<m_socketDescriptor<<"）";
        count=0;
        m_timer->stop();
        m_socket->abort();//断开连接；
    }
}



