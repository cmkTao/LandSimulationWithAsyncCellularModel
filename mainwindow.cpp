#include "mainwindow.h"

#include "anndialog.h"
#include "batchcasimdialog.h"
#include "cadialog.h"
#include "cleandatadialog.h"
#include "cleanlandusedialog.h"
#include "duplicatecaconfigdialog.h"
#include "generateconfigdialog.h"
#include "genprobimagedialog.h"
#include "imagedialog.h"
#include "imagediffdialog.h"
#include "mapwidget.h"
#include "settingsdialog.h"
#include "ui_mainwindow.h"
#include "validationdialog.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connectSlots();
    this->loadAppConfig();  // 加载默认配置文件

    if (AppConfig::autoLoadConfig) {
        // 填充下拉框
        auto configNameList = MUTILS::getSubDirName(AppConfig::simConfigDir);
        foreach (auto n, configNameList) {
            ui->cb_areas->addItem(n);
        }
        DEFAULTCONFIG::useOneYear = true;
        ui->btn_cleanData->setVisible(false);
        ui->menubar->setVisible(false);
        ui->rb_one->setChecked(true);
        connect(ui->rb_one, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlot()));
        connect(ui->rb_two, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlot()));
        connect(ui->cb_areas, SIGNAL(currentIndexChanged(int)), this, SLOT(areasChoiceSlot()));
        this->loadSimulationConfig(); // 加载默认模拟配置文件
    } else {
        ui->groupBox_3->setVisible(false);
        ui->groupBox_4->setVisible(false);
    }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::radioBtnSlot() {
    qDebug() << "1";
    bool res;
    if (ui->rb_one->isChecked()) {
        DEFAULTCONFIG::useOneYear = true;
        qDebug() << "1";
    } else {
        DEFAULTCONFIG::useOneYear = false;
        qDebug() << "2";
    }
    this->loadSimulationConfig();
}

void MainWindow::openTif() {
    ImageDialog *id = new ImageDialog();
    if (!AppConfig::autoLoadConfig) {
        QString filePath;
        filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择文件..."), false, "Text File(*.tif)");
        if (filePath == "") {
            return;
        }
        id->readImage(filePath);
    }
    id->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    id->setAttribute(Qt::WA_DeleteOnClose);
    id->show();
}

void MainWindow::openDiffDialog() {
    ImageDiffDialog *id = new ImageDiffDialog();
    id->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    id->setAttribute(Qt::WA_DeleteOnClose);
    id->show();
}

void MainWindow::openANNDialog() {
    ANNDialog *ad = new ANNDialog();
    ad->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    ad->setAttribute(Qt::WA_DeleteOnClose);
    ad->show();
}

