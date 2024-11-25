/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *button_start;
    QPushButton *button_dir_selects;
    QPushButton *button_dir_db;
    QListWidget *listWidget_log;
    QLabel *label_2;
    QLabel *label_dir_db;
    QLabel *label_dir_selects;
    QLabel *label_1;
    QPushButton *button_clear_db;
    QLabel *label_3;
    QRadioButton *radioButton_EM;
    QRadioButton *radioButton_NT;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(733, 441);
        MainWindow->setMinimumSize(QSize(733, 441));
        MainWindow->setMaximumSize(QSize(733, 441));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        button_start = new QPushButton(centralwidget);
        button_start->setObjectName("button_start");
        button_start->setGeometry(QRect(320, 260, 80, 25));
        button_dir_selects = new QPushButton(centralwidget);
        button_dir_selects->setObjectName("button_dir_selects");
        button_dir_selects->setGeometry(QRect(10, 80, 80, 25));
        button_dir_db = new QPushButton(centralwidget);
        button_dir_db->setObjectName("button_dir_db");
        button_dir_db->setGeometry(QRect(10, 20, 80, 25));
        listWidget_log = new QListWidget(centralwidget);
        listWidget_log->setObjectName("listWidget_log");
        listWidget_log->setGeometry(QRect(0, 290, 731, 101));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 60, 551, 21));
        label_dir_db = new QLabel(centralwidget);
        label_dir_db->setObjectName("label_dir_db");
        label_dir_db->setGeometry(QRect(100, 20, 431, 21));
        label_dir_selects = new QLabel(centralwidget);
        label_dir_selects->setObjectName("label_dir_selects");
        label_dir_selects->setGeometry(QRect(100, 80, 431, 21));
        label_1 = new QLabel(centralwidget);
        label_1->setObjectName("label_1");
        label_1->setGeometry(QRect(10, 0, 491, 21));
        button_clear_db = new QPushButton(centralwidget);
        button_clear_db->setObjectName("button_clear_db");
        button_clear_db->setGeometry(QRect(10, 140, 80, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 120, 361, 21));
        radioButton_EM = new QRadioButton(centralwidget);
        radioButton_EM->setObjectName("radioButton_EM");
        radioButton_EM->setGeometry(QRect(290, 220, 41, 22));
        radioButton_NT = new QRadioButton(centralwidget);
        radioButton_NT->setObjectName("radioButton_NT");
        radioButton_NT->setGeometry(QRect(400, 220, 41, 22));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(700, 260, 20, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 733, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
#if QT_CONFIG(shortcut)
        label_dir_db->setBuddy(button_dir_db);
        label_dir_selects->setBuddy(button_dir_selects);
        label_3->setBuddy(button_clear_db);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "txt to access for TPTS", nullptr));
        button_start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        button_dir_selects->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\267\320\276\321\200", nullptr));
        button_dir_db->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\267\320\276\321\200", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \320\277\320\260\320\277\320\272\321\203 \321\201 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\320\274\320\270 \320\264\320\260\320\275\320\275\321\213\320\274\320\270, \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \321\205\320\276\321\202\320\270\321\202\320\265 \320\277\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270 \320\262 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205 MS Access", nullptr));
        label_dir_db->setText(QString());
        label_dir_selects->setText(QString());
        label_1->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265  \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205 MS Access \320\262 \321\204\320\276\321\200\320\274\320\260\321\202\320\265 accdb, \320\262 \320\272\320\276\321\202\320\276\321\200\321\203\321\216 \320\261\321\203\320\264\321\203\321\202 \320\267\320\260\320\277\320\270\321\201\320\260\320\275\321\213 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        button_clear_db->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\261\320\260\320\267\321\203 \320\276\321\202 \321\202\320\260\320\261\320\273\320\270\321\206", nullptr));
        radioButton_EM->setText(QCoreApplication::translate("MainWindow", "EM", nullptr));
        radioButton_NT->setText(QCoreApplication::translate("MainWindow", "HT", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "i", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
