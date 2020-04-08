#include "smsform.h"
#include "ui_smsform.h"
#include <mainwindow.h>
#include <QMessageBox>
#include <QDebug>

SMSForm::SMSForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SMSForm)
{
    ui->setupUi(this);

    QSqlDatabase db;
//    QMessageBox * msgbox = new QMessageBox;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("SMS/mmssms.db");
    if(!db.open()) {
        QMessageBox * mg = new QMessageBox;
        mg->setText("Не подключилась почему то...");
        mg->show();
    }

    QSqlQueryModel * query_m = new QSqlQueryModel;

    query_m->setQuery("attach database 'SMS/contacts2.db' as contacts;");

    query_m->setQuery("select b.display_name, address, datetime(substr(date,0,length(date)-2), 'unixepoch', 'localtime') as date_, body, sub_id "
                     "from sms a "
                     "left join (select a.display_name, b.normalized_number from contacts.raw_contacts a "
                     "left join contacts.phone_lookup b on a._id = b.raw_contact_id) b on a.address=b.normalized_number "
                     "order by 3 desc;");

    ui->tableView_2->setModel(query_m);
    db.close();

    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(SendMes()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(RefreshDB()));
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
        query = "adb shell input keyevent 66 && sleep 1";
        this->exec(query);
        this->close();
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

void SMSForm::RefreshDB() {
    QString query("./CopyDataBases.sh");
    this->exec(query);
}

SMSForm::~SMSForm()
{
    delete ui;
}
