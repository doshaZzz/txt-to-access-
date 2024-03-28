#ifndef WAIT_TIME_H
#define WAIT_TIME_H

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class wait_time;
}

class wait_time : public QDialog
{
    Q_OBJECT

public:
    explicit wait_time(QWidget *parent = nullptr);
    ~wait_time();

private:
    Ui::wait_time *ui;
public slots:
};

#endif // WAIT_TIME_H
