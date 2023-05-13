#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::SlotRedyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
    ui->textBrowser->append(QTime::currentTime().toString() + "  You were succesfully connected!");
}



void MainWindow::SendToServer(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_1);
    out<<str;
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::SlotRedyRead()
{

    QString strDescriptor = QString::number(socket->socketDescriptor());
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_1);
    if(in.status()==QDataStream::Ok){
        QString str;
        in>>str;

        ui->textBrowser->append(QTime::currentTime().toString()+ " " +strDescriptor+
                                " " + str );
    }
    else{
        ui->textBrowser->append("Read error");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text()!="" && ui->lineEdit->text()!=" ")
    SendToServer(ui->lineEdit->text());
    else{
        QMessageBox::warning(this, "Warning","This line can't be empty");
    }
}

void MainWindow::on_lineEdit_returnPressed()
{
    if(ui->lineEdit->text()!="" && ui->lineEdit->text()!=" "){
    SendToServer(ui->lineEdit->text());
    }
    else{
        QMessageBox::warning(this, "Warning","This line can't be empty");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    socket->disconnect();
    qApp->exit();
}

