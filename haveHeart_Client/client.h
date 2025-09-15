#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
class Client : public QObject
{
    Q_OBJECT
private:
    QTimer *timer_heart;
    QTimer *timer_reConn;
    QTcpSocket *socket;
    QString ip;
    quint16 port;
    int count=0;
    bool isFirst=true;

public:
    explicit Client(QObject *parent = nullptr);
    void Toconnect(QString ip, quint16 port);

signals:

private slots:
    void doHeart();
    void isConnection();
    void isDisConnection();
    void reConnection();
};

#endif // CLIENT_H
