/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_help
{
public:
    QLabel *label;

    void setupUi(QWidget *help)
    {
        if (help->objectName().isEmpty())
            help->setObjectName("help");
        help->setWindowModality(Qt::ApplicationModal);
        help->resize(403, 140);
        help->setMinimumSize(QSize(403, 140));
        help->setMaximumSize(QSize(403, 140));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setStrikeOut(false);
        help->setFont(font);
        label = new QLabel(help);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 391, 101));

        retranslateUi(help);

        QMetaObject::connectSlotsByName(help);
    } // setupUi

    void retranslateUi(QWidget *help)
    {
        help->setWindowTitle(QCoreApplication::translate("help", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("help", "\320\247\321\202\320\276 \320\264\320\265\320\273\320\260\320\265\321\202 \320\264\320\260\320\275\320\275\320\260\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260:\n"
"\n"
"1. \320\237\320\265\321\200\320\265\320\275\320\276\321\201\320\270\321\202 \320\264\320\260\320\275\320\275\321\213\320\265 \320\270\320\267 txt \320\262 MS Access.\n"
"2. \320\237\321\200\320\276\320\262\320\265\321\200\321\217\320\265\321\202 \320\264\321\203\320\261\320\273\320\270\320\272\320\260\321\202\321\213 \321\201\320\270\320\263\320\275\320\260\320\273\320\276\320\262 \320\262\320\275\321\203\321\202\321\200\320\270 \320\276\320\264\320\275\320\276\320\263\320\276 \320\272\320\260\320\261\320\270\320\275\320\265\321\202\320\260.\n"
"3. \320\237\321\200\320\276\320\262\320\265\321\200\321\217\320\265\321\202 \320\264\321\203\320\261\320\273\320\270\320\272\320\260\321\202\321\213 \321\201\320\270\320\263\320\275\320\260\320\273\320\276\320\262 \320\274\320\265\320\266\320\264\321\203 \320\262\321"
                        "\201\320\265\320\274\320\270 \320\272\320\260\320\261\320\270\320\275\320\265\321\202\320\260\320\274\320\270.\n"
"4. \320\222\321\201\320\265 \320\275\320\260\320\271\320\264\320\265\320\275\320\275\321\213\320\265 \320\275\320\265\321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\321\202\320\262\320\270\321\217 \320\267\320\260\320\277\320\270\321\201\321\213\320\262\320\260\321\216\321\202\321\201\321\217 \320\262 \320\273\320\276\320\263 \321\204\320\260\320\271\320\273.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class help: public Ui_help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