void MainWindow::openCADialog() {
    CADialog *cd = new CADialog();
    cd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::openEvalDialog() {
    ValidationDialog *vd = new ValidationDialog();
    vd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    vd->setAttribute(Qt::WA_DeleteOnClose);
    vd->show();
}

void MainWindow::openCleanDialog() {
    if (AppConfig::autoLoadConfig) {
        GenerateConfigDialog *gcd = new GenerateConfigDialog();
        gcd->setWindowFlags(Qt::Widget);
        //    cd->setModal(true);
        gcd->setAttribute(Qt::WA_DeleteOnClose);
        gcd->show();
        return;
    }
    CleanDataDialog *cd = new CleanDataDialog();
    cd->setWindowFlags(Qt::Widget);
    //    cd->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::openCleanLandDialog() {
    CleanLandUseDialog *cd = new CleanLandUseDialog();
    cd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::openGenProbImageDialog() {
    GenProbImageDialog *cd = new GenProbImageDialog();
    cd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::openBatchSimDialog() {
    BatchCASimDialog *cd = new BatchCASimDialog();
    cd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::openDuplicateConfigDialog() {
    DuplicateCaConfigDialog *cd = new DuplicateCaConfigDialog();
    cd->setWindowFlags(Qt::Widget);
    //    id->setModal(true);
    cd->setAttribute(Qt::WA_DeleteOnClose);
    cd->show();
}

void MainWindow::areasChoiceSlot()
{
    this->loadSimulationConfig();
}

void MainWindow::connectSlots() {
    connect(ui->action_openTif, &QAction::triggered, this, &MainWindow::openTif);
    connect(ui->action_cmpTif, &QAction::triggered, this, &MainWindow::openDiffDialog);
    connect(ui->actionANN, &QAction::triggered, this, &MainWindow::openANNDialog);
    connect(ui->actionCA, &QAction::triggered, this, &MainWindow::openCADialog);
    connect(ui->actionKappa_Fom, &QAction::triggered, this, &MainWindow::openEvalDialog);
    connect(ui->action_genProbImage, &QAction::triggered, this, &MainWindow::openGenProbImageDialog);
    connect(ui->actioncleanLanImage, &QAction::triggered, this, &MainWindow::openCleanLandDialog);
    connect(ui->actionBatchRunSim_Eval, &QAction::triggered, this, &MainWindow::openBatchSimDialog);
    connect(ui->actionduplicateConfig, &QAction::triggered, this, &MainWindow::openDuplicateConfigDialog);
    connect(ui->actionuseOfficalFLUSVersion, &QAction::triggered, this, [=]() {
        //        if (QMessageBox::question(this, QString::fromLocal8Bit("版本切换"),
        //                Global::useOfficialFlus ? QString::fromLocal8Bit("官方版本 -> 非官方版本")
        //                                        : QString::fromLocal8Bit("非官方版本 -> 官方版本"),
        //                QMessageBox::Yes | QMessageBox::No)
        //            == QMessageBox::No) {
        //            return;
        //        }
        //        Global::useOfficialFlus = !Global::useOfficialFlus;
        //        qDebug() << Global::useOfficialFlus;
        SettingsDialog *id = new SettingsDialog();
        id->setWindowFlags(Qt::Widget);
        //    id->setModal(true);
        id->setAttribute(Qt::WA_DeleteOnClose);
        id->show();
    });
}

void MainWindow::loadAppConfig()
{
    QString dataDir = QSettingTools::getStringValueFromIniFile(CVALUE::appConfigFilePath, "APP", "data_dir");
    QString simConfigDir = QSettingTools::getStringValueFromIniFile(CVALUE::appConfigFilePath, "APP", "sim_config_dir");
    AppConfig::useAbsoluePath = !QSettingTools::getVariantFromIniFile(CVALUE::appConfigFilePath, "APP", "use_relative_path").toBool();
    AppConfig::autoLoadConfig = QSettingTools::getVariantFromIniFile(CVALUE::appConfigFilePath, "APP", "auto_config").toBool();

    AppConfig::simConfigDir = simConfigDir == "" ? AppConfig::simConfigDir : simConfigDir;
    AppConfig::dataDir = dataDir == "" ? AppConfig::dataDir : dataDir;
    qDebug() << QString("dataDir[%1] FilePathAbsolute[%2] AUTO_LOAD_CONFIG[%3] simConfigDir[%4]")
                .arg(dataDir)
                .arg(AppConfig::useAbsoluePath)
                .arg(AppConfig::autoLoadConfig)
                .arg(simConfigDir);

}

void MainWindow::loadSimulationConfig()
{
    this->m_area = ui->cb_areas->currentText();
    QDir dir(AppConfig::simConfigDir);
    QString configName = DEFAULTCONFIG::useOneYear ? DEFAULTCONFIG::DEFAULT_NAME_CONFIG1 : DEFAULTCONFIG::DEFAULT_NAME_CONFIG2;
    QString configDirPath = QDir::toNativeSeparators(dir.absoluteFilePath(this->m_area));
    QDir configDir(configDirPath);
    this->m_defaultConfigPath = QDir::toNativeSeparators(configDir.absoluteFilePath(configName));
    qDebug() << QString("defaultConfiPath[%1] area[%2]").arg(this->m_defaultConfigPath).arg(this->m_area);

    DEFAULTCONFIG::loadDefaultConfigPath(this->m_defaultConfigPath);
}

void MainWindow::on_btn_open_clicked() { openTif(); }

void MainWindow::on_btn_ana_clicked() { openDiffDialog(); }

void MainWindow::on_btn_ANN_clicked() { openANNDialog(); }

void MainWindow::on_btn_CA_clicked() { openCADialog(); }

void MainWindow::on_btn_CA_2_clicked() { openEvalDialog(); }

void MainWindow::on_btn_cleanData_clicked() { openCleanDialog(); }

void MainWindow::enableRegion(bool flag) {
    //    ui->groupBox_2->setEnabled(flag);
    //    ui->groupBox->setEnabled(flag);
}
