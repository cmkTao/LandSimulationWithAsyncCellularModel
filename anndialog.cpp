#include "anndialog.h"

#include "ui_anndialog.h"
#include "utils/config.h"
#include "utils/constValue.h"

ANNDialog::ANNDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ANNDialog) {
    ui->setupUi(this);
    pattern1 = "(\\d*)/(\\d*) (\\d*)/(\\d*)";
    pattern2 = "(\\d*)/(\\d*)";
    rx1      = QRegExp(pattern1);
    rx2      = QRegExp(pattern2);
    ui->w_loading->setDotCount(20);
    ui->w_loading->setMaxDiameter(5);
    ui->w_loading->setMinDiameter(2);
    ui->w_loading->setVisible(false);
    m_process = NULL;
    if (AppConfig::autoLoadConfig) {
        ui->le_config->setText(DEFAULTCONFIG::annDefaultConfigPath);
        ui->groupBox_4->setVisible(false);
        ui->gb_LUD->setVisible(false);
        ui->gb_PPath->setVisible(false);
        ui->gb_DFD->setVisible(false);
        ui->btn_startSim->setEnabled(true);

        if (json2Ui(DEFAULTCONFIG::annDefaultConfigPath)) {
            ui->gb_LUD->setEnabled(true);
            ui->gb_DFD->setEnabled(true);
            ui->gb_PPath->setEnabled(true);
            ui->gb_ANNS->setEnabled(true);
            ui->btn_saveConfig->setEnabled(true);
        }
        //        ui->btn_saveConfig->click();
    }
}

ANNDialog::~ANNDialog() {
    if (m_process != NULL && m_process->state() == QProcess::Running) {
        m_process->kill();
    }
    delete ui;
}

void ANNDialog::uI2Json(QString jsonPath) {
    //根节点
    Json::Value root;

    //根节点属性
    root["ratio"]            = Json::Value(ui->dsb_SR->value());
    root["epochs"]           = Json::Value(ui->sb_Epochs->value());
    root["mode"]             = Json::Value(ui->rb_US->isChecked() ? "u" : "r");
    root["norm"]             = Json::Value(ui->cb_norm->isChecked() ? 1 : 0);
    root["weighted_loss"]    = Json::Value(ui->cb_wl->isChecked() ? 1 : 0);
    root["drive_factor_dir"] = Json::Value(ui->le_drive_factor->text().toStdString());
    root["save_path"]        = Json::Value(ui->le_probPath->text().toStdString());

    if (ui->rb_one->isChecked()) {
        root["input_file_path"] = Json::Value(ui->le_input1->text().toStdString());
    } else {
        root["input_file_path1"] = Json::Value(ui->le_input1->text().toStdString());
        root["input_file_path2"] = Json::Value(ui->le_input2->text().toStdString());
    }

    //缩进输出
    cout << "StyledWriter:" << endl;
    Json::StyledWriter sw;
    cout << sw.write(root) << endl << endl;

    //输出到文件
    ofstream os;
    os.open(jsonPath.toStdString());
    os << sw.write(root);
    os.close();
    if (!AppConfig::autoLoadConfig) {
        QMessageBox::information(nullptr, "Success!", QString::fromLocal8Bit("配置文件保存成功： %1").arg(jsonPath));
    }
    saveTifPathToConfig();
}

