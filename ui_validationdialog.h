/********************************************************************************
** Form generated from reading UI file 'validationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALIDATIONDIALOG_H
#define UI_VALIDATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customWidget/Loading/Loading.h>

QT_BEGIN_NAMESPACE

class Ui_ValidationDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QSplitter *splitter;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_configPath;
    QPushButton *btn_config;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *le_truePath;
    QPushButton *btn_truePath;
    QPushButton *btn_startPath;
    QLabel *label_4;
    QPushButton *btn_simPath;
    QLabel *label_5;
    QLineEdit *le_startPath;
    QLabel *label_6;
    QLineEdit *le_simPath;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btn_saveConfig;
    QPushButton *btn_saveOther;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_cal;
    QProgressBar *pgb_process;
    Loading *w_loading;
    QTextEdit *te_res;

    void setupUi(QDialog *ValidationDialog)
    {
        if (ValidationDialog->objectName().isEmpty())
            ValidationDialog->setObjectName(QString::fromUtf8("ValidationDialog"));
        ValidationDialog->resize(892, 350);
        ValidationDialog->setMinimumSize(QSize(848, 350));
        horizontalLayout_5 = new QHBoxLayout(ValidationDialog);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        splitter = new QSplitter(ValidationDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(460, 311));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(0, 63));
        groupBox_2->setMaximumSize(QSize(16777215, 63));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 0, 2, 0);
        le_configPath = new QLineEdit(groupBox_2);
        le_configPath->setObjectName(QString::fromUtf8("le_configPath"));

        horizontalLayout_3->addWidget(le_configPath);

        btn_config = new QPushButton(groupBox_2);
        btn_config->setObjectName(QString::fromUtf8("btn_config"));

        horizontalLayout_3->addWidget(btn_config);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 0, 2, 0);
        le_truePath = new QLineEdit(groupBox);
        le_truePath->setObjectName(QString::fromUtf8("le_truePath"));

        gridLayout_2->addWidget(le_truePath, 1, 1, 1, 1);

        btn_truePath = new QPushButton(groupBox);
        btn_truePath->setObjectName(QString::fromUtf8("btn_truePath"));

        gridLayout_2->addWidget(btn_truePath, 1, 2, 1, 1);

        btn_startPath = new QPushButton(groupBox);
        btn_startPath->setObjectName(QString::fromUtf8("btn_startPath"));

        gridLayout_2->addWidget(btn_startPath, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        btn_simPath = new QPushButton(groupBox);
        btn_simPath->setObjectName(QString::fromUtf8("btn_simPath"));

        gridLayout_2->addWidget(btn_simPath, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        le_startPath = new QLineEdit(groupBox);
        le_startPath->setObjectName(QString::fromUtf8("le_startPath"));

        gridLayout_2->addWidget(le_startPath, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        le_simPath = new QLineEdit(groupBox);
        le_simPath->setObjectName(QString::fromUtf8("le_simPath"));

        gridLayout_2->addWidget(le_simPath, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        widget = new QWidget(widget_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 48));
        widget->setMaximumSize(QSize(16777215, 48));
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_saveConfig = new QPushButton(widget);
        btn_saveConfig->setObjectName(QString::fromUtf8("btn_saveConfig"));
        btn_saveConfig->setMinimumSize(QSize(0, 30));
        btn_saveConfig->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(btn_saveConfig);

        btn_saveOther = new QPushButton(widget);
        btn_saveOther->setObjectName(QString::fromUtf8("btn_saveOther"));
        btn_saveOther->setMinimumSize(QSize(0, 30));
        btn_saveOther->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_4->addWidget(btn_saveOther);


        verticalLayout->addWidget(widget);

        splitter->addWidget(widget_2);
        widget_3 = new QWidget(splitter);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_5);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_cal = new QPushButton(widget_4);
        btn_cal->setObjectName(QString::fromUtf8("btn_cal"));
        btn_cal->setEnabled(false);
        btn_cal->setMinimumSize(QSize(0, 30));
        btn_cal->setMaximumSize(QSize(16777215, 30));

        verticalLayout_2->addWidget(btn_cal);

        pgb_process = new QProgressBar(widget_4);
        pgb_process->setObjectName(QString::fromUtf8("pgb_process"));
        pgb_process->setMinimumSize(QSize(0, 30));
        pgb_process->setMaximumSize(QSize(16777215, 30));
        pgb_process->setValue(0);

        verticalLayout_2->addWidget(pgb_process);


        horizontalLayout_6->addWidget(widget_4);

        w_loading = new Loading(widget_5);
        w_loading->setObjectName(QString::fromUtf8("w_loading"));
        sizePolicy.setHeightForWidth(w_loading->sizePolicy().hasHeightForWidth());
        w_loading->setSizePolicy(sizePolicy);
        w_loading->setMinimumSize(QSize(60, 60));
        w_loading->setMaximumSize(QSize(60, 60));

        horizontalLayout_6->addWidget(w_loading);


        verticalLayout_3->addWidget(widget_5);

        te_res = new QTextEdit(widget_3);
        te_res->setObjectName(QString::fromUtf8("te_res"));

        verticalLayout_3->addWidget(te_res);

        splitter->addWidget(widget_3);

        horizontalLayout_5->addWidget(splitter);


        retranslateUi(ValidationDialog);

        QMetaObject::connectSlotsByName(ValidationDialog);
    } // setupUi

    void retranslateUi(QDialog *ValidationDialog)
    {
        ValidationDialog->setWindowTitle(QCoreApplication::translate("ValidationDialog", "\350\256\241\347\256\227Kappa\345\222\214Fom", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ValidationDialog", "Load Config", nullptr));
        btn_config->setText(QCoreApplication::translate("ValidationDialog", "\351\200\211\346\213\251", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ValidationDialog", "File Input", nullptr));
        btn_truePath->setText(QCoreApplication::translate("ValidationDialog", "\351\200\211\346\213\251", nullptr));
        btn_startPath->setText(QCoreApplication::translate("ValidationDialog", "\351\200\211\346\213\251", nullptr));
        label_4->setText(QCoreApplication::translate("ValidationDialog", "sim_file", nullptr));
        btn_simPath->setText(QCoreApplication::translate("ValidationDialog", "\351\200\211\346\213\251", nullptr));
        label_5->setText(QCoreApplication::translate("ValidationDialog", "true_path", nullptr));
        label_6->setText(QCoreApplication::translate("ValidationDialog", "start_path", nullptr));
        btn_saveConfig->setText(QCoreApplication::translate("ValidationDialog", "\344\277\235\345\255\230", nullptr));
        btn_saveOther->setText(QCoreApplication::translate("ValidationDialog", "\345\217\246\345\255\230\344\270\272", nullptr));
        btn_cal->setText(QCoreApplication::translate("ValidationDialog", "\350\256\241\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ValidationDialog: public Ui_ValidationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALIDATIONDIALOG_H
