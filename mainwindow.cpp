#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{        
    QProcess qp;
    QString proc;
    const int waitTime=15000;
    QString cmd("su -c cat /sys/class/power_supply/battery/capacity"), NameDevice;
    QTimer * t = new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(RefreshInfoBatary()));
    QFile f("Connection_device");
//    NameDevice=f.readLine();

    QString str="";
//    f.open(QIODevice::ReadWrite);
//    while(!f.atEnd())
//    {
//        str=str+f.readLine();
//    }
//    f.close();
    if((f.exists() && f.open(QIODevice::ReadOnly))){
//        QMessageBox * msgbox = new QMessageBox;
//        msgbox->setText(f.readLine());
//        msgbox->show();

//        this->setWindowIcon("/home/leo/picture/icon_InfoPhone.png");
//        this->setWindowTitle("123");
        NameDevice=f.readLine();
        f.close();
    }

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
        ui->label_2->setText("Информация об устройстве " + NameDevice);
        ui->progressBar_2->setValue(proc.toInt());
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        t->start(10000);
        connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(WakeUphone()));
        connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(OpenWhatsApp()));
//        QString str("adb shell am start -a android.intent.action.VIEW http://www.google.com");
//        QString str(ui->lineEdit->text());
        connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(OpenWebPage()));
        connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ExecCommand()));
        connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(OpenSmsForm()));
        connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(EnterNumber()));
        connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(CallNumber()));

    } else {
        ui->label_2->setText("Телефон не подключен");
        ui->progressBar_2->setValue(0);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
    }
}

void MainWindow::WakeUphone() {
    this->ExecuteShellCommands("input keyevent 26",0);
//    this->ExecuteShellCommands("input keyevent 82 && sleep 1",0);
//    this->ExecuteShellCommands("input keyevent 67",0);

    //adb shell input keyevent 26
}

void MainWindow::OpenWhatsApp() {
    this->ExecuteShellCommands("am start -n com.whatsapp/com.whatsapp.Conversation",0);
    //adb shell am start -n com.whatsapp/com.whatsapp.Conversation
}

void MainWindow::OpenWebPage() {
    this->ExecuteShellCommands("am start -a android.intent.action.VIEW " + ui->lineEdit->text(),0);
}

void MainWindow::OpenSmsForm() {
    SMSForm * sms = new SMSForm;
    sms->show();
}

void MainWindow::ExecCommand() {
    this->ExecuteShellCommands(ui->lineEdit_2->text(),1);
}

QString MainWindow::ExecuteShellCommands(QString str, int param) {
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
//    param = 1 - нужен комментарий
//    param = 0 - не нужен комментарий
    if(param==1 && !proc.toStdString().empty())
    {
//        QMessageBox * msgbox = new QMessageBox;
//        msgbox->setText(proc);
//        msgbox->show();
        ui->label_3->setText(proc);        
    }
    return (QString)proc;
}

void MainWindow::RefreshInfoBatary() {
    QString proc1("su -c 'cat /sys/class/power_supply/battery/capacity'"), proc;
    proc = this->ExecuteShellCommands(proc1,0);
    ui->progressBar_2->setValue(proc.toInt());

    QFile f("Connection_device");

    if((f.exists()&&f.open(QIODevice::ReadOnly))){
        ui->label_2->setText("Информация об устройстве " + f.readLine());
        f.close();
    }
}

void MainWindow::EnterNumber() {
    //am start -a android.intent.action.CALL tel:
    //input keyevent 66
    //input keyevent 66
    QString proc1("input keyevent 3");
    this->ExecuteShellCommands(proc1,0);
    proc1 = "am start -a android.intent.action.DIAL tel:" + ui->lineEdit_3->text();
    this->ExecuteShellCommands(proc1,0);
}

void MainWindow::CallNumber() {
    //am start -a android.intent.action.CALL tel:
    //input keyevent 66
    //input keyevent 66
    QString proc1("input keyevent 3");
    this->ExecuteShellCommands(proc1,0);
    proc1="am start -a android.intent.action.CALL tel:" + ui->lineEdit_3->text();
    this->ExecuteShellCommands(proc1,0);
    proc1="sleep 1 && input keyevent 66";
    this->ExecuteShellCommands(proc1,0);
    proc1="sleep 1 && input keyevent 66";
    this->ExecuteShellCommands(proc1,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
