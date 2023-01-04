/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_openTif;
    QAction *action_cmpTif;
    QAction *actionANN;
    QAction *actionCA;
    QAction *actionKappa_Fom;
    QAction *action_genProbImage;
    QAction *actioncleanLanImage;
    QAction *actionBatchRunSim_Eval;
    QAction *actionduplicateConfig;
    QAction *actionuseOfficalFLUSVersion;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QRadioButton *rb_one;
    QRadioButton *rb_two;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_open;
    QPushButton *btn_ana;
    QPushButton *btn_CA_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *btn_cleanData;
    QPushButton *btn_ANN;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_CA;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QComboBox *cb_areas;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(584, 434);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/\345\234\260\347\220\203.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        action_openTif = new QAction(MainWindow);
        action_openTif->setObjectName(QString::fromUtf8("action_openTif"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_openTif->setIcon(icon1);
        action_cmpTif = new QAction(MainWindow);
        action_cmpTif->setObjectName(QString::fromUtf8("action_cmpTif"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/\347\273\223\346\236\234\345\257\271\346\257\224\345\210\206\346\236\220.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_cmpTif->setIcon(icon2);
        actionANN = new QAction(MainWindow);
        actionANN->setObjectName(QString::fromUtf8("actionANN"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/ann.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionANN->setIcon(icon3);
        actionCA = new QAction(MainWindow);
        actionCA->setObjectName(QString::fromUtf8("actionCA"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/ca.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCA->setIcon(icon4);
        actionKappa_Fom = new QAction(MainWindow);
        actionKappa_Fom->setObjectName(QString::fromUtf8("actionKappa_Fom"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/\351\252\214\350\257\201\347\240\201.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionKappa_Fom->setIcon(icon5);
        action_genProbImage = new QAction(MainWindow);
        action_genProbImage->setObjectName(QString::fromUtf8("action_genProbImage"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/genProb.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_genProbImage->setIcon(icon6);
        actioncleanLanImage = new QAction(MainWindow);
        actioncleanLanImage->setObjectName(QString::fromUtf8("actioncleanLanImage"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/clean.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncleanLanImage->setIcon(icon7);
        actionBatchRunSim_Eval = new QAction(MainWindow);
        actionBatchRunSim_Eval->setObjectName(QString::fromUtf8("actionBatchRunSim_Eval"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/img/batch.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBatchRunSim_Eval->setIcon(icon8);
        actionduplicateConfig = new QAction(MainWindow);
        actionduplicateConfig->setObjectName(QString::fromUtf8("actionduplicateConfig"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/img/duplicate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionduplicateConfig->setIcon(icon9);
        actionuseOfficalFLUSVersion = new QAction(MainWindow);
        actionuseOfficalFLUSVersion->setObjectName(QString::fromUtf8("actionuseOfficalFLUSVersion"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/img/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionuseOfficalFLUSVersion->setIcon(icon10);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setMinimumSize(QSize(0, 60));
        groupBox_3->setMaximumSize(QSize(16777215, 60));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        rb_one = new QRadioButton(groupBox_3);
        rb_one->setObjectName(QString::fromUtf8("rb_one"));

        gridLayout_4->addWidget(rb_one, 0, 0, 1, 1);

        rb_two = new QRadioButton(groupBox_3);
        rb_two->setObjectName(QString::fromUtf8("rb_two"));

        gridLayout_4->addWidget(rb_two, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(80, 80, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 4, 1, 1);

        btn_open = new QPushButton(groupBox);
        btn_open->setObjectName(QString::fromUtf8("btn_open"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_open->sizePolicy().hasHeightForWidth());
        btn_open->setSizePolicy(sizePolicy1);
        btn_open->setMinimumSize(QSize(80, 80));
        btn_open->setMaximumSize(QSize(80, 80));
        btn_open->setFocusPolicy(Qt::StrongFocus);
        btn_open->setAutoFillBackground(true);
        btn_open->setStyleSheet(QString::fromUtf8(""));
        btn_open->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        btn_open->setIcon(icon1);
        btn_open->setIconSize(QSize(64, 64));

        gridLayout_2->addWidget(btn_open, 0, 0, 1, 1);

        btn_ana = new QPushButton(groupBox);
        btn_ana->setObjectName(QString::fromUtf8("btn_ana"));
        sizePolicy1.setHeightForWidth(btn_ana->sizePolicy().hasHeightForWidth());
        btn_ana->setSizePolicy(sizePolicy1);
        btn_ana->setMinimumSize(QSize(80, 80));
        btn_ana->setMaximumSize(QSize(80, 80));
        btn_ana->setIcon(icon2);
        btn_ana->setIconSize(QSize(64, 64));

        gridLayout_2->addWidget(btn_ana, 0, 1, 1, 1);

        btn_CA_2 = new QPushButton(groupBox);
        btn_CA_2->setObjectName(QString::fromUtf8("btn_CA_2"));
        sizePolicy1.setHeightForWidth(btn_CA_2->sizePolicy().hasHeightForWidth());
        btn_CA_2->setSizePolicy(sizePolicy1);
        btn_CA_2->setMinimumSize(QSize(80, 80));
        btn_CA_2->setMaximumSize(QSize(80, 80));
        btn_CA_2->setIcon(icon5);
        btn_CA_2->setIconSize(QSize(64, 64));

        gridLayout_2->addWidget(btn_CA_2, 0, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn_cleanData = new QPushButton(groupBox_2);
        btn_cleanData->setObjectName(QString::fromUtf8("btn_cleanData"));
        sizePolicy1.setHeightForWidth(btn_cleanData->sizePolicy().hasHeightForWidth());
        btn_cleanData->setSizePolicy(sizePolicy1);
        btn_cleanData->setMinimumSize(QSize(80, 80));
        btn_cleanData->setMaximumSize(QSize(80, 80));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/img/\346\270\205\346\264\227\350\256\260\345\275\225.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_cleanData->setIcon(icon11);
        btn_cleanData->setIconSize(QSize(64, 64));
        btn_cleanData->setAutoDefault(false);
        btn_cleanData->setFlat(false);

        gridLayout->addWidget(btn_cleanData, 0, 2, 1, 1);

        btn_ANN = new QPushButton(groupBox_2);
        btn_ANN->setObjectName(QString::fromUtf8("btn_ANN"));
        sizePolicy1.setHeightForWidth(btn_ANN->sizePolicy().hasHeightForWidth());
        btn_ANN->setSizePolicy(sizePolicy1);
        btn_ANN->setMinimumSize(QSize(80, 80));
        btn_ANN->setMaximumSize(QSize(80, 80));
        btn_ANN->setIcon(icon3);
        btn_ANN->setIconSize(QSize(64, 64));

        gridLayout->addWidget(btn_ANN, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(80, 80, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        btn_CA = new QPushButton(groupBox_2);
        btn_CA->setObjectName(QString::fromUtf8("btn_CA"));
        sizePolicy1.setHeightForWidth(btn_CA->sizePolicy().hasHeightForWidth());
        btn_CA->setSizePolicy(sizePolicy1);
        btn_CA->setMinimumSize(QSize(80, 80));
        btn_CA->setMaximumSize(QSize(80, 80));
        btn_CA->setIcon(icon4);
        btn_CA->setIconSize(QSize(64, 64));
        btn_CA->setAutoDefault(false);
        btn_CA->setFlat(false);

        gridLayout->addWidget(btn_CA, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(0, 80));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        cb_areas = new QComboBox(groupBox_4);
        cb_areas->setObjectName(QString::fromUtf8("cb_areas"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cb_areas->sizePolicy().hasHeightForWidth());
        cb_areas->setSizePolicy(sizePolicy2);
        cb_areas->setMinimumSize(QSize(0, 20));

        gridLayout_5->addWidget(cb_areas, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 584, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        menu->addAction(action_openTif);
        menu->addAction(action_cmpTif);
        menu_2->addAction(actionANN);
        menu_2->addAction(actionCA);
        menu_3->addAction(actionKappa_Fom);
        menu_4->addAction(action_genProbImage);
        menu_4->addAction(actioncleanLanImage);
        menu_4->addAction(actionBatchRunSim_Eval);
        menu_4->addAction(actionduplicateConfig);
        menu_4->addAction(actionuseOfficalFLUSVersion);

        retranslateUi(MainWindow);

        btn_cleanData->setDefault(true);
        btn_CA->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\234\237\345\234\260\346\250\241\346\213\237\345\267\245\345\205\267", nullptr));
        action_openTif->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200tif\346\226\207\344\273\266", nullptr));
        action_cmpTif->setText(QCoreApplication::translate("MainWindow", "\345\257\271\346\257\224tif\346\226\207\344\273\266", nullptr));
        actionANN->setText(QCoreApplication::translate("MainWindow", "ANN", nullptr));
        actionCA->setText(QCoreApplication::translate("MainWindow", "CA", nullptr));
        actionKappa_Fom->setText(QCoreApplication::translate("MainWindow", "Kappa & Fom", nullptr));
        action_genProbImage->setText(QCoreApplication::translate("MainWindow", "genProbsImage", nullptr));
        actioncleanLanImage->setText(QCoreApplication::translate("MainWindow", "cleanLanImage", nullptr));
        actionBatchRunSim_Eval->setText(QCoreApplication::translate("MainWindow", "BatchRunSim/Eval", nullptr));
        actionduplicateConfig->setText(QCoreApplication::translate("MainWindow", "duplicateConfig", nullptr));
        actionuseOfficalFLUSVersion->setText(QCoreApplication::translate("MainWindow", "settings", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "One/Two years for training", nullptr));
        rb_one->setText(QCoreApplication::translate("MainWindow", "One year", nullptr));
        rb_two->setText(QCoreApplication::translate("MainWindow", "Two years", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Tools", nullptr));
#if QT_CONFIG(tooltip)
        btn_open->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200TIF\345\233\276\345\203\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_open->setText(QString());
#if QT_CONFIG(tooltip)
        btn_ana->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\271\346\257\224\344\270\244\345\274\240TIF\346\226\207\344\273\266\347\232\204\344\270\215\345\220\214\347\202\271", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_ana->setText(QString());
#if QT_CONFIG(tooltip)
        btn_CA_2->setToolTip(QCoreApplication::translate("MainWindow", "\351\252\214\350\257\201\346\250\241\346\213\237\347\273\223\346\236\234", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_CA_2->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "ANN-CA", nullptr));
#if QT_CONFIG(tooltip)
        btn_cleanData->setToolTip(QCoreApplication::translate("MainWindow", "\346\270\205\346\264\227\346\225\260\346\215\256", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_cleanData->setText(QString());
#if QT_CONFIG(tooltip)
        btn_ANN->setToolTip(QCoreApplication::translate("MainWindow", "\347\245\236\347\273\217\347\275\221\347\273\234\350\256\241\347\256\227\351\200\202\345\272\224\346\200\247\346\246\202\347\216\207", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_ANN->setText(QString());
#if QT_CONFIG(tooltip)
        btn_CA->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\203\347\273\206\350\203\236\350\207\252\345\212\250\346\234\272\350\277\233\350\241\214\346\250\241\346\213\237", nullptr));
#endif // QT_CONFIG(tooltip)
        btn_CA->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Simulation Areas", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\236\213", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\351\252\214\350\257\201", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
