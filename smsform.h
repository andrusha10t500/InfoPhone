#ifndef SMSFORM_H
#define SMSFORM_H

#include <QWidget>

namespace Ui {
class SMSForm;
}

class SMSForm : public QWidget
{
    Q_OBJECT

public:
    explicit SMSForm(QWidget *parent = 0);
    void exec(QString query);
    ~SMSForm();

private slots:
    void SendMes();

private:
    Ui::SMSForm *ui;

};

#endif // SMSFORM_H
