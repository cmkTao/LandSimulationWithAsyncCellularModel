/********************************************************************************
** Form generated from reading UI file 'anndialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNDIALOG_H
#define UI_ANNDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customWidget/Loading/Loading.h>

QT_BEGIN_NAMESPACE

class Ui_ANNDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QSplitter *splitter;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_config;
    QPushButton *btn_chConfig;
    QGroupBox *gb_LUD;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rb_one;
    QRadioButton *rb_two;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *le_input2;
    QLabel *label;
    QLineEdit *le_input1;
    QPushButton *pushButton_2;
    QGroupBox *gb_PPath;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *le_probPath;
    QPushButton *btn_chProbPath;
    QGroupBox *gb_DFD;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *le_drive_factor;
    QPushButton *btn_chDir;
    QGroupBox *gb_ANNS;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rb_US;
    QRadioButton *rb_RS;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QCheckBox *cb_norm;
    QLabel *label_6;
    QCheckBox *cb_wl;
    QLabel *label_3;
    QDoubleSpinBox *dsb_SR;
    QLabel *label_4;
    QSpinBox *sb_Epochs;
    QPushButton *btn_saveConfig;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_startSim;
    QPushButton *btn_stopSim;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_4;
    QProgressBar *pgb_epochs;
    QProgressBar *pgb_subepochs;
    Loading *w_loading;
    QTextEdit *te_res;

    void setupUi(QDialog *ANNDialog)
    {
        if (ANNDialog->objectName().isEmpty())
            ANNDialog->setObjectName(QString::fromUtf8("ANNDialog"));
        ANNDialog->resize(992, 739);
        ANNDialog->setMinimumSize(QSize(0, 680));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/03 \347\245\236\347\273\217\347\275\221\347\273\234.png"), QSize(), QIcon::Normal, QIcon::Off);
        ANNDialog->setWindowIcon(icon);
        horizontalLayout_5 = new QHBoxLayout(ANNDialog);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        splitter = new QSplitter(ANNDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget_5 = new QWidget(splitter);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(0, 692));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_4 = new QGroupBox(widget_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(0, 85));
        groupBox_4->setMaximumSize(QSize(16777215, 85));
        groupBox_4->setAlignment(Qt::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        le_config = new QLineEdit(groupBox_4);
        le_config->setObjectName(QString::fromUtf8("le_config"));

        horizontalLayout_4->addWidget(le_config);

        btn_chConfig = new QPushButton(groupBox_4);
        btn_chConfig->setObjectName(QString::fromUtf8("btn_chConfig"));

        horizontalLayout_4->addWidget(btn_chConfig);


        verticalLayout_3->addWidget(groupBox_4);

        gb_LUD = new QGroupBox(widget_5);
        gb_LUD->setObjectName(QString::fromUtf8("gb_LUD"));
        gb_LUD->setEnabled(false);
        sizePolicy.setHeightForWidth(gb_LUD->sizePolicy().hasHeightForWidth());
        gb_LUD->setSizePolicy(sizePolicy);
        gb_LUD->setMinimumSize(QSize(0, 180));
        gb_LUD->setMaximumSize(QSize(16777215, 180));
        gb_LUD->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(gb_LUD);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(gb_LUD);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 31));
        widget->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rb_one = new QRadioButton(widget);
        rb_one->setObjectName(QString::fromUtf8("rb_one"));
        rb_one->setChecked(true);

        horizontalLayout->addWidget(rb_one);

        rb_two = new QRadioButton(widget);
        rb_two->setObjectName(QString::fromUtf8("rb_two"));

        horizontalLayout->addWidget(rb_two);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(gb_LUD);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        le_input2 = new QLineEdit(widget_2);
        le_input2->setObjectName(QString::fromUtf8("le_input2"));
        le_input2->setEnabled(false);

        gridLayout->addWidget(le_input2, 1, 1, 1, 1);

        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        le_input1 = new QLineEdit(widget_2);
        le_input1->setObjectName(QString::fromUtf8("le_input1"));

        gridLayout->addWidget(le_input1, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);


        verticalLayout->addWidget(widget_2);


        verticalLayout_3->addWidget(gb_LUD);

        gb_PPath = new QGroupBox(widget_5);
        gb_PPath->setObjectName(QString::fromUtf8("gb_PPath"));
        gb_PPath->setEnabled(false);
        sizePolicy.setHeightForWidth(gb_PPath->sizePolicy().hasHeightForWidth());
        gb_PPath->setSizePolicy(sizePolicy);
        gb_PPath->setMinimumSize(QSize(0, 71));
        gb_PPath->setMaximumSize(QSize(16777215, 71));
        gb_PPath->setAlignment(Qt::AlignCenter);
        horizontalLayout_6 = new QHBoxLayout(gb_PPath);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        le_probPath = new QLineEdit(gb_PPath);
        le_probPath->setObjectName(QString::fromUtf8("le_probPath"));

        horizontalLayout_6->addWidget(le_probPath);

        btn_chProbPath = new QPushButton(gb_PPath);
        btn_chProbPath->setObjectName(QString::fromUtf8("btn_chProbPath"));

        horizontalLayout_6->addWidget(btn_chProbPath);


        verticalLayout_3->addWidget(gb_PPath);

        gb_DFD = new QGroupBox(widget_5);
        gb_DFD->setObjectName(QString::fromUtf8("gb_DFD"));
        gb_DFD->setEnabled(false);
        sizePolicy.setHeightForWidth(gb_DFD->sizePolicy().hasHeightForWidth());
        gb_DFD->setSizePolicy(sizePolicy);
        gb_DFD->setMinimumSize(QSize(0, 71));
        gb_DFD->setMaximumSize(QSize(16777215, 71));
        gb_DFD->setAlignment(Qt::AlignCenter);
        horizontalLayout_2 = new QHBoxLayout(gb_DFD);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        le_drive_factor = new QLineEdit(gb_DFD);
        le_drive_factor->setObjectName(QString::fromUtf8("le_drive_factor"));

        horizontalLayout_2->addWidget(le_drive_factor);

        btn_chDir = new QPushButton(gb_DFD);
        btn_chDir->setObjectName(QString::fromUtf8("btn_chDir"));

        horizontalLayout_2->addWidget(btn_chDir);


        verticalLayout_3->addWidget(gb_DFD);

        gb_ANNS = new QGroupBox(widget_5);
        gb_ANNS->setObjectName(QString::fromUtf8("gb_ANNS"));
        gb_ANNS->setEnabled(false);
        sizePolicy1.setHeightForWidth(gb_ANNS->sizePolicy().hasHeightForWidth());
        gb_ANNS->setSizePolicy(sizePolicy1);
        gb_ANNS->setMaximumSize(QSize(16777215, 250));
        gb_ANNS->setLayoutDirection(Qt::LeftToRight);
        gb_ANNS->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(gb_ANNS);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_3 = new QWidget(gb_ANNS);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMinimumSize(QSize(0, 31));
        widget_3->setMaximumSize(QSize(16777215, 31));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        rb_US = new QRadioButton(widget_3);
        rb_US->setObjectName(QString::fromUtf8("rb_US"));

        horizontalLayout_3->addWidget(rb_US);

        rb_RS = new QRadioButton(widget_3);
        rb_RS->setObjectName(QString::fromUtf8("rb_RS"));

        horizontalLayout_3->addWidget(rb_RS);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(gb_ANNS);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(0, 134));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(150, 0));
        label_5->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        cb_norm = new QCheckBox(widget_4);
        cb_norm->setObjectName(QString::fromUtf8("cb_norm"));
        cb_norm->setChecked(true);

        gridLayout_2->addWidget(cb_norm, 0, 1, 1, 1);

        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMinimumSize(QSize(150, 0));
        label_6->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        cb_wl = new QCheckBox(widget_4);
        cb_wl->setObjectName(QString::fromUtf8("cb_wl"));
        cb_wl->setChecked(false);

        gridLayout_2->addWidget(cb_wl, 1, 1, 1, 1);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(150, 0));
        label_3->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        dsb_SR = new QDoubleSpinBox(widget_4);
        dsb_SR->setObjectName(QString::fromUtf8("dsb_SR"));
        dsb_SR->setMinimum(0.000000000000000);
        dsb_SR->setMaximum(100.000000000000000);
        dsb_SR->setValue(0.100000000000000);

        gridLayout_2->addWidget(dsb_SR, 2, 1, 1, 1);

        label_4 = new QLabel(widget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(150, 0));
        label_4->setMaximumSize(QSize(150, 16777215));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        sb_Epochs = new QSpinBox(widget_4);
        sb_Epochs->setObjectName(QString::fromUtf8("sb_Epochs"));
        sb_Epochs->setMinimum(2);
        sb_Epochs->setMaximum(300);

        gridLayout_2->addWidget(sb_Epochs, 3, 1, 1, 1);


        verticalLayout_2->addWidget(widget_4);


        verticalLayout_3->addWidget(gb_ANNS);

        btn_saveConfig = new QPushButton(widget_5);
        btn_saveConfig->setObjectName(QString::fromUtf8("btn_saveConfig"));
        btn_saveConfig->setEnabled(false);
        btn_saveConfig->setMinimumSize(QSize(0, 25));
        btn_saveConfig->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(btn_saveConfig);

        splitter->addWidget(widget_5);
        widget_6 = new QWidget(splitter);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        verticalLayout_5 = new QVBoxLayout(widget_6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        sizePolicy.setHeightForWidth(widget_7->sizePolicy().hasHeightForWidth());
        widget_7->setSizePolicy(sizePolicy);
        widget_7->setMinimumSize(QSize(0, 53));
        widget_7->setMaximumSize(QSize(16777213, 53));
        horizontalLayout_7 = new QHBoxLayout(widget_7);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        btn_startSim = new QPushButton(widget_7);
        btn_startSim->setObjectName(QString::fromUtf8("btn_startSim"));
        btn_startSim->setEnabled(false);
        btn_startSim->setMinimumSize(QSize(0, 35));
        btn_startSim->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_7->addWidget(btn_startSim);

        btn_stopSim = new QPushButton(widget_7);
        btn_stopSim->setObjectName(QString::fromUtf8("btn_stopSim"));
        btn_stopSim->setEnabled(false);
        btn_stopSim->setMinimumSize(QSize(0, 35));
        btn_stopSim->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_7->addWidget(btn_stopSim);


        verticalLayout_5->addWidget(widget_7);

        widget_8 = new QWidget(widget_6);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        sizePolicy.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy);
        widget_8->setMinimumSize(QSize(0, 70));
        widget_8->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_8 = new QHBoxLayout(widget_8);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QWidget(widget_8);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        verticalLayout_4 = new QVBoxLayout(widget_9);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pgb_epochs = new QProgressBar(widget_9);
        pgb_epochs->setObjectName(QString::fromUtf8("pgb_epochs"));
        pgb_epochs->setMinimumSize(QSize(0, 23));
        pgb_epochs->setSizeIncrement(QSize(0, 23));
        pgb_epochs->setValue(0);

        verticalLayout_4->addWidget(pgb_epochs);

        pgb_subepochs = new QProgressBar(widget_9);
        pgb_subepochs->setObjectName(QString::fromUtf8("pgb_subepochs"));
        pgb_subepochs->setMinimumSize(QSize(0, 23));
        pgb_subepochs->setMaximumSize(QSize(16777215, 23));
        pgb_subepochs->setValue(0);

        verticalLayout_4->addWidget(pgb_subepochs);


        horizontalLayout_8->addWidget(widget_9);

        w_loading = new Loading(widget_8);
        w_loading->setObjectName(QString::fromUtf8("w_loading"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(w_loading->sizePolicy().hasHeightForWidth());
        w_loading->setSizePolicy(sizePolicy3);
        w_loading->setMinimumSize(QSize(110, 60));
        w_loading->setMaximumSize(QSize(110, 60));

        horizontalLayout_8->addWidget(w_loading);


        verticalLayout_5->addWidget(widget_8);

        te_res = new QTextEdit(widget_6);
        te_res->setObjectName(QString::fromUtf8("te_res"));

        verticalLayout_5->addWidget(te_res);

        splitter->addWidget(widget_6);

        horizontalLayout_5->addWidget(splitter);


        retranslateUi(ANNDialog);

        QMetaObject::connectSlotsByName(ANNDialog);
    } // setupUi

    void retranslateUi(QDialog *ANNDialog)
    {
        ANNDialog->setWindowTitle(QCoreApplication::translate("ANNDialog", "ANN", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ANNDialog", "Load Config", nullptr));
        btn_chConfig->setText(QCoreApplication::translate("ANNDialog", "\351\200\211\346\213\251", nullptr));
        gb_LUD->setTitle(QCoreApplication::translate("ANNDialog", "Land Use Data", nullptr));
        rb_one->setText(QCoreApplication::translate("ANNDialog", "\344\270\200\346\234\237\346\225\260\346\215\256", nullptr));
        rb_two->setText(QCoreApplication::translate("ANNDialog", "\344\270\244\346\234\237\346\225\260\346\215\256", nullptr));
        pushButton->setText(QCoreApplication::translate("ANNDialog", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("ANNDialog", "\345\234\237\345\234\260\345\210\251\347\224\250\346\225\260\346\215\2562", nullptr));
        label->setText(QCoreApplication::translate("ANNDialog", "\345\234\237\345\234\260\345\210\251\347\224\250\346\225\260\346\215\2561", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ANNDialog", "\351\200\211\346\213\251", nullptr));
        gb_PPath->setTitle(QCoreApplication::translate("ANNDialog", "Probability", nullptr));
        btn_chProbPath->setText(QCoreApplication::translate("ANNDialog", "\351\200\211\346\213\251", nullptr));
        gb_DFD->setTitle(QCoreApplication::translate("ANNDialog", "Drive Factors Dir", nullptr));
        btn_chDir->setText(QCoreApplication::translate("ANNDialog", "\351\200\211\346\213\251", nullptr));
        gb_ANNS->setTitle(QCoreApplication::translate("ANNDialog", "ANN Settings", nullptr));
        rb_US->setText(QCoreApplication::translate("ANNDialog", "Uniform Samping", nullptr));
        rb_RS->setText(QCoreApplication::translate("ANNDialog", "Random Sampling", nullptr));
        label_5->setText(QCoreApplication::translate("ANNDialog", "Norm", nullptr));
        cb_norm->setText(QString());
        label_6->setText(QCoreApplication::translate("ANNDialog", "weighted_loss", nullptr));
        cb_wl->setText(QString());
        label_3->setText(QCoreApplication::translate("ANNDialog", "Sampling Rate (1/100)", nullptr));
        label_4->setText(QCoreApplication::translate("ANNDialog", "Epochs", nullptr));
        btn_saveConfig->setText(QCoreApplication::translate("ANNDialog", "\344\277\235\345\255\230", nullptr));
        btn_startSim->setText(QCoreApplication::translate("ANNDialog", "Start Simulation", nullptr));
        btn_stopSim->setText(QCoreApplication::translate("ANNDialog", "Stop Simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ANNDialog: public Ui_ANNDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNDIALOG_H
