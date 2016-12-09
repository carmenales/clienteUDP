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
    processPendingDatagrams();
}

void MainWindow::processPendingDatagrams(){
    QByteArray datagram;
    do{
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    }while(udpSocket.hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_7); //TODO: Creo que no hace falta
    QString msj;
    in >> msj;

    ui->mensaje->setText(msj);
}