bool ANNDialog::json2Ui(QString jsonPath) {
    Json::Reader reader;
    Json::Value  root;
    //从文件中读取，保证当前文件有test.json文件
    ifstream in(jsonPath.toStdString(), ios::binary);
    bool     status;
    if (!in.is_open()) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1").arg(jsonPath));
        status = false;
    }
    if (reader.parse(in, root)) {
        ui->le_drive_factor->setText(MUTILS::string2Qstring(root["drive_factor_dir"].asString()));

        if (root.isMember("input_file_path")) {
            ui->le_input1->setText(MUTILS::string2Qstring(root["input_file_path"].asString()));
            ui->rb_two->setChecked(false);
        } else {
            ui->rb_two->setChecked(true);
            ui->le_input1->setText(MUTILS::string2Qstring(root["input_file_path1"].asString()));
            ui->le_input2->setText(MUTILS::string2Qstring(root["input_file_path2"].asString()));
        }

        ui->cb_norm->setChecked(root["norm"].asInt() == 1);

        if (root.isMember("weighted_loss")) {
            ui->cb_wl->setChecked(root["weighted_loss"].asInt() == 1);
        } else {
            ui->cb_wl->setChecked(false);
        }

        ui->le_probPath->setText(MUTILS::string2Qstring(root["save_path"].asString()));

        QString mode = MUTILS::string2Qstring(root["mode"].asString());
        if (mode == "u") {
            ui->rb_US->setChecked(true);
        } else {
            ui->rb_RS->setChecked(true);
        }
        ui->dsb_SR->setValue(root["ratio"].asDouble());
        ui->sb_Epochs->setValue(root["epochs"].asInt());
        status = true;

    } else {
        QMessageBox::critical(nullptr, "Error!", QString("fail to parse file %1").arg(jsonPath));
        status = false;
    }
    in.close();
    saveTifPathToConfig();
    return status;
}

void ANNDialog::saveTifPathToConfig() {
    if (AppConfig::autoLoadConfig) {
        DEFAULTCONFIG::tifPathConfig.startTifPath = ui->le_input1->text();
        DEFAULTCONFIG::tifPathConfig.probsTifPath = ui->le_probPath->text();
    }
}

void ANNDialog::on_btn_chConfig_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置文件..."), false, "Text File(*.json)");
    if (filePath == "") {
        return;
    }
    resetUI();
    ui->le_config->setText(filePath);
    if (json2Ui(filePath)) {
        ui->gb_LUD->setEnabled(true);
        ui->gb_DFD->setEnabled(true);
        ui->gb_PPath->setEnabled(true);
        ui->gb_ANNS->setEnabled(true);
        ui->btn_saveConfig->setEnabled(true);
    }
}

void ANNDialog::on_btn_chDir_clicked() {
    QString filePath;
    //    filePath = MUTILS::getFileFromDialog(this, "选择驱动力目录...", true);
    filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择驱动力目录..."), true, "");
    ;
    if (filePath == "") {
        return;
    }
    ui->le_drive_factor->setText(filePath);
}

void ANNDialog::on_pushButton_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择土地利用数据...", false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_input1->setText(filePath);
}

void ANNDialog::on_pushButton_2_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择土地利用数据...", false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_input2->setText(filePath);
}

void ANNDialog::on_btn_chProbPath_clicked() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();

    //    QString   probPath = QFileDialog::getSaveFileName(this, tr("Open File"), lastPath, tr("Text File(*.tif)"));
    //    ui->le_probPath->setText(MUTILS::getRelativeFilePath2ExeDir(probPath));

    QString probPath = MUTILS::getFileFromDialog(
        this, QString::fromLocal8Bit("选择概率文件保存路径..."), false, "Text File(*.tif)", true);
    ui->le_probPath->setText(probPath);
}

void ANNDialog::on_rb_two_toggled(bool checked) {
    ui->le_input2->setEnabled(checked);
    ui->pushButton_2->setEnabled(checked);
}

void ANNDialog::resetUI() {
    ui->le_input1->setText("");
    ui->le_input2->setText("");
    ui->rb_one->setChecked(true);
    ui->le_probPath->setText("");
    ui->dsb_SR->setValue(0.1);
    ui->sb_Epochs->setValue(35);
}

