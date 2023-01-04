/********************************************************************************
** Form generated from reading UI file 'tmp.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TMP_H
#define UI_TMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_generateProbImageDailog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;

    void setupUi(QDialog *generateProbImageDailog)
    {
        if (generateProbImageDailog->objectName().isEmpty())
            generateProbImageDailog->setObjectName(QString::fromUtf8("generateProbImageDailog"));
        generateProbImageDailog->resize(260, 155);
        verticalLayout = new QVBoxLayout(generateProbImageDailog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(generateProbImageDailog);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(34, 0));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(generateProbImageDailog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(widget_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(200);

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addWidget(widget_2);

        pushButton = new QPushButton(generateProbImageDailog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(generateProbImageDailog);

        QMetaObject::connectSlotsByName(generateProbImageDailog);
    } // setupUi

    void retranslateUi(QDialog *generateProbImageDailog)
    {
        generateProbImageDailog->setWindowTitle(QCoreApplication::translate("generateProbImageDailog", "\350\207\252\345\256\232\344\271\211\347\224\237\346\210\220\346\246\202\347\216\207\345\233\276", nullptr));
        label->setText(QCoreApplication::translate("generateProbImageDailog", "\347\224\237\346\210\220\346\226\271\345\274\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("generateProbImageDailog", "\345\205\2501", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("generateProbImageDailog", "\351\232\217\346\234\272\357\274\210\345\205\250\345\261\202\345\220\214\357\274\211", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("generateProbImageDailog", "\345\205\250\345\261\202\344\270\215\345\220\214", nullptr));

        label_2->setText(QCoreApplication::translate("generateProbImageDailog", "\345\261\202\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("generateProbImageDailog", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class generateProbImageDailog: public Ui_generateProbImageDailog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TMP_H
