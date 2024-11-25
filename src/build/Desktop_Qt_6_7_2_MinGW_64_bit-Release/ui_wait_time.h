/********************************************************************************
** Form generated from reading UI file 'wait_time.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAIT_TIME_H
#define UI_WAIT_TIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_wait_time
{
public:
    QLabel *label;

    void setupUi(QDialog *wait_time)
    {
        if (wait_time->objectName().isEmpty())
            wait_time->setObjectName("wait_time");
        wait_time->setEnabled(true);
        wait_time->resize(345, 58);
        wait_time->setMinimumSize(QSize(345, 58));
        wait_time->setMaximumSize(QSize(345, 58));
        wait_time->setTabletTracking(false);
        wait_time->setAcceptDrops(false);
        wait_time->setAutoFillBackground(false);
        wait_time->setStyleSheet(QString::fromUtf8(""));
        wait_time->setSizeGripEnabled(false);
        label = new QLabel(wait_time);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 291, 17));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        retranslateUi(wait_time);

        QMetaObject::connectSlotsByName(wait_time);
    } // setupUi

    void retranslateUi(QDialog *wait_time)
    {
        wait_time->setWindowTitle(QCoreApplication::translate("wait_time", "Wait", nullptr));
        label->setText(QCoreApplication::translate("wait_time", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201 \320\267\320\260\320\271\320\274\320\265\321\202 \320\275\320\265\321\201\320\272\320\276\320\273\321\214\320\272\320\276 \320\274\320\270\320\275\321\203\321\202...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wait_time: public Ui_wait_time {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAIT_TIME_H
