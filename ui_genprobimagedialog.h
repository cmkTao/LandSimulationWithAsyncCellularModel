/********************************************************************************
** Form generated from reading UI file 'genprobimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENPROBIMAGEDIALOG_H
#define UI_GENPROBIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenProbImageDialog
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QLineEdit *le_landPath;
    QPushButton *pushButton_3;
    QLineEdit *le_dir;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QCheckBox *cb_One;
    QCheckBox *cb_Random;
    QCheckBox *cb_NormalRandom;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rb_one;
    QRadioButton *rb_two;
    QPushButton *pushButton;
    QTextEdit *textEdit;

    void setupUi(QDialog *GenProbImageDialog)
    {
        if (GenProbImageDialog->objectName().isEmpty())
            GenProbImageDialog->setObjectName(QString::fromUtf8("GenProbImageDialog"));
        GenProbImageDialog->resize(810, 280);
        horizontalLayout_4 = new QHBoxLayout(GenProbImageDialog);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        widget_4 = new QWidget(GenProbImageDialog);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setMinimumSize(QSize(0, 250));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 0, 1, 1);

        le_landPath = new QLineEdit(widget_3);
        le_landPath->setObjectName(QString::fromUtf8("le_landPath"));

        gridLayout->addWidget(le_landPath, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_3, 0, 0, 1, 2);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 0, 1, 1);

        le_dir = new QLineEdit(widget_4);
        le_dir->setObjectName(QString::fromUtf8("le_dir"));

        gridLayout_2->addWidget(le_dir, 1, 1, 1, 1);

        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(100, 0));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        cb_One = new QCheckBox(widget);
        cb_One->setObjectName(QString::fromUtf8("cb_One"));
        cb_One->setChecked(true);

        horizontalLayout->addWidget(cb_One);

        cb_Random = new QCheckBox(widget);
        cb_Random->setObjectName(QString::fromUtf8("cb_Random"));

        horizontalLayout->addWidget(cb_Random);

        cb_NormalRandom = new QCheckBox(widget);
        cb_NormalRandom->setObjectName(QString::fromUtf8("cb_NormalRandom"));

        horizontalLayout->addWidget(cb_NormalRandom);


        gridLayout_2->addWidget(widget, 2, 0, 1, 2);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rb_one = new QRadioButton(widget_2);
        rb_one->setObjectName(QString::fromUtf8("rb_one"));
        rb_one->setChecked(true);

        horizontalLayout_2->addWidget(rb_one);

        rb_two = new QRadioButton(widget_2);
        rb_two->setObjectName(QString::fromUtf8("rb_two"));

        horizontalLayout_2->addWidget(rb_two);


        gridLayout_2->addWidget(widget_2, 3, 0, 1, 2);

        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 4, 0, 1, 1);


        horizontalLayout_4->addWidget(widget_4);

        textEdit = new QTextEdit(GenProbImageDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout_4->addWidget(textEdit);


        retranslateUi(GenProbImageDialog);

        QMetaObject::connectSlotsByName(GenProbImageDialog);
    } // setupUi

    void retranslateUi(QDialog *GenProbImageDialog)
    {
        GenProbImageDialog->setWindowTitle(QCoreApplication::translate("GenProbImageDialog", "\350\207\252\345\256\232\344\271\211\346\246\202\347\216\207\345\233\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("GenProbImageDialog", "\345\234\237\345\234\260\345\210\251\347\224\250\345\233\276\345\203\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("GenProbImageDialog", "\345\233\276\345\203\217\344\277\235\345\255\230\347\233\256\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("GenProbImageDialog", "\347\224\237\346\210\220\346\226\271\345\274\217", nullptr));
        cb_One->setText(QCoreApplication::translate("GenProbImageDialog", "\345\205\2501", nullptr));
        cb_Random->setText(QCoreApplication::translate("GenProbImageDialog", "\351\232\217\346\234\272(\345\235\207\345\214\200)", nullptr));
        cb_NormalRandom->setText(QCoreApplication::translate("GenProbImageDialog", "\351\232\217\346\234\272(\346\255\243\346\200\201)", nullptr));
        rb_one->setText(QCoreApplication::translate("GenProbImageDialog", "\344\270\200\346\234\237\346\225\260\346\215\256", nullptr));
        rb_two->setText(QCoreApplication::translate("GenProbImageDialog", "\344\270\244\346\234\237\346\225\260\346\215\256", nullptr));
        pushButton->setText(QCoreApplication::translate("GenProbImageDialog", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenProbImageDialog: public Ui_GenProbImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENPROBIMAGEDIALOG_H
