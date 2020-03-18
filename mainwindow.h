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
    void ExecuteShellCommands(QString str);
    void RefreshInfoBatary();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
