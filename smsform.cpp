#include "smsform.h"
#include "ui_smsform.h"
#include <mainwindow.h>
#include <QMessageBox>

SMSForm::SMSForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SMSForm)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(SendMes()));
}

void SMSForm::SendMes() {

    if(!ui->checkBox->checkState() && !ui->checkBox_2->checkState())
    {
        QMessageBox * msgbox = new QMessageBox;
        msgbox->setText("Не выбрана сим карта");
        msgbox->show();
    } else {
        QString query("adb shell am start -a android.intent.action.SENDTO -d sms:'" + ui->lineEdit->text() + "' --es sms_body '" + ui->lineEdit_2->text() + "'");
        this->exec(query);
        query = "adb shell input keyevent 22 && sleep 1";
        this->exec(query);
        query = "adb shell input keyevent 66 && sleep 1";
        this->exec(query);
        if(ui->checkBox_2->checkState())
        {
            query = "adb shell input keyevent 20 && sleep 1";
            this->exec(query);
        }
        query = "adb shell input keyevent 66";
        this->exec(query);
    }
}

void SMSForm::exec(QString query) {
    QProcess qp;
    QString proc;
    const int waitTime=15000;

    qp.start(query);
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);
}

SMSForm::~SMSForm()
{
    delete ui;
}
