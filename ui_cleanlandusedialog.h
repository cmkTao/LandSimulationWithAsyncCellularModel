/********************************************************************************
** Form generated from reading UI file 'cleanlandusedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLEANLANDUSEDIALOG_H
#define UI_CLEANLANDUSEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cleanLandUseDialog
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *le_start;
    QPushButton *pushButton_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *le_target;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_save;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QTextEdit *te_res;

    void setupUi(QDialog *cleanLandUseDialog)
    {
        if (cleanLandUseDialog->objectName().isEmpty())
            cleanLandUseDialog->setObjectName(QString::fromUtf8("cleanLandUseDialog"));
        cleanLandUseDialog->resize(648, 513);
        gridLayout = new QGridLayout(cleanLandUseDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(cleanLandUseDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        le_start = new QLineEdit(widget);
        le_start->setObjectName(QString::fromUtf8("le_start"));

        horizontalLayout->addWidget(le_start);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(cleanLandUseDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        le_target = new QLineEdit(widget_2);
        le_target->setObjectName(QString::fromUtf8("le_target"));

        horizontalLayout_2->addWidget(le_target);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        widget_3 = new QWidget(cleanLandUseDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        le_save = new QLineEdit(widget_3);
        le_save->setObjectName(QString::fromUtf8("le_save"));

        horizontalLayout_3->addWidget(le_save);

        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_3->addWidget(pushButton_5);


        gridLayout->addWidget(widget_3, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(cleanLandUseDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 3, 0, 1, 1);

        te_res = new QTextEdit(cleanLandUseDialog);
        te_res->setObjectName(QString::fromUtf8("te_res"));

        gridLayout->addWidget(te_res, 4, 0, 1, 1);


        retranslateUi(cleanLandUseDialog);

        QMetaObject::connectSlotsByName(cleanLandUseDialog);
    } // setupUi

    void retranslateUi(QDialog *cleanLandUseDialog)
    {
        cleanLandUseDialog->setWindowTitle(QCoreApplication::translate("cleanLandUseDialog", "Dialog", nullptr));
        pushButton_2->setText(QCoreApplication::translate("cleanLandUseDialog", "\350\265\267\345\247\213", nullptr));
        pushButton_3->setText(QCoreApplication::translate("cleanLandUseDialog", "\347\233\256\346\240\207", nullptr));
        pushButton_5->setText(QCoreApplication::translate("cleanLandUseDialog", "\344\277\235\345\255\230", nullptr));
        pushButton_4->setText(QCoreApplication::translate("cleanLandUseDialog", "\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cleanLandUseDialog: public Ui_cleanLandUseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEANLANDUSEDIALOG_H
