#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QProcess qp;
    QString proc;
    const int waitTime=15000;
    QString cmd("connectDevice.sh");

    qp.start("/bin/bash", QStringList() << cmd);
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
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(WakeUphone()));
        connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(OpenWhatsApp()));
        connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(OpenWebPage()));


    } else {
        ui->label_2->setText("Телефон не подключен");
        ui->progressBar_2->setValue(0);        
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}

void MainWindow::WakeUphone() {
    this->ExecuteShellCommands("adb shell input keyevent 26");
    //adb shell input keyevent 26
}

void MainWindow::OpenWhatsApp() {

    this->ExecuteShellCommands("adb shell am start -n com.whatsapp/com.whatsapp.Conversation");
    //adb shell am start -n com.whatsapp/com.whatsapp.Conversation
}

void MainWindow::OpenWebPage() {

//    ui->lineEdit->setEnabled(true);
//    ui->pushButton_3->setText("Отправить");
    this->ExecuteShellCommands("adb shell am start -a android.intent.action.VIEW http://www.google.com");
//    QString str("adb shell am start -a android.intent.action.VIEW " + ui->lineEdit->text());

    //adb shell am start -a android.intent.action.VIEW http://www.google.com
}

void MainWindow::ExecuteShellCommands(QString str) {
    QMessageBox * msgbox = new QMessageBox;
    msgbox->setText(str);
    msgbox->show();
    QProcess qp;
    QString proc;
    const int waitTime=15000;

    qp.start(str);
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);

    proc = qp.readAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}
