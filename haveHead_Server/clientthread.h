#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTimer>
class ClientThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientThread(qintptr socketDescriptor,QObject *parent = nullptr);
private:
    QTcpSocket *m_socket;
    qintptr m_socketDescriptor;
    QTimer *m_timer;
    int count=0;

public:
    void run();
signals:
    void sendheart();
    void started();
public slots:
    void readSlot();
    void doheart();
};

#endif // CLIENTTHREAD_H
