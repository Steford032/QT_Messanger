#ifndef SERVER_H
#define SERVER_H
#include<QTcpServer>
#include<QTcpSocket>
#include<QVector>

class Server:public QTcpServer{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToCLient(QString str);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void SlotReadyRead();
    void EndingConnection(qintptr socketDescriptor);
};

#endif // SERVER_H
