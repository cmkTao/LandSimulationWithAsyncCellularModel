/********************************************************************************
** Form generated from reading UI file 'imagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDIALOG_H
#define UI_IMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mapwidget.h>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_ImageDialog
{
public:
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_6;
    QComboBox *cb_tifPath;
    QTreeView *treeView;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox;
    QPushButton *export_2;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QComboBox *comB_bandR;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QComboBox *comB_bandG;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QComboBox *comB_bandB;
    QWidget *tab_color;
    QGridLayout *gridLayout_2;
    QWidget *widget_7;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tabV_landColor;
    MapWidget *graphicsView;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter;
    QTableView *tableView;
    QTabWidget *tabWidget_2;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QChartView *qcharView;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_2;
    QChartView *qchartViewPercent;

    void setupUi(QDialog *ImageDialog)
    {
        if (ImageDialog->objectName().isEmpty())
            ImageDialog->setObjectName(QString::fromUtf8("ImageDialog"));
        ImageDialog->resize(1078, 739);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/\346\265\217\350\247\210.png"), QSize(), QIcon::Normal, QIcon::Off);
        ImageDialog->setWindowIcon(icon);
        horizontalLayout_4 = new QHBoxLayout(ImageDialog);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter_2 = new QSplitter(ImageDialog);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_6 = new QVBoxLayout(widget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        cb_tifPath = new QComboBox(widget);
        cb_tifPath->setObjectName(QString::fromUtf8("cb_tifPath"));

        verticalLayout_6->addWidget(cb_tifPath);

        treeView = new QTreeView(widget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        treeView->setMinimumSize(QSize(151, 0));

        verticalLayout_6->addWidget(treeView);

        widget_8 = new QWidget(widget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy1);
        widget_8->setMinimumSize(QSize(0, 30));
        widget_8->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_5 = new QHBoxLayout(widget_8);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(widget_8);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        export_2 = new QPushButton(widget_8);
        export_2->setObjectName(QString::fromUtf8("export_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(export_2->sizePolicy().hasHeightForWidth());
        export_2->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(export_2);


        verticalLayout_6->addWidget(widget_8);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setEnabled(true);
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(tab);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(0, 14));

        verticalLayout_3->addWidget(label_2);

        comB_bandR = new QComboBox(widget_4);
        comB_bandR->setObjectName(QString::fromUtf8("comB_bandR"));
        sizePolicy1.setHeightForWidth(comB_bandR->sizePolicy().hasHeightForWidth());
        comB_bandR->setSizePolicy(sizePolicy1);
        comB_bandR->setMinimumSize(QSize(100, 25));
        comB_bandR->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(comB_bandR);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_4 = new QVBoxLayout(widget_5);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(0, 14));

        verticalLayout_4->addWidget(label_3);

        comB_bandG = new QComboBox(widget_5);
        comB_bandG->setObjectName(QString::fromUtf8("comB_bandG"));
        sizePolicy1.setHeightForWidth(comB_bandG->sizePolicy().hasHeightForWidth());
        comB_bandG->setSizePolicy(sizePolicy1);
        comB_bandG->setMinimumSize(QSize(100, 25));
        comB_bandG->setMaximumSize(QSize(16777215, 25));

        verticalLayout_4->addWidget(comB_bandG);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        verticalLayout_5 = new QVBoxLayout(widget_6);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setMinimumSize(QSize(0, 14));

        verticalLayout_5->addWidget(label_4);

        comB_bandB = new QComboBox(widget_6);
        comB_bandB->setObjectName(QString::fromUtf8("comB_bandB"));
        sizePolicy1.setHeightForWidth(comB_bandB->sizePolicy().hasHeightForWidth());
        comB_bandB->setSizePolicy(sizePolicy1);
        comB_bandB->setMinimumSize(QSize(100, 25));
        comB_bandB->setMaximumSize(QSize(16777215, 25));

        verticalLayout_5->addWidget(comB_bandB);


        verticalLayout_2->addWidget(widget_6);


        verticalLayout->addWidget(widget_2);

        tabWidget->addTab(tab, QString());
        tab_color = new QWidget();
        tab_color->setObjectName(QString::fromUtf8("tab_color"));
        tab_color->setEnabled(false);
        gridLayout_2 = new QGridLayout(tab_color);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_7 = new QWidget(tab_color);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        gridLayout = new QGridLayout(widget_7);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(widget_7);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(widget_7);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget_7, 0, 0, 1, 1);

        tabV_landColor = new QTableWidget(tab_color);
        tabV_landColor->setObjectName(QString::fromUtf8("tabV_landColor"));

        gridLayout_2->addWidget(tabV_landColor, 1, 0, 1, 1);

        tabWidget->addTab(tab_color, QString());

        verticalLayout_6->addWidget(tabWidget);

        splitter_2->addWidget(widget);
        graphicsView = new MapWidget(splitter_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy4);
        graphicsView->setMinimumSize(QSize(575, 615));
        splitter_2->addWidget(graphicsView);
        widget_3 = new QWidget(splitter_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_7 = new QVBoxLayout(widget_3);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setMinimumSize(QSize(0, 150));
        tableView->setMaximumSize(QSize(16777215, 500));
        splitter->addWidget(tableView);
        tabWidget_2 = new QTabWidget(splitter);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        qcharView = new QChartView(tab_2);
        qcharView->setObjectName(QString::fromUtf8("qcharView"));

        horizontalLayout_3->addWidget(qcharView);

        tabWidget_2->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_2 = new QHBoxLayout(tab_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        qchartViewPercent = new QChartView(tab_3);
        qchartViewPercent->setObjectName(QString::fromUtf8("qchartViewPercent"));

        horizontalLayout_2->addWidget(qchartViewPercent);

        tabWidget_2->addTab(tab_3, QString());
        splitter->addWidget(tabWidget_2);

        verticalLayout_7->addWidget(splitter);

        splitter_2->addWidget(widget_3);

        horizontalLayout_4->addWidget(splitter_2);


        retranslateUi(ImageDialog);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDialog)
    {
        ImageDialog->setWindowTitle(QCoreApplication::translate("ImageDialog", "\351\242\204\350\247\210TIF\346\226\207\344\273\266", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ImageDialog", "\345\233\272\345\256\232\345\200\2741", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ImageDialog", "\351\232\217\346\234\272\345\200\274\357\274\210\345\205\254\347\224\250\357\274\211", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ImageDialog", "\351\232\217\346\234\272\345\200\274\357\274\210\344\270\215\345\220\214\357\274\211", nullptr));

        export_2->setText(QCoreApplication::translate("ImageDialog", "\345\257\274\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("ImageDialog", "Red Band", nullptr));
        label_3->setText(QCoreApplication::translate("ImageDialog", "Green Band", nullptr));
        label_4->setText(QCoreApplication::translate("ImageDialog", "Blue Band", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("ImageDialog", " R G B", nullptr));
        pushButton->setText(QCoreApplication::translate("ImageDialog", "\345\212\240\350\275\275\351\205\215\347\275\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ImageDialog", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_color), QCoreApplication::translate("ImageDialog", "landColor", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("ImageDialog", " \346\225\260\351\207\217", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("ImageDialog", " \347\231\276\345\210\206\346\257\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageDialog: public Ui_ImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDIALOG_H
