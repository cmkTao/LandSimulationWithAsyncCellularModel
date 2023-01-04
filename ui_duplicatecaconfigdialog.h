/********************************************************************************
** Form generated from reading UI file 'duplicatecaconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUPLICATECACONFIGDIALOG_H
#define UI_DUPLICATECACONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DuplicateCaConfigDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_configDir;
    QPushButton *b_choseConfig;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *le_saveDirPath;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *ds_min;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *ds_step;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *ds_max;

    void setupUi(QDialog *DuplicateCaConfigDialog)
    {
        if (DuplicateCaConfigDialog->objectName().isEmpty())
            DuplicateCaConfigDialog->setObjectName(QString::fromUtf8("DuplicateCaConfigDialog"));
        DuplicateCaConfigDialog->resize(414, 289);
        verticalLayout = new QVBoxLayout(DuplicateCaConfigDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_4 = new QWidget(DuplicateCaConfigDialog);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        le_configDir = new QLineEdit(widget_4);
        le_configDir->setObjectName(QString::fromUtf8("le_configDir"));

        horizontalLayout_4->addWidget(le_configDir);

        b_choseConfig = new QPushButton(widget_4);
        b_choseConfig->setObjectName(QString::fromUtf8("b_choseConfig"));

        horizontalLayout_4->addWidget(b_choseConfig);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(DuplicateCaConfigDialog);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        le_saveDirPath = new QLineEdit(widget_5);
        le_saveDirPath->setObjectName(QString::fromUtf8("le_saveDirPath"));

        horizontalLayout_5->addWidget(le_saveDirPath);

        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(92, 0));

        horizontalLayout_5->addWidget(pushButton_2);


        verticalLayout->addWidget(widget_5);

        pushButton = new QPushButton(DuplicateCaConfigDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        widget = new QWidget(DuplicateCaConfigDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ds_min = new QDoubleSpinBox(widget);
        ds_min->setObjectName(QString::fromUtf8("ds_min"));
        ds_min->setMaximum(1.000000000000000);
        ds_min->setSingleStep(0.010000000000000);
        ds_min->setValue(0.300000000000000);

        horizontalLayout->addWidget(ds_min);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(DuplicateCaConfigDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        ds_step = new QDoubleSpinBox(widget_2);
        ds_step->setObjectName(QString::fromUtf8("ds_step"));
        ds_step->setMinimum(0.050000000000000);
        ds_step->setMaximum(1.000000000000000);
        ds_step->setSingleStep(0.010000000000000);
        ds_step->setValue(0.200000000000000);

        horizontalLayout_2->addWidget(ds_step);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(DuplicateCaConfigDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        ds_max = new QDoubleSpinBox(widget_3);
        ds_max->setObjectName(QString::fromUtf8("ds_max"));
        ds_max->setMaximum(1.000000000000000);
        ds_max->setSingleStep(0.010000000000000);
        ds_max->setValue(0.900000000000000);

        horizontalLayout_3->addWidget(ds_max);


        verticalLayout->addWidget(widget_3);


        retranslateUi(DuplicateCaConfigDialog);

        QMetaObject::connectSlotsByName(DuplicateCaConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *DuplicateCaConfigDialog)
    {
        DuplicateCaConfigDialog->setWindowTitle(QCoreApplication::translate("DuplicateCaConfigDialog", "Dialog", nullptr));
        b_choseConfig->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\351\200\211\346\213\251\351\205\215\347\275\256\347\233\256\345\275\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\344\277\235\345\255\230\344\275\215\347\275\256", nullptr));
        pushButton->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\346\211\271\351\207\217\347\224\237\346\210\220\351\205\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_2->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\346\255\245\351\225\277", nullptr));
        label_3->setText(QCoreApplication::translate("DuplicateCaConfigDialog", "\346\234\200\345\244\247\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DuplicateCaConfigDialog: public Ui_DuplicateCaConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUPLICATECACONFIGDIALOG_H
