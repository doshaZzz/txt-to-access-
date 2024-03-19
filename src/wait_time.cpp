#include "wait_time.h"
#include "ui_wait_time.h"

wait_time::wait_time(QWidget *parent) :
    QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint), // Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |  Qt::FramelessWindowHint
    ui(new Ui::wait_time)
{
    ui->setupUi(this);
}

wait_time::~wait_time()
{
    delete ui;
}
