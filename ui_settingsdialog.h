/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout;
    QCheckBox *cb_probCheck;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QRadioButton *rb_offical;
    QRadioButton *rb_selfD;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QRadioButton *rb_v1;
    QRadioButton *rb_v2;
    QCheckBox *cb_changeAlphaSetMode;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(411, 200);
        gridLayout = new QGridLayout(SettingsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cb_probCheck = new QCheckBox(SettingsDialog);
        cb_probCheck->setObjectName(QString::fromUtf8("cb_probCheck"));

        gridLayout->addWidget(cb_probCheck, 2, 0, 1, 1);

        pushButton = new QPushButton(SettingsDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(SettingsDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        rb_offical = new QRadioButton(groupBox_2);
        rb_offical->setObjectName(QString::fromUtf8("rb_offical"));

        gridLayout_3->addWidget(rb_offical, 0, 0, 1, 1);

        rb_selfD = new QRadioButton(groupBox_2);
        rb_selfD->setObjectName(QString::fromUtf8("rb_selfD"));

        gridLayout_3->addWidget(rb_selfD, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        rb_v1 = new QRadioButton(groupBox);
        rb_v1->setObjectName(QString::fromUtf8("rb_v1"));

        gridLayout_2->addWidget(rb_v1, 0, 0, 1, 1);

        rb_v2 = new QRadioButton(groupBox);
        rb_v2->setObjectName(QString::fromUtf8("rb_v2"));

        gridLayout_2->addWidget(rb_v2, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        cb_changeAlphaSetMode = new QCheckBox(SettingsDialog);
        cb_changeAlphaSetMode->setObjectName(QString::fromUtf8("cb_changeAlphaSetMode"));

        gridLayout->addWidget(cb_changeAlphaSetMode, 3, 0, 1, 1);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        cb_probCheck->setText(QCoreApplication::translate("SettingsDialog", "\351\200\202\345\272\224\346\200\247\346\246\202\347\216\207\345\210\244\346\226\255\345\274\200\345\220\257", nullptr));
        pushButton->setText(QCoreApplication::translate("SettingsDialog", "\344\277\235\345\255\230", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SettingsDialog", "\345\256\230\346\226\271/\350\207\252\345\256\232\344\271\211\351\200\273\350\276\221", nullptr));
        rb_offical->setText(QCoreApplication::translate("SettingsDialog", "\345\256\230\346\226\271", nullptr));
        rb_selfD->setText(QCoreApplication::translate("SettingsDialog", "\350\207\252\345\256\232\344\271\211", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SettingsDialog", "\344\275\277\347\224\250\347\211\210\346\234\254", nullptr));
        rb_v1->setText(QCoreApplication::translate("SettingsDialog", "V1", nullptr));
        rb_v2->setText(QCoreApplication::translate("SettingsDialog", "V2", nullptr));
        cb_changeAlphaSetMode->setText(QCoreApplication::translate("SettingsDialog", "\345\217\252\346\233\264\346\226\260alpha\345\255\220\351\233\206\344\270\255\347\273\206\350\203\236\347\232\204\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
