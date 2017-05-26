#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "fdconnection.h"
#include "sender.h"

using namespace NetServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnConn_clicked();

    void on_btnSend_clicked();

    void on_btnClose_clicked();

    void on_btnConn_C_clicked();

    void on_btnSend_C_clicked();

    void on_btnClose_C_clicked();

private:
    Ui::MainWindow *ui;

    Sender *       timecode_sender;
    Sender *       cristian_sender;
};

#endif // MAINWINDOW_H
