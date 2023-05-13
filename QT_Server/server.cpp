#include "server.h"
Server::Server(){
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug()<<"Server is started...";
    }

    else{
        qDebug()<<"Error whiile starting server.";
    }
}

void Server:: incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead,this, &Server::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug()<<"Client "<<socketDescriptor<<" was connected!";
}

void Server::SlotReadyRead(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_1);
    if(in.status() == QDataStream::Ok){
        QString str;
        in>>str;
        qDebug()<<"Client "<<socket->socketDescriptor()<<": "<<str;
        SendToCLient(str);
    }
    else{
        qDebug()<<"DataStream error";
    }
}

void Server::SendToCLient(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_1);
    out<<str;
    for(int i = 0; i<Sockets.size(); i++){
        Sockets[i]->write(Data);
    }


}

void Server:: EndingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    qDebug()<<"Client "<<socketDescriptor<<" was disconnected!";
    //Sockets.clear();
    Sockets.pop_back();
}
