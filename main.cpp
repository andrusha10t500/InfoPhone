#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    QHBoxLayout * layout = new QHBoxLayout;
    QPushButton * button = new QPushButton("Exit");
    QWidget * widget = new QWidget;
    QLabel *label = new QLabel();
    QLabel *zaryad = new QLabel();
    QProcess qp;
    QString proc;
    const int waitTime=15000;
    QString cmd("connectDevice.sh");

    qp.start("/bin/bash", QStringList() << cmd);
    label->setText("Заряд батареи: ");
    button->setText("Exit");

    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);

    proc = qp.readAll();
    zaryad->setText(proc);
    QObject::connect(button,SIGNAL(clicked()),&a,SLOT(quit()));


//    Инициализация формы:
    layout->addWidget(label);
    layout->addWidget(zaryad);
    layout->addWidget(button);

    widget->setLayout(layout);
    widget->show();

    return a.exec();
}
