#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpclient.h"

using namespace NetServer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timecode_server_ = NULL;
    cristian_server_ = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    //::tcsync_thread_.start();

    qDebug() << "TimeCodeServer ---->";

    timecode_server_ = new TimeCodeServer();
    timecode_server_->Start();

    ui->btnStart->setEnabled(false);
}

void MainWindow::on_btnStart_C_clicked()
{
    //::cristian_thread_.start();

    qDebug() << "CristianServer ---->";

    cristian_server_ = new CristianServer();
    cristian_server_->Start();

    ui->btnStart_C->setEnabled(false);
}

void MainWindow::on_btnStop_clicked()
{
    if (timecode_server_) {
        timecode_server_->Stop();
        delete timecode_server_;
        timecode_server_ = NULL;
        ui->btnStart->setEnabled(true);
        qDebug() << "TimeCodeServer <----";
    }
}

void MainWindow::on_btnStop_C_clicked()
{
    if (cristian_server_) {
        cristian_server_->Stop();
        delete cristian_server_;
        cristian_server_ = NULL;
        ui->btnStart_C->setEnabled(true);
        qDebug() << "CristianServer <----";
    }
}
