#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    udpSocket.bind(5824);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_receiveButton_clicked(){
//    QByteArray buffer;
//    QString direccion;
//    int port;

//    buffer = ui->mensaje->toPlainText().toUtf8();
//    direccion = ui->ipAddress->text();
//    port = ui->puerto->text().toInt();

//    udpSocket.writeDatagram(buffer.data(),QHostAddress(direccion), port);

    processPendingDatagrams();
}

void MainWindow::processPendingDatagrams(){
    QByteArray datagram;
    do{
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    }while(udpSocket.hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_7);
    QString msj;
    in >> msj;

    ui->mensaje->setText(msj);
}
