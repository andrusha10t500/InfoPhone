#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{        
    QProcess qp;
    QString proc;
    const int waitTime=15000;
    QString cmd("su -c 'cat /sys/class/power_supply/battery/capacity'");
    QTimer * t = new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(RefreshInfoBatary()));

//    ui->horizontalLayout_2->setGeometry();

//    qp.start("/bin/bash connectDevice.sh", QStringList() << cmd);
    qp.start("/bin/bash connectDevice.sh \"" + cmd + "\"");
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);

    proc = qp.readAll();

    ui->setupUi(this);    
    ui->progressBar_2->setMinimum(0);
    ui->progressBar_2->setMaximum(100);

    if(proc.toInt() > 0){
        ui->label_2->setText("Информация о батарее");
        ui->progressBar_2->setValue(proc.toInt());
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        t->start(10000);
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(WakeUphone()));
        connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(OpenWhatsApp()));
//        QString str("adb shell am start -a android.intent.action.VIEW http://www.google.com");
//        QString str(ui->lineEdit->text());
        connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(OpenWebPage()));
        connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ExecCommand()));
        connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(OpenSmsForm()));

    } else {
        ui->label_2->setText("Телефон не подключен");
        ui->progressBar_2->setValue(0);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }
}

void MainWindow::WakeUphone() {
    this->ExecuteShellCommands("input keyevent 26");
    //adb shell input keyevent 26
}

void MainWindow::OpenWhatsApp() {
    this->ExecuteShellCommands("am start -n com.whatsapp/com.whatsapp.Conversation");
    //adb shell am start -n com.whatsapp/com.whatsapp.Conversation
}

void MainWindow::OpenWebPage() {
    this->ExecuteShellCommands("am start -a android.intent.action.VIEW https://" + ui->lineEdit->text());
}

void MainWindow::OpenSmsForm() {
    SMSForm * sms = new SMSForm;
    sms->show();
}

void MainWindow::ExecCommand() {
    this->ExecuteShellCommands(ui->lineEdit_2->text());
}

QString MainWindow::ExecuteShellCommands(QString str) {
//    QMessageBox * msgbox = new QMessageBox;
//    msgbox->setText("/bin/bash connectDevice.sh " + str);
//    msgbox->show();

    QProcess qp;
    QString proc;
    const int waitTime=15000;

//    qp.start("/bin/bash connectDevice.sh", QStringList() << str);
    qp.start("/bin/bash connectDevice.sh \"" + str + "\"");
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);

    proc = qp.readAll();

    if(!proc.toStdString().empty())
    {
//        QMessageBox * msgbox = new QMessageBox;
//        msgbox->setText(proc);
//        msgbox->show();
        ui->label_3->setText(proc);
        return (QString)proc;
    }
    return "";
}

void MainWindow::RefreshInfoBatary() {
    QString proc1("su -c 'cat /sys/class/power_supply/battery/capacity'"), proc;
    proc = this->ExecuteShellCommands(proc1);
    ui->progressBar_2->setValue(proc.toInt());
}

MainWindow::~MainWindow()
{
    delete ui;
}
