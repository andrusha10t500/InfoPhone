#include "mainthread.h"

MainThread::run()
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
}

