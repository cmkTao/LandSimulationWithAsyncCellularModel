/********************************************************************************
** Form generated from reading UI file 'batchcasimdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATCHCASIMDIALOG_H
#define UI_BATCHCASIMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customWidget/Loading/Loading.h>

QT_BEGIN_NAMESPACE

class Ui_BatchCASimDialog
{
public:
    QGridLayout *gridLayout_5;
    QSplitter *splitter;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *le_targetPath;
    QPushButton *pb_targetPath;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *le_startPath;
    QPushButton *pb_starPath;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *le_probPath;
    QPushButton *pb_probFile;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *le_logPath;
    QPushButton *pb_logPath;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_runDir;
    QPushButton *pb_runDir;
    QWidget *widget_4;
    QGridLayout *gridLayout_6;
    QSpinBox *sb_runTimes;
    QCheckBox *cb_newRepeatNum;
    QLabel *label;
    QSpinBox *sb_threadNum;
    QLabel *label_3;
    QCheckBox *cb_toExcel;
    QWidget *widget_11;
    QGridLayout *gridLayout_4;
    QRadioButton *rb_eval;
    QRadioButton *rb_batchChange;
    QRadioButton *rb_sim;
    QRadioButton *rb_batchChangeParam;
    QPushButton *pushButton;
    QTableWidget *tw_configs;
    QWidget *widget_14;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gb_simConfig;
    QGridLayout *gridLayout_3;
    QSpinBox *sb_NO;
    QLabel *label_9;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *sp_endDiffValue;
    QSpinBox *sb_MIN;
    QTabWidget *tab_matrix;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_9;
    QTableWidget *tw_LUD;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_11;
    QTableWidget *tw_CM;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_12;
    QTableWidget *tw_WN;
    QWidget *widget_8;
    QGridLayout *gridLayout;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_pause;
    Loading *w_loading;
    QTextEdit *te_res;
    QWidget *widget_5;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QProgressBar *pb_overall;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *proB_curSim;
    QProgressBar *pb_curSim;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *proB_curConfig;
    QProgressBar *pb_curConfig;

    void setupUi(QDialog *BatchCASimDialog)
    {
        if (BatchCASimDialog->objectName().isEmpty())
            BatchCASimDialog->setObjectName(QString::fromUtf8("BatchCASimDialog"));
        BatchCASimDialog->resize(1200, 700);
        gridLayout_5 = new QGridLayout(BatchCASimDialog);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        splitter = new QSplitter(BatchCASimDialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget_10 = new QWidget(splitter);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        verticalLayout = new QVBoxLayout(widget_10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(widget_10);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        le_targetPath = new QLineEdit(widget);
        le_targetPath->setObjectName(QString::fromUtf8("le_targetPath"));

        horizontalLayout->addWidget(le_targetPath);

        pb_targetPath = new QPushButton(widget);
        pb_targetPath->setObjectName(QString::fromUtf8("pb_targetPath"));

        horizontalLayout->addWidget(pb_targetPath);


        verticalLayout->addWidget(widget);

        widget_12 = new QWidget(widget_10);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        horizontalLayout_8 = new QHBoxLayout(widget_12);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        le_startPath = new QLineEdit(widget_12);
        le_startPath->setObjectName(QString::fromUtf8("le_startPath"));

        horizontalLayout_8->addWidget(le_startPath);

        pb_starPath = new QPushButton(widget_12);
        pb_starPath->setObjectName(QString::fromUtf8("pb_starPath"));

        horizontalLayout_8->addWidget(pb_starPath);


        verticalLayout->addWidget(widget_12);

        widget_13 = new QWidget(widget_10);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        horizontalLayout_10 = new QHBoxLayout(widget_13);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        le_probPath = new QLineEdit(widget_13);
        le_probPath->setObjectName(QString::fromUtf8("le_probPath"));

        horizontalLayout_10->addWidget(le_probPath);

        pb_probFile = new QPushButton(widget_13);
        pb_probFile->setObjectName(QString::fromUtf8("pb_probFile"));
        pb_probFile->setMinimumSize(QSize(113, 0));

        horizontalLayout_10->addWidget(pb_probFile);


        verticalLayout->addWidget(widget_13);

        widget_2 = new QWidget(widget_10);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        le_logPath = new QLineEdit(widget_2);
        le_logPath->setObjectName(QString::fromUtf8("le_logPath"));

        horizontalLayout_2->addWidget(le_logPath);

        pb_logPath = new QPushButton(widget_2);
        pb_logPath->setObjectName(QString::fromUtf8("pb_logPath"));
        pb_logPath->setMinimumSize(QSize(113, 0));

        horizontalLayout_2->addWidget(pb_logPath);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_10);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        le_runDir = new QLineEdit(widget_3);
        le_runDir->setObjectName(QString::fromUtf8("le_runDir"));

        horizontalLayout_3->addWidget(le_runDir);

        pb_runDir = new QPushButton(widget_3);
        pb_runDir->setObjectName(QString::fromUtf8("pb_runDir"));
        pb_runDir->setMinimumSize(QSize(113, 0));

        horizontalLayout_3->addWidget(pb_runDir);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget_10);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_6 = new QGridLayout(widget_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        sb_runTimes = new QSpinBox(widget_4);
        sb_runTimes->setObjectName(QString::fromUtf8("sb_runTimes"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sb_runTimes->sizePolicy().hasHeightForWidth());
        sb_runTimes->setSizePolicy(sizePolicy);
        sb_runTimes->setMinimumSize(QSize(113, 0));
        sb_runTimes->setMaximumSize(QSize(113, 16777215));
        sb_runTimes->setMinimum(1);
        sb_runTimes->setMaximum(10);
        sb_runTimes->setValue(3);

        gridLayout_6->addWidget(sb_runTimes, 0, 3, 1, 1);

        cb_newRepeatNum = new QCheckBox(widget_4);
        cb_newRepeatNum->setObjectName(QString::fromUtf8("cb_newRepeatNum"));
        cb_newRepeatNum->setChecked(true);

        gridLayout_6->addWidget(cb_newRepeatNum, 0, 0, 1, 1);

        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_6->addWidget(label, 0, 1, 1, 1);

        sb_threadNum = new QSpinBox(widget_4);
        sb_threadNum->setObjectName(QString::fromUtf8("sb_threadNum"));
        sb_threadNum->setMinimum(1);

        gridLayout_6->addWidget(sb_threadNum, 1, 3, 1, 1);

        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_6->addWidget(label_3, 1, 1, 1, 1);

        cb_toExcel = new QCheckBox(widget_4);
        cb_toExcel->setObjectName(QString::fromUtf8("cb_toExcel"));

        gridLayout_6->addWidget(cb_toExcel, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_4);

        widget_11 = new QWidget(widget_10);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        gridLayout_4 = new QGridLayout(widget_11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        rb_eval = new QRadioButton(widget_11);
        rb_eval->setObjectName(QString::fromUtf8("rb_eval"));

        gridLayout_4->addWidget(rb_eval, 0, 1, 1, 1);

        rb_batchChange = new QRadioButton(widget_11);
        rb_batchChange->setObjectName(QString::fromUtf8("rb_batchChange"));

        gridLayout_4->addWidget(rb_batchChange, 0, 2, 1, 1);

        rb_sim = new QRadioButton(widget_11);
        rb_sim->setObjectName(QString::fromUtf8("rb_sim"));
        rb_sim->setChecked(true);

        gridLayout_4->addWidget(rb_sim, 0, 0, 1, 1);

        rb_batchChangeParam = new QRadioButton(widget_11);
        rb_batchChangeParam->setObjectName(QString::fromUtf8("rb_batchChangeParam"));

        gridLayout_4->addWidget(rb_batchChangeParam, 0, 3, 1, 1);


        verticalLayout->addWidget(widget_11);

        pushButton = new QPushButton(widget_10);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        tw_configs = new QTableWidget(widget_10);
        tw_configs->setObjectName(QString::fromUtf8("tw_configs"));
        tw_configs->setTextElideMode(Qt::ElideRight);

        verticalLayout->addWidget(tw_configs);

        splitter->addWidget(widget_10);
        widget_14 = new QWidget(splitter);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        verticalLayout_2 = new QVBoxLayout(widget_14);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gb_simConfig = new QGroupBox(widget_14);
        gb_simConfig->setObjectName(QString::fromUtf8("gb_simConfig"));
        gb_simConfig->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gb_simConfig->sizePolicy().hasHeightForWidth());
        gb_simConfig->setSizePolicy(sizePolicy1);
        gb_simConfig->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(gb_simConfig);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        sb_NO = new QSpinBox(gb_simConfig);
        sb_NO->setObjectName(QString::fromUtf8("sb_NO"));
        sb_NO->setMinimum(3);
        sb_NO->setSingleStep(2);

        gridLayout_3->addWidget(sb_NO, 2, 2, 1, 2);

        label_9 = new QLabel(gb_simConfig);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        label_5 = new QLabel(gb_simConfig);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        label_4 = new QLabel(gb_simConfig);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        sp_endDiffValue = new QSpinBox(gb_simConfig);
        sp_endDiffValue->setObjectName(QString::fromUtf8("sp_endDiffValue"));
        sp_endDiffValue->setMaximum(1000);

        gridLayout_3->addWidget(sp_endDiffValue, 0, 2, 1, 2);

        sb_MIN = new QSpinBox(gb_simConfig);
        sb_MIN->setObjectName(QString::fromUtf8("sb_MIN"));
        sb_MIN->setMinimum(1);
        sb_MIN->setMaximum(5000);

        gridLayout_3->addWidget(sb_MIN, 1, 2, 1, 2);


        verticalLayout_2->addWidget(gb_simConfig);

        tab_matrix = new QTabWidget(widget_14);
        tab_matrix->setObjectName(QString::fromUtf8("tab_matrix"));
        tab_matrix->setEnabled(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_9 = new QHBoxLayout(tab);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        tw_LUD = new QTableWidget(tab);
        tw_LUD->setObjectName(QString::fromUtf8("tw_LUD"));

        horizontalLayout_9->addWidget(tw_LUD);

        tab_matrix->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_11 = new QHBoxLayout(tab_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        tw_CM = new QTableWidget(tab_2);
        tw_CM->setObjectName(QString::fromUtf8("tw_CM"));

        horizontalLayout_11->addWidget(tw_CM);

        tab_matrix->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_12 = new QHBoxLayout(tab_3);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        tw_WN = new QTableWidget(tab_3);
        tw_WN->setObjectName(QString::fromUtf8("tw_WN"));

        horizontalLayout_12->addWidget(tw_WN);

        tab_matrix->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tab_matrix);

        splitter->addWidget(widget_14);
        widget_8 = new QWidget(splitter);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setMaximumSize(QSize(300, 16777215));
        gridLayout = new QGridLayout(widget_8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_9 = new QWidget(widget_8);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        sizePolicy1.setHeightForWidth(widget_9->sizePolicy().hasHeightForWidth());
        widget_9->setSizePolicy(sizePolicy1);
        widget_9->setMinimumSize(QSize(0, 60));
        widget_9->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_5 = new QHBoxLayout(widget_9);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btn_start = new QPushButton(widget_9);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setEnabled(true);
        btn_start->setMinimumSize(QSize(0, 45));
        btn_start->setMaximumSize(QSize(16777215, 45));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_start->setIcon(icon);
        btn_start->setIconSize(QSize(40, 40));

        horizontalLayout_5->addWidget(btn_start);

        btn_stop = new QPushButton(widget_9);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setEnabled(false);
        btn_stop->setMinimumSize(QSize(0, 45));
        btn_stop->setMaximumSize(QSize(16777215, 45));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_stop->setIcon(icon1);
        btn_stop->setIconSize(QSize(40, 40));

        horizontalLayout_5->addWidget(btn_stop);

        btn_pause = new QPushButton(widget_9);
        btn_pause->setObjectName(QString::fromUtf8("btn_pause"));
        btn_pause->setEnabled(false);
        btn_pause->setMinimumSize(QSize(0, 45));
        btn_pause->setMaximumSize(QSize(16777215, 45));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_pause->setIcon(icon2);
        btn_pause->setIconSize(QSize(40, 40));

        horizontalLayout_5->addWidget(btn_pause);

        w_loading = new Loading(widget_9);
        w_loading->setObjectName(QString::fromUtf8("w_loading"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(w_loading->sizePolicy().hasHeightForWidth());
        w_loading->setSizePolicy(sizePolicy2);
        w_loading->setMinimumSize(QSize(100, 50));
        w_loading->setMaximumSize(QSize(50, 50));

        horizontalLayout_5->addWidget(w_loading);

        btn_start->raise();
        btn_pause->raise();
        w_loading->raise();
        btn_stop->raise();

        gridLayout->addWidget(widget_9, 0, 0, 1, 1);

        te_res = new QTextEdit(widget_8);
        te_res->setObjectName(QString::fromUtf8("te_res"));
        te_res->setEnabled(true);
        te_res->setReadOnly(true);

        gridLayout->addWidget(te_res, 4, 0, 1, 1);

        widget_5 = new QWidget(widget_8);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_2 = new QGridLayout(widget_5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(widget_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);
        label_2->setMinimumSize(QSize(84, 0));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        pb_overall = new QProgressBar(widget_5);
        pb_overall->setObjectName(QString::fromUtf8("pb_overall"));
        pb_overall->setValue(0);

        gridLayout_2->addWidget(pb_overall, 0, 1, 1, 1);


        gridLayout->addWidget(widget_5, 1, 0, 1, 1);

        widget_7 = new QWidget(widget_8);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_7 = new QHBoxLayout(widget_7);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        proB_curSim = new QLabel(widget_7);
        proB_curSim->setObjectName(QString::fromUtf8("proB_curSim"));

        horizontalLayout_7->addWidget(proB_curSim);

        pb_curSim = new QProgressBar(widget_7);
        pb_curSim->setObjectName(QString::fromUtf8("pb_curSim"));
        pb_curSim->setValue(0);

        horizontalLayout_7->addWidget(pb_curSim);


        gridLayout->addWidget(widget_7, 3, 0, 1, 1);

        widget_6 = new QWidget(widget_8);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        proB_curConfig = new QLabel(widget_6);
        proB_curConfig->setObjectName(QString::fromUtf8("proB_curConfig"));

        horizontalLayout_6->addWidget(proB_curConfig);

        pb_curConfig = new QProgressBar(widget_6);
        pb_curConfig->setObjectName(QString::fromUtf8("pb_curConfig"));
        pb_curConfig->setValue(0);

        horizontalLayout_6->addWidget(pb_curConfig);


        gridLayout->addWidget(widget_6, 2, 0, 1, 1);

        splitter->addWidget(widget_8);

        gridLayout_5->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(BatchCASimDialog);

        tab_matrix->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(BatchCASimDialog);
    } // setupUi

    void retranslateUi(QDialog *BatchCASimDialog)
    {
        BatchCASimDialog->setWindowTitle(QCoreApplication::translate("BatchCASimDialog", "BatchSimulation/Validation", nullptr));
#if QT_CONFIG(whatsthis)
        BatchCASimDialog->setWhatsThis(QCoreApplication::translate("BatchCASimDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">## 1</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pb_targetPath->setText(QCoreApplication::translate("BatchCASimDialog", "\351\200\211\346\213\251\347\233\256\346\240\207\345\271\264\344\273\275tif", nullptr));
        pb_starPath->setText(QCoreApplication::translate("BatchCASimDialog", "\351\200\211\346\213\251\346\250\241\346\213\237\350\265\267\347\202\271tif", nullptr));
        pb_probFile->setText(QCoreApplication::translate("BatchCASimDialog", "\351\200\211\346\213\251\346\246\202\347\216\207tif", nullptr));
        pb_logPath->setText(QCoreApplication::translate("BatchCASimDialog", "\346\200\273\346\227\245\345\277\227\344\275\215\347\275\256", nullptr));
        pb_runDir->setText(QCoreApplication::translate("BatchCASimDialog", "\351\200\211\346\213\251\350\277\220\350\241\214\347\233\256\345\275\225", nullptr));
#if QT_CONFIG(tooltip)
        sb_runTimes->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        cb_newRepeatNum->setText(QCoreApplication::translate("BatchCASimDialog", " \350\256\276\347\275\256\346\226\260\347\232\204", nullptr));
        label->setText(QCoreApplication::translate("BatchCASimDialog", "\346\257\217\344\270\252\351\205\215\347\275\256\350\277\220\350\241\214\346\254\241\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("BatchCASimDialog", " \347\272\277\347\250\213\346\225\260", nullptr));
        cb_toExcel->setText(QCoreApplication::translate("BatchCASimDialog", "\345\257\274\345\207\272\345\210\260Excel", nullptr));
        rb_eval->setText(QCoreApplication::translate("BatchCASimDialog", "\351\252\214\350\257\201", nullptr));
        rb_batchChange->setText(QCoreApplication::translate("BatchCASimDialog", "\346\211\271\351\207\217\346\224\271\350\265\267\347\202\271/prob", nullptr));
        rb_sim->setText(QCoreApplication::translate("BatchCASimDialog", "\346\250\241\346\213\237", nullptr));
        rb_batchChangeParam->setText(QCoreApplication::translate("BatchCASimDialog", "\346\211\271\351\207\217\345\217\202\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("BatchCASimDialog", "\346\211\271\351\207\217\346\267\273\345\212\240", nullptr));
        gb_simConfig->setTitle(QCoreApplication::translate("BatchCASimDialog", "SIM CONFIG", nullptr));
        label_9->setText(QCoreApplication::translate("BatchCASimDialog", "endConditionValue", nullptr));
        label_5->setText(QCoreApplication::translate("BatchCASimDialog", "NeighboorhoodOdd", nullptr));
        label_4->setText(QCoreApplication::translate("BatchCASimDialog", "MaxIterNum", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab), QCoreApplication::translate("BatchCASimDialog", "LandUseDemand", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab_2), QCoreApplication::translate("BatchCASimDialog", "CostMatrix", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab_3), QCoreApplication::translate("BatchCASimDialog", "WeightOfNeighborhood", nullptr));
        btn_start->setText(QString());
        btn_stop->setText(QString());
        btn_pause->setText(QString());
#if QT_CONFIG(whatsthis)
        w_loading->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        label_2->setText(QCoreApplication::translate("BatchCASimDialog", "\346\200\273\350\277\233\345\272\246", nullptr));
        pb_overall->setFormat(QCoreApplication::translate("BatchCASimDialog", "%p%", nullptr));
        proB_curSim->setText(QCoreApplication::translate("BatchCASimDialog", "\346\234\254\346\254\241\346\250\241\346\213\237\350\277\233\345\272\246", nullptr));
        proB_curConfig->setText(QCoreApplication::translate("BatchCASimDialog", "\345\275\223\345\211\215\351\205\215\347\275\256\350\277\233\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BatchCASimDialog: public Ui_BatchCASimDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATCHCASIMDIALOG_H
