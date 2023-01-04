/********************************************************************************
** Form generated from reading UI file 'cleandatadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLEANDATADIALOG_H
#define UI_CLEANDATADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CleanDataDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *le_in_dir;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *le_out_dir;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLineEdit *le_landUsePath;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QSpinBox *spinBox;
    QLabel *label_5;
    QComboBox *comboBox;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QPushButton *pushButton_4;
    QProgressBar *progressBar;

    void setupUi(QDialog *CleanDataDialog)
    {
        if (CleanDataDialog->objectName().isEmpty())
            CleanDataDialog->setObjectName(QString::fromUtf8("CleanDataDialog"));
        CleanDataDialog->resize(642, 518);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/\346\270\205\346\264\227\347\273\237\350\256\241.png"), QSize(), QIcon::Normal, QIcon::Off);
        CleanDataDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(CleanDataDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(CleanDataDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 111));
        widget->setMaximumSize(QSize(16777215, 111));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le_in_dir = new QLineEdit(widget);
        le_in_dir->setObjectName(QString::fromUtf8("le_in_dir"));

        gridLayout->addWidget(le_in_dir, 0, 1, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        le_out_dir = new QLineEdit(widget);
        le_out_dir->setObjectName(QString::fromUtf8("le_out_dir"));

        gridLayout->addWidget(le_out_dir, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        le_landUsePath = new QLineEdit(widget);
        le_landUsePath->setObjectName(QString::fromUtf8("le_landUsePath"));

        gridLayout->addWidget(le_landUsePath, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 2, 1, 1);


        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(CleanDataDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMinimumSize(QSize(0, 75));
        widget_3->setMaximumSize(QSize(16777215, 75));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        spinBox = new QSpinBox(widget_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(3);
        spinBox->setSingleStep(2);

        gridLayout_3->addWidget(spinBox, 0, 1, 1, 1);

        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 1, 0, 1, 1);

        comboBox = new QComboBox(widget_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_3->addWidget(comboBox, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_3);

        widget_2 = new QWidget(CleanDataDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(widget_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_2->addWidget(textEdit, 2, 0, 1, 1);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 0, 0, 1, 1);

        progressBar = new QProgressBar(widget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        gridLayout_2->addWidget(progressBar, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_2);


        retranslateUi(CleanDataDialog);

        QMetaObject::connectSlotsByName(CleanDataDialog);
    } // setupUi

    void retranslateUi(QDialog *CleanDataDialog)
    {
        CleanDataDialog->setWindowTitle(QCoreApplication::translate("CleanDataDialog", "\346\270\205\346\264\227\346\225\260\346\215\256", nullptr));
        label->setText(QCoreApplication::translate("CleanDataDialog", "\351\251\261\345\212\250\345\212\233\347\233\256\345\275\225", nullptr));
        pushButton->setText(QCoreApplication::translate("CleanDataDialog", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("CleanDataDialog", "\350\276\223\345\207\272\347\233\256\345\275\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CleanDataDialog", "\351\200\211\346\213\251", nullptr));
        label_3->setText(QCoreApplication::translate("CleanDataDialog", "\345\234\237\345\234\260\345\210\251\347\224\250\346\225\260\346\215\256", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CleanDataDialog", "\351\200\211\346\213\251", nullptr));
        label_4->setText(QCoreApplication::translate("CleanDataDialog", "\351\242\206\345\237\237\345\215\212\345\276\204", nullptr));
        label_5->setText(QCoreApplication::translate("CleanDataDialog", "\346\250\241\345\274\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CleanDataDialog", "\345\235\207\345\200\274", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("CleanDataDialog", "\344\274\227\346\225\260", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("CleanDataDialog", "\346\234\200\345\260\217\345\200\274", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("CleanDataDialog", "\346\234\200\345\260\217\345\200\274", nullptr));

        pushButton_4->setText(QCoreApplication::translate("CleanDataDialog", "\346\270\205\346\264\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CleanDataDialog: public Ui_CleanDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEANDATADIALOG_H
