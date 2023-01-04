/********************************************************************************
** Form generated from reading UI file 'generateconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATECONFIGDIALOG_H
#define UI_GENERATECONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GenerateConfigDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *GenerateConfigDialog)
    {
        if (GenerateConfigDialog->objectName().isEmpty())
            GenerateConfigDialog->setObjectName(QString::fromUtf8("GenerateConfigDialog"));
        GenerateConfigDialog->resize(339, 82);
        gridLayout = new QGridLayout(GenerateConfigDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(GenerateConfigDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(GenerateConfigDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        retranslateUi(GenerateConfigDialog);

        QMetaObject::connectSlotsByName(GenerateConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateConfigDialog)
    {
        GenerateConfigDialog->setWindowTitle(QCoreApplication::translate("GenerateConfigDialog", "\347\224\237\346\210\220defaultConfig.ini\346\226\207\344\273\266", nullptr));
        pushButton->setText(QCoreApplication::translate("GenerateConfigDialog", "defaultConfig1.ini", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GenerateConfigDialog", "defaultConfig2.ini", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerateConfigDialog: public Ui_GenerateConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATECONFIGDIALOG_H
