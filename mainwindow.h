#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QProgressBar>
#include <QTimer>
#include <smsform.h>
#include <QFile>

namespace Ui {
class MainWindow;    
}

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//    void ExecuteShellCommands(QString str);
    ~MainWindow();

private slots:
    void WakeUphone();
    void OpenWhatsApp();
    void OpenWebPage();
    void ExecCommand();
    QString ExecuteShellCommands(QString str, int param);
    void RefreshInfoBatary();
    void OpenSmsForm();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
