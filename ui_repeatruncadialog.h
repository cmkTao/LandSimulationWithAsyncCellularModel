/********************************************************************************
** Form generated from reading UI file 'repeatruncadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPEATRUNCADIALOG_H
#define UI_REPEATRUNCADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RepeatRunCADialog
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QWidget *widget_3;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QDialog *RepeatRunCADialog)
    {
        if (RepeatRunCADialog->objectName().isEmpty())
            RepeatRunCADialog->setObjectName(QString::fromUtf8("RepeatRunCADialog"));
        RepeatRunCADialog->resize(508, 338);
        gridLayout = new QGridLayout(RepeatRunCADialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(RepeatRunCADialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(RepeatRunCADialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        textEdit = new QTextEdit(RepeatRunCADialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 4, 0, 1, 1);

        widget_3 = new QWidget(RepeatRunCADialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_2 = new QGridLayout(widget_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(widget_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout_2->addWidget(spinBox, 0, 1, 1, 1);


        gridLayout->addWidget(widget_3, 2, 0, 1, 1);


        retranslateUi(RepeatRunCADialog);

        QMetaObject::connectSlotsByName(RepeatRunCADialog);
    } // setupUi

    void retranslateUi(QDialog *RepeatRunCADialog)
    {
        RepeatRunCADialog->setWindowTitle(QCoreApplication::translate("RepeatRunCADialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("RepeatRunCADialog", "\351\200\211\346\213\251\351\205\215\347\275\256\346\226\207\344\273\266", nullptr));
        pushButton_2->setText(QCoreApplication::translate("RepeatRunCADialog", "\351\200\211\346\213\251\344\277\235\345\255\230\347\233\256\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("RepeatRunCADialog", "\346\250\241\346\213\237\346\254\241\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RepeatRunCADialog: public Ui_RepeatRunCADialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPEATRUNCADIALOG_H