void ANNDialog::on_btn_saveConfig_clicked() {
    uI2Json(ui->le_config->text());
    ui->btn_startSim->setEnabled(true);
    //    ui->btn_stopSim->setEnabled(true);
    qDebug() << "保存ann配置文件";
    if (AppConfig::autoLoadConfig) {
        DEFAULTCONFIG::tifPathConfig.startTifPath = ui->le_input1->text();
        QMessageBox::information(
            nullptr, "Success!", QString::fromLocal8Bit("配置文件保存成功： %1").arg(ui->le_config->text()));
    }
}

void ANNDialog::on_btn_startSim_clicked() {
    ui->pgb_epochs->setMaximum(ui->sb_Epochs->value() + 1);
    ui->pgb_epochs->setValue(0);
    ui->pgb_subepochs->setValue(0);
    time.start();
    ui->te_res->clear();
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setRes2Te()));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinshed()));
    QString modeArg = ui->rb_one->isChecked() ? "ann" : "ann2";

    if (!MUTILS::useScriptWithLocalEnv) {
        // 运行打包好的python程序，exe
        QString program = MUTILS::EXEPATH;
        program.append(" -m " + modeArg);
        program.append(" -c " + ui->le_config->text());
        ui->te_res->append(program);
        ui->te_res->append(QString("Program status: %1").arg(m_process->state()));
        qDebug() << program;
        qDebug() << m_process->state();
        m_process->start(program);
    } else {
        // 运行本地的python脚本
        QString pythonExePath = MUTILS::initPythonEnv(m_process);  // 初始化环境
        // 构造执行参数
        QStringList params;
        params << MUTILS::PYTHONSCRIPTPATH << "--mode=" + modeArg << "--config=" + ui->le_config->text();
        m_process->start(pythonExePath, params);
    }

    ui->w_loading->start();
    ui->w_loading->setVisible(true);
    ui->btn_stopSim->setEnabled(true);
    ui->btn_startSim->setEnabled(false);
}

void ANNDialog::setRes2Te() {
    QByteArray qbt = m_process->readAllStandardOutput();
    QString    msg = QString::fromLocal8Bit(qbt);
    QString    str = msg.simplified();
    int        pos = str.indexOf(rx1);
    if (pos >= 0) {
        curr_epochs = rx1.cap(1).toInt();
        all_epochs  = rx1.cap(2).toInt();
        curr_batch  = rx1.cap(3).toInt();
        all_batch   = rx1.cap(4).toInt();
    } else {
        pos = str.indexOf(rx2);
        if (pos >= 0) {
            curr_batch = rx2.cap(1).toInt();
            all_batch  = rx2.cap(2).toInt();
        }
    }
    if (pos >= 0) {
        // 这里+1是因为多了一步分析功能
        //        ui->pgb_epochs->setValue((curr_epochs * 1.0) / (all_epochs + 1) * 100);
        ui->pgb_epochs->setValue(curr_epochs);
        ui->pgb_subepochs->setValue((curr_batch * 1.0) / all_batch * 100);
    }
    ui->te_res->append(msg);
    ui->te_res->update();
}

void ANNDialog::on_btn_stopSim_clicked() {
    m_process->kill();
    ui->te_res->append(QString::fromLocal8Bit("运行提前终止!!!"));
    ui->w_loading->stop();
    ui->w_loading->setVisible(false);
    ui->btn_startSim->setEnabled(true);
    ui->btn_stopSim->setEnabled(false);
    ui->te_res->append(QString::fromLocal8Bit("用时：%1").arg(time.elapsed() / 1000.0));
}

void ANNDialog::slotProcessFinshed() {
    ui->pgb_epochs->setValue(ui->sb_Epochs->value() + 1);
    ui->w_loading->stop();
    ui->w_loading->setVisible(false);
    ui->btn_startSim->setEnabled(true);
    ui->btn_stopSim->setEnabled(false);
    ui->te_res->append(QString::fromLocal8Bit("用时：%1 s").arg(time.elapsed() / 1000.0));
    if (AppConfig::autoLoadConfig) {
        DEFAULTCONFIG::tifPathConfig.probsTifPath = ui->le_probPath->text();
    }
}
