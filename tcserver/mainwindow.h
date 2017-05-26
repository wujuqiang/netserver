#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tcsyncserverthread.h"
#include "cristianserverthread.h"

#include "timecode_server.h"
#include "cristian_server.h"

namespace Ui {
class MainWindow;
}

using namespace NetServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();

    void on_btnStart_C_clicked();

    void on_btnStop_clicked();

    void on_btnStop_C_clicked();

private:
    Ui::MainWindow *ui;

    TCSyncServerThread      tcsync_thread_;
    CristianServerThread    cristian_thread_;

    TimeCodeServer* timecode_server_;
    CristianServer* cristian_server_;
};

#endif // MAINWINDOW_H
