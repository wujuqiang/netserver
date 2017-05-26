#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ipaddr.h"
#include "tcpclient.h"
#include "udpclient.h"
#include "utility.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timecode_sender = NULL;
    cristian_sender = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConn_clicked()
{
    IPAddr addr;
    addr.SetIPAddr("127.0.0.1");
    addr.SetPort(54321);

    TCPClient client;
    client.SetPeerAddr(addr);
    FDConnection * conn = client.StartConnect();

    timecode_sender = new Sender(conn);
    ui->btnConn->setEnabled(false);
}

void MainWindow::on_btnSend_clicked()
{
    NS_INF("To Send");

    char temp_get_tc[] = "1212345";
    temp_get_tc[0]=0x02;
    temp_get_tc[1]=5;

    char temp_sync_tc[] = "121234567890000T11:22:33:44T1";
    temp_sync_tc[0]=0x01;
    temp_sync_tc[1]=27;
    if (timecode_sender) {
        int32_t len = timecode_sender->Write((unsigned char *)temp_sync_tc, strlen(temp_sync_tc));
        printf("send %d bytes", len);
    }
}

void MainWindow::on_btnClose_clicked()
{
    if (timecode_sender) {
        timecode_sender->Close();
        delete timecode_sender;
        timecode_sender = NULL;
        ui->btnConn->setEnabled(true);
    }
}

void MainWindow::on_btnConn_C_clicked()
{
    IPAddr addr;
    addr.SetIPAddr("127.0.0.1");
    addr.SetPort(54320);

    UDPClient client;
    client.SetPeerAddr(addr);
    FDConnection * conn = client.StartConnect();

    if (conn) {
        cristian_sender = new Sender(conn);
        ui->btnConn_C->setEnabled(false);
    }
}

void MainWindow::on_btnSend_C_clicked()
{
    if (cristian_sender) {
        int32_t len = cristian_sender->Write((unsigned char *)"Hello World", strlen("Hello World"));
        printf("send %d bytes", len);
    }
}

void MainWindow::on_btnClose_C_clicked()
{
    if (cristian_sender) {
        cristian_sender->Close();
        delete cristian_sender;
        cristian_sender = NULL;
        ui->btnConn_C->setEnabled(true);
    }
}
