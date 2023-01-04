/********************************************************************************
** Form generated from reading UI file 'imagediffdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDIFFDIALOG_H
#define UI_IMAGEDIFFDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mapwidget.h>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_ImageDiffDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QComboBox *cb_config;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *le_img1;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_img1;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *le_img2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn_img2;
    QPushButton *btn_confirm;
    QWidget *widget_5;
    QGridLayout *gridLayout_3;
    QRadioButton *rb_vR;
    QRadioButton *rb_hR;
    QCheckBox *cb_legal;
    QComboBox *cb_landCode;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tw_color;
    MapWidget *gv_map;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QTableWidget *tw_transMatrix;
    QChartView *qchart_trans;

    void setupUi(QDialog *ImageDiffDialog)
    {
        if (ImageDiffDialog->objectName().isEmpty())
            ImageDiffDialog->setObjectName(QString::fromUtf8("ImageDiffDialog"));
        ImageDiffDialog->resize(1058, 840);
        ImageDiffDialog->setMinimumSize(QSize(0, 300));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/\345\210\206\346\236\220.png"), QSize(), QIcon::Normal, QIcon::Off);
        ImageDiffDialog->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(ImageDiffDialog);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        splitter_3 = new QSplitter(ImageDiffDialog);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cb_config = new QComboBox(widget);
        cb_config->setObjectName(QString::fromUtf8("cb_config"));

        verticalLayout_2->addWidget(cb_config);

        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 171));
        groupBox->setMaximumSize(QSize(16777215, 230));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMinimumSize(QSize(0, 100));
        widget_2->setMaximumSize(QSize(16777215, 100));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        le_img1 = new QLineEdit(widget_2);
        le_img1->setObjectName(QString::fromUtf8("le_img1"));

        gridLayout->addWidget(le_img1, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 1);

        btn_img1 = new QPushButton(widget_2);
        btn_img1->setObjectName(QString::fromUtf8("btn_img1"));

        gridLayout->addWidget(btn_img1, 0, 4, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        le_img2 = new QLineEdit(widget_2);
        le_img2->setObjectName(QString::fromUtf8("le_img2"));

        gridLayout->addWidget(le_img2, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        btn_img2 = new QPushButton(widget_2);
        btn_img2->setObjectName(QString::fromUtf8("btn_img2"));

        gridLayout->addWidget(btn_img2, 1, 4, 1, 1);


        verticalLayout->addWidget(widget_2);

        btn_confirm = new QPushButton(groupBox);
        btn_confirm->setObjectName(QString::fromUtf8("btn_confirm"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btn_confirm->sizePolicy().hasHeightForWidth());
        btn_confirm->setSizePolicy(sizePolicy2);
        btn_confirm->setMinimumSize(QSize(0, 30));
        btn_confirm->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(btn_confirm);

        widget_5 = new QWidget(groupBox);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setEnabled(true);
        gridLayout_3 = new QGridLayout(widget_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        rb_vR = new QRadioButton(widget_5);
        rb_vR->setObjectName(QString::fromUtf8("rb_vR"));
        rb_vR->setChecked(true);

        gridLayout_3->addWidget(rb_vR, 0, 1, 1, 1);

        rb_hR = new QRadioButton(widget_5);
        rb_hR->setObjectName(QString::fromUtf8("rb_hR"));
        rb_hR->setChecked(false);

        gridLayout_3->addWidget(rb_hR, 0, 2, 1, 1);

        cb_legal = new QCheckBox(widget_5);
        cb_legal->setObjectName(QString::fromUtf8("cb_legal"));

        gridLayout_3->addWidget(cb_legal, 1, 1, 1, 1);


        verticalLayout->addWidget(widget_5);

        splitter->addWidget(groupBox);
        cb_landCode = new QComboBox(splitter);
        cb_landCode->setObjectName(QString::fromUtf8("cb_landCode"));
        cb_landCode->setMinimumSize(QSize(0, 31));
        cb_landCode->setMaximumSize(QSize(16777215, 32));
        QFont font;
        font.setPointSize(12);
        cb_landCode->setFont(font);
        splitter->addWidget(cb_landCode);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_4 = new QWidget(groupBox_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(widget_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 0, 1, 1, 1);


        verticalLayout_4->addWidget(widget_4);

        tw_color = new QTableWidget(groupBox_2);
        tw_color->setObjectName(QString::fromUtf8("tw_color"));

        verticalLayout_4->addWidget(tw_color);

        splitter->addWidget(groupBox_2);

        verticalLayout_2->addWidget(splitter);

        splitter_3->addWidget(widget);
        gv_map = new MapWidget(splitter_3);
        gv_map->setObjectName(QString::fromUtf8("gv_map"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(gv_map->sizePolicy().hasHeightForWidth());
        gv_map->setSizePolicy(sizePolicy3);
        gv_map->setMinimumSize(QSize(500, 0));
        splitter_3->addWidget(gv_map);
        widget_3 = new QWidget(splitter_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(widget_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        tw_transMatrix = new QTableWidget(splitter_2);
        tw_transMatrix->setObjectName(QString::fromUtf8("tw_transMatrix"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tw_transMatrix->sizePolicy().hasHeightForWidth());
        tw_transMatrix->setSizePolicy(sizePolicy4);
        splitter_2->addWidget(tw_transMatrix);
        qchart_trans = new QChartView(splitter_2);
        qchart_trans->setObjectName(QString::fromUtf8("qchart_trans"));
        sizePolicy4.setHeightForWidth(qchart_trans->sizePolicy().hasHeightForWidth());
        qchart_trans->setSizePolicy(sizePolicy4);
        qchart_trans->setMinimumSize(QSize(0, 550));
        splitter_2->addWidget(qchart_trans);

        verticalLayout_3->addWidget(splitter_2);

        splitter_3->addWidget(widget_3);

        horizontalLayout_2->addWidget(splitter_3);


        retranslateUi(ImageDiffDialog);

        QMetaObject::connectSlotsByName(ImageDiffDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDiffDialog)
    {
        ImageDiffDialog->setWindowTitle(QCoreApplication::translate("ImageDiffDialog", "\345\257\271\346\257\224\345\234\237\345\234\260\345\210\251\347\224\250\346\225\260\346\215\256", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ImageDiffDialog", "File", nullptr));
        label->setText(QCoreApplication::translate("ImageDiffDialog", "Image1", nullptr));
        btn_img1->setText(QCoreApplication::translate("ImageDiffDialog", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("ImageDiffDialog", "Image2", nullptr));
        btn_img2->setText(QCoreApplication::translate("ImageDiffDialog", "\351\200\211\346\213\251", nullptr));
        btn_confirm->setText(QCoreApplication::translate("ImageDiffDialog", "\347\241\256\350\256\244", nullptr));
        rb_vR->setText(QCoreApplication::translate("ImageDiffDialog", "\346\230\276\347\244\272\346\225\260\345\255\227", nullptr));
        rb_hR->setText(QCoreApplication::translate("ImageDiffDialog", "\346\230\276\347\244\272\346\257\224\344\276\213", nullptr));
        cb_legal->setText(QCoreApplication::translate("ImageDiffDialog", "\345\220\210\346\263\225\346\200\247\344\270\200\350\207\264", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ImageDiffDialog", "Colors", nullptr));
        pushButton->setText(QCoreApplication::translate("ImageDiffDialog", "\344\277\235\345\255\230\351\205\215\347\275\256", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ImageDiffDialog", "\345\212\240\350\275\275\351\205\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageDiffDialog: public Ui_ImageDiffDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDIFFDIALOG_H
