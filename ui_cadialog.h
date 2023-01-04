/********************************************************************************
** Form generated from reading UI file 'cadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADIALOG_H
#define UI_CADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
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
#include <mapwidget.h>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_CADialog
{
public:
    QHBoxLayout *horizontalLayout_6;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QComboBox *comboBox;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_configPath;
    QPushButton *btn_chConfig;
    QGroupBox *gb_filePath;
    QGridLayout *gridLayout;
    QPushButton *btn_lu;
    QLabel *label_2;
    QLineEdit *le_res;
    QLineEdit *le_prob;
    QPushButton *btn_res;
    QLabel *label_7;
    QLineEdit *le_landuse;
    QPushButton *btn_sp;
    QLabel *label;
    QPushButton *btn_prob;
    QLabel *label_3;
    QLineEdit *le_sp;
    QGroupBox *gb_simConfig;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QRadioButton *rb_one;
    QLabel *label_6;
    QDoubleSpinBox *dsb_Degree;
    QLabel *label_4;
    QSpinBox *sb_MIN;
    QRadioButton *rb_two;
    QLabel *label_9;
    QSpinBox *sp_endDiffValue;
    QSpinBox *sb_NO;
    QTabWidget *tab_matrix;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tw_LUD;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tw_CM;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tw_WN;
    QWidget *w_save;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_saveConfig;
    QPushButton *btn_saveOther;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_pause;
    Loading *w_loading;
    QProgressBar *pgb_process;
    QWidget *widget_5;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QComboBox *cb_caType;
    QDoubleSpinBox *doubleSpinBox;
    QTextEdit *te_res;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QSplitter *splitter_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_3;
    QChartView *chart_landCounts;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tw_colors;
    MapWidget *gv_map;

    void setupUi(QDialog *CADialog)
    {
        if (CADialog->objectName().isEmpty())
            CADialog->setObjectName(QString::fromUtf8("CADialog"));
        CADialog->resize(1624, 921);
        horizontalLayout_6 = new QHBoxLayout(CADialog);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        splitter = new QSplitter(CADialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(400, 0));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_4->addWidget(comboBox, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(0, 63));
        groupBox_3->setMaximumSize(QSize(16777215, 63));
        groupBox_3->setAlignment(Qt::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 0, 2, 0);
        le_configPath = new QLineEdit(groupBox_3);
        le_configPath->setObjectName(QString::fromUtf8("le_configPath"));

        horizontalLayout_4->addWidget(le_configPath);

        btn_chConfig = new QPushButton(groupBox_3);
        btn_chConfig->setObjectName(QString::fromUtf8("btn_chConfig"));

        horizontalLayout_4->addWidget(btn_chConfig);


        verticalLayout->addWidget(groupBox_3);

        gb_filePath = new QGroupBox(widget);
        gb_filePath->setObjectName(QString::fromUtf8("gb_filePath"));
        gb_filePath->setEnabled(true);
        sizePolicy.setHeightForWidth(gb_filePath->sizePolicy().hasHeightForWidth());
        gb_filePath->setSizePolicy(sizePolicy);
        gb_filePath->setMinimumSize(QSize(0, 170));
        gb_filePath->setMaximumSize(QSize(16777215, 170));
        gb_filePath->setAlignment(Qt::AlignCenter);
        gridLayout = new QGridLayout(gb_filePath);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_lu = new QPushButton(gb_filePath);
        btn_lu->setObjectName(QString::fromUtf8("btn_lu"));

        gridLayout->addWidget(btn_lu, 0, 2, 1, 1);

        label_2 = new QLabel(gb_filePath);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        le_res = new QLineEdit(gb_filePath);
        le_res->setObjectName(QString::fromUtf8("le_res"));
        le_res->setEnabled(false);

        gridLayout->addWidget(le_res, 6, 1, 1, 1);

        le_prob = new QLineEdit(gb_filePath);
        le_prob->setObjectName(QString::fromUtf8("le_prob"));
        le_prob->setEnabled(false);

        gridLayout->addWidget(le_prob, 4, 1, 1, 1);

        btn_res = new QPushButton(gb_filePath);
        btn_res->setObjectName(QString::fromUtf8("btn_res"));
        btn_res->setEnabled(false);

        gridLayout->addWidget(btn_res, 6, 2, 1, 1);

        label_7 = new QLabel(gb_filePath);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        le_landuse = new QLineEdit(gb_filePath);
        le_landuse->setObjectName(QString::fromUtf8("le_landuse"));

        gridLayout->addWidget(le_landuse, 0, 1, 1, 1);

        btn_sp = new QPushButton(gb_filePath);
        btn_sp->setObjectName(QString::fromUtf8("btn_sp"));
        btn_sp->setEnabled(false);

        gridLayout->addWidget(btn_sp, 3, 2, 1, 1);

        label = new QLabel(gb_filePath);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        btn_prob = new QPushButton(gb_filePath);
        btn_prob->setObjectName(QString::fromUtf8("btn_prob"));
        btn_prob->setEnabled(false);

        gridLayout->addWidget(btn_prob, 4, 2, 1, 1);

        label_3 = new QLabel(gb_filePath);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        le_sp = new QLineEdit(gb_filePath);
        le_sp->setObjectName(QString::fromUtf8("le_sp"));
        le_sp->setEnabled(false);

        gridLayout->addWidget(le_sp, 3, 1, 1, 1);


        verticalLayout->addWidget(gb_filePath);

        gb_simConfig = new QGroupBox(widget);
        gb_simConfig->setObjectName(QString::fromUtf8("gb_simConfig"));
        gb_simConfig->setEnabled(false);
        sizePolicy.setHeightForWidth(gb_simConfig->sizePolicy().hasHeightForWidth());
        gb_simConfig->setSizePolicy(sizePolicy);
        gb_simConfig->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(gb_simConfig);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(gb_simConfig);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        rb_one = new QRadioButton(gb_simConfig);
        rb_one->setObjectName(QString::fromUtf8("rb_one"));
        rb_one->setChecked(true);

        gridLayout_2->addWidget(rb_one, 1, 0, 1, 1);

        label_6 = new QLabel(gb_simConfig);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        dsb_Degree = new QDoubleSpinBox(gb_simConfig);
        dsb_Degree->setObjectName(QString::fromUtf8("dsb_Degree"));
        dsb_Degree->setMinimum(0.100000000000000);
        dsb_Degree->setMaximum(1.000000000000000);
        dsb_Degree->setSingleStep(0.010000000000000);

        gridLayout_2->addWidget(dsb_Degree, 4, 2, 1, 2);

        label_4 = new QLabel(gb_simConfig);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        sb_MIN = new QSpinBox(gb_simConfig);
        sb_MIN->setObjectName(QString::fromUtf8("sb_MIN"));
        sb_MIN->setMinimum(1);
        sb_MIN->setMaximum(5000);

        gridLayout_2->addWidget(sb_MIN, 2, 2, 1, 2);

        rb_two = new QRadioButton(gb_simConfig);
        rb_two->setObjectName(QString::fromUtf8("rb_two"));

        gridLayout_2->addWidget(rb_two, 1, 3, 1, 1);

        label_9 = new QLabel(gb_simConfig);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);

        sp_endDiffValue = new QSpinBox(gb_simConfig);
        sp_endDiffValue->setObjectName(QString::fromUtf8("sp_endDiffValue"));
        sp_endDiffValue->setMaximum(1000);

        gridLayout_2->addWidget(sp_endDiffValue, 0, 2, 1, 2);

        sb_NO = new QSpinBox(gb_simConfig);
        sb_NO->setObjectName(QString::fromUtf8("sb_NO"));
        sb_NO->setMinimum(3);
        sb_NO->setSingleStep(2);

        gridLayout_2->addWidget(sb_NO, 3, 2, 1, 2);


        verticalLayout->addWidget(gb_simConfig);

        tab_matrix = new QTabWidget(widget);
        tab_matrix->setObjectName(QString::fromUtf8("tab_matrix"));
        tab_matrix->setEnabled(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tw_LUD = new QTableWidget(tab);
        tw_LUD->setObjectName(QString::fromUtf8("tw_LUD"));

        horizontalLayout->addWidget(tw_LUD);

        tab_matrix->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tw_CM = new QTableWidget(tab_2);
        tw_CM->setObjectName(QString::fromUtf8("tw_CM"));

        horizontalLayout_2->addWidget(tw_CM);

        tab_matrix->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_3 = new QHBoxLayout(tab_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tw_WN = new QTableWidget(tab_3);
        tw_WN->setObjectName(QString::fromUtf8("tw_WN"));

        horizontalLayout_3->addWidget(tw_WN);

        tab_matrix->addTab(tab_3, QString());

        verticalLayout->addWidget(tab_matrix);

        w_save = new QWidget(widget);
        w_save->setObjectName(QString::fromUtf8("w_save"));
        w_save->setEnabled(true);
        sizePolicy.setHeightForWidth(w_save->sizePolicy().hasHeightForWidth());
        w_save->setSizePolicy(sizePolicy);
        w_save->setMinimumSize(QSize(0, 40));
        w_save->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_7 = new QHBoxLayout(w_save);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        btn_saveConfig = new QPushButton(w_save);
        btn_saveConfig->setObjectName(QString::fromUtf8("btn_saveConfig"));
        btn_saveConfig->setEnabled(false);

        horizontalLayout_7->addWidget(btn_saveConfig);

        btn_saveOther = new QPushButton(w_save);
        btn_saveOther->setObjectName(QString::fromUtf8("btn_saveOther"));
        btn_saveOther->setEnabled(false);

        horizontalLayout_7->addWidget(btn_saveOther);


        verticalLayout->addWidget(w_save);

        splitter->addWidget(widget);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setMinimumSize(QSize(0, 53));
        widget_3->setMaximumSize(QSize(16777215, 53));
        horizontalLayout_5 = new QHBoxLayout(widget_3);
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btn_start = new QPushButton(widget_3);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setEnabled(false);
        btn_start->setMinimumSize(QSize(0, 35));
        btn_start->setMaximumSize(QSize(16777215, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_start->setIcon(icon);
        btn_start->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(btn_start);

        btn_stop = new QPushButton(widget_3);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));
        btn_stop->setEnabled(false);
        btn_stop->setMinimumSize(QSize(0, 35));
        btn_stop->setMaximumSize(QSize(16777215, 35));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_stop->setIcon(icon1);
        btn_stop->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(btn_stop);

        btn_pause = new QPushButton(widget_3);
        btn_pause->setObjectName(QString::fromUtf8("btn_pause"));
        btn_pause->setEnabled(false);
        btn_pause->setMinimumSize(QSize(0, 35));
        btn_pause->setMaximumSize(QSize(16777215, 35));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_pause->setIcon(icon2);
        btn_pause->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(btn_pause);

        w_loading = new Loading(widget_3);
        w_loading->setObjectName(QString::fromUtf8("w_loading"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(w_loading->sizePolicy().hasHeightForWidth());
        w_loading->setSizePolicy(sizePolicy1);
        w_loading->setMinimumSize(QSize(50, 50));
        w_loading->setMaximumSize(QSize(50, 50));

        horizontalLayout_5->addWidget(w_loading);

        btn_start->raise();
        btn_pause->raise();
        w_loading->raise();
        btn_stop->raise();

        verticalLayout_2->addWidget(widget_3);

        pgb_process = new QProgressBar(widget_2);
        pgb_process->setObjectName(QString::fromUtf8("pgb_process"));
        pgb_process->setValue(0);

        verticalLayout_2->addWidget(pgb_process);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        sizePolicy.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(widget_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        cb_caType = new QComboBox(widget_5);
        cb_caType->addItem(QString());
        cb_caType->addItem(QString());
        cb_caType->setObjectName(QString::fromUtf8("cb_caType"));

        gridLayout_3->addWidget(cb_caType, 0, 0, 1, 2);

        doubleSpinBox = new QDoubleSpinBox(widget_5);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximum(1.000000000000000);
        doubleSpinBox->setSingleStep(0.100000000000000);
        doubleSpinBox->setValue(1.000000000000000);

        gridLayout_3->addWidget(doubleSpinBox, 1, 1, 1, 1);


        verticalLayout_2->addWidget(widget_5);

        te_res = new QTextEdit(widget_2);
        te_res->setObjectName(QString::fromUtf8("te_res"));
        te_res->setReadOnly(false);

        verticalLayout_2->addWidget(te_res);

        splitter->addWidget(widget_2);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(groupBox);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widget_4 = new QWidget(splitter_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_3 = new QSplitter(widget_4);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        chart_landCounts = new QChartView(splitter_3);
        chart_landCounts->setObjectName(QString::fromUtf8("chart_landCounts"));
        chart_landCounts->setMinimumSize(QSize(500, 0));
        splitter_3->addWidget(chart_landCounts);
        groupBox_4 = new QGroupBox(splitter_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(0, 300));
        groupBox_4->setMaximumSize(QSize(16777215, 300));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tw_colors = new QTableWidget(groupBox_4);
        tw_colors->setObjectName(QString::fromUtf8("tw_colors"));

        verticalLayout_4->addWidget(tw_colors);

        splitter_3->addWidget(groupBox_4);

        verticalLayout_3->addWidget(splitter_3);

        splitter_2->addWidget(widget_4);
        gv_map = new MapWidget(splitter_2);
        gv_map->setObjectName(QString::fromUtf8("gv_map"));
        gv_map->setMinimumSize(QSize(500, 0));
        splitter_2->addWidget(gv_map);

        horizontalLayout_8->addWidget(splitter_2);

        splitter->addWidget(groupBox);

        horizontalLayout_6->addWidget(splitter);


        retranslateUi(CADialog);

        tab_matrix->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CADialog);
    } // setupUi

    void retranslateUi(QDialog *CADialog)
    {
        CADialog->setWindowTitle(QCoreApplication::translate("CADialog", "CA \346\250\241\346\213\237", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CADialog", "The end year of the simulation", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CADialog", "Load Config", nullptr));
        btn_chConfig->setText(QCoreApplication::translate("CADialog", "\351\200\211\346\213\251", nullptr));
        gb_filePath->setTitle(QCoreApplication::translate("CADialog", "FILE PATH", nullptr));
        btn_lu->setText(QCoreApplication::translate("CADialog", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("CADialog", "Probability", nullptr));
        btn_res->setText(QCoreApplication::translate("CADialog", "\351\200\211\346\213\251", nullptr));
        label_7->setText(QCoreApplication::translate("CADialog", "SavePath", nullptr));
        btn_sp->setText(QCoreApplication::translate("CADialog", "\351\200\211\346\213\251", nullptr));
        label->setText(QCoreApplication::translate("CADialog", "LandUse", nullptr));
        btn_prob->setText(QCoreApplication::translate("CADialog", "\351\200\211\346\213\251", nullptr));
        label_3->setText(QCoreApplication::translate("CADialog", "restrictedPath", nullptr));
        gb_simConfig->setTitle(QCoreApplication::translate("CADialog", "SIM CONFIG", nullptr));
        label_5->setText(QCoreApplication::translate("CADialog", "NeighboorhoodOdd", nullptr));
        rb_one->setText(QCoreApplication::translate("CADialog", "One Year", nullptr));
        label_6->setText(QCoreApplication::translate("CADialog", "Degree", nullptr));
        label_4->setText(QCoreApplication::translate("CADialog", "MaxIterNum", nullptr));
        rb_two->setText(QCoreApplication::translate("CADialog", "Two Years", nullptr));
        label_9->setText(QCoreApplication::translate("CADialog", "endConditionValue", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab), QCoreApplication::translate("CADialog", "LandUseDemand", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab_2), QCoreApplication::translate("CADialog", "CostMatrix", nullptr));
        tab_matrix->setTabText(tab_matrix->indexOf(tab_3), QCoreApplication::translate("CADialog", "WeightOfNeighborhood", nullptr));
        btn_saveConfig->setText(QCoreApplication::translate("CADialog", " \344\277\235\345\255\230", nullptr));
        btn_saveOther->setText(QCoreApplication::translate("CADialog", "\345\217\246\345\255\230\344\270\272", nullptr));
        btn_start->setText(QString());
        btn_stop->setText(QString());
        btn_pause->setText(QString());
        label_8->setText(QCoreApplication::translate("CADialog", "alpha", nullptr));
        cb_caType->setItemText(0, QCoreApplication::translate("CADialog", "CA", nullptr));
        cb_caType->setItemText(1, QCoreApplication::translate("CADialog", "ACA", nullptr));

        groupBox->setTitle(QCoreApplication::translate("CADialog", " \350\277\207\347\250\213\345\217\257\350\247\206\345\214\226", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CADialog", "Colors Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CADialog: public Ui_CADialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADIALOG_H
