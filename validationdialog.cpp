#include "validationdialog.h"

#include "ui_validationdialog.h"

ValidationDialog::ValidationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ValidationDialog) {
    ui->setupUi(this);
    pattern = "(\\d*)/(\\d*)";
    rx      = QRegExp(pattern);
    ui->w_loading->setDotCount(20);
    ui->w_loading->setMaxDiameter(5);
    ui->w_loading->setMinDiameter(2);
    ui->w_loading->setVisible(false);

    m_vt = new ValidationThread(this);
    connect(m_vt, SIGNAL(isDone(QList<QList<double>>)), this, SLOT(slotEvalProcessFinshed(QList<QList<double>>)));

    if (AppConfig::autoLoadConfig) {
        ui->btn_config->click();
        ui->widget_2->setVisible(false);
        ui->btn_cal->setEnabled(true);
    }
}

ValidationDialog::~ValidationDialog() { delete ui; }

void ValidationDialog::uI2Json(QString jsonPath) {
    //根节点
    Json::Value root;

    root["sim_path"]   = Json::Value(ui->le_simPath->text().toStdString());
    root["true_path"]  = Json::Value(ui->le_truePath->text().toStdString());
    root["start_path"] = Json::Value(ui->le_startPath->text().toStdString());

    //缩进输出
    cout << "StyledWriter:" << endl;
    Json::StyledWriter sw;
    cout << sw.write(root) << endl << endl;

    //输出到文件
    ofstream os;
    os.open(jsonPath.toStdString());
    os << sw.write(root);
    os.close();

    QMessageBox::information(nullptr, "Success!", QString::fromLocal8Bit("配置文件保存成功： %1").arg(jsonPath));
}

bool ValidationDialog::json2Ui(QString jsonPath) {
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
        ui->le_simPath->setText(MUTILS::string2Qstring(root["sim_path"].asString()));
        ui->le_truePath->setText(MUTILS::string2Qstring(root["true_path"].asString()));
        ui->le_startPath->setText(MUTILS::string2Qstring(root["start_path"].asString()));
        status = true;

    } else {
        QMessageBox::critical(nullptr, "Error!", QString("fail to parse file %1").arg(jsonPath));
        status = false;
    }
    in.close();
    return status;
}

void ValidationDialog::slotEvalProcessFinshed(QList<QList<double>> valRes) {
    ui->w_loading->stop();
    ui->w_loading->setVisible(false);
    ui->btn_cal->setEnabled(true);
    for (int i = 0; i < valRes.size() - 1; i++) {
        ui->te_res->append(QString::fromLocal8Bit("===\n第%1轮：OA=%2, Kappa=%3, Fom=%4")
                               .arg(i + 1)
                               .arg(valRes[i][0])
                               .arg(valRes[i][1])
                               .arg(valRes[i][2]));
    }
    int index = valRes.size() - 1;
    ui->te_res->append(QString::fromLocal8Bit("===\nMean： OA=%2, Kappa=%3, Fom=%4")
                           .arg(valRes[index][0])
                           .arg(valRes[index][1])
                           .arg(valRes[index][2]));
}

void ValidationDialog::on_btn_config_clicked() {
    QString filePath;
    if (!AppConfig::autoLoadConfig) {
        filePath = MUTILS::getFileFromDialog(this, "选择配置文件...", false, "Text File(*.json)");
        if (filePath == "") {
            return;
        }
    } else {
        filePath = DEFAULTCONFIG::evalDefaultConfigPath;
    }
    ui->le_configPath->setText(filePath);
    resetUI();
    if (json2Ui(filePath)) {
        ui->btn_saveConfig->setEnabled(true);
    }
}

void ValidationDialog::resetUI() {
    ui->le_simPath->setText("");
    ui->le_truePath->setText("");
    ui->le_startPath->setText("");
    ui->btn_cal->setEnabled(false);
}

void ValidationDialog::on_btn_simPath_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(
        this, QString::fromLocal8Bit("选择模拟文件..."), false, "Text File(*.tif)", false, true);
    if (filePath == "") {
        return;
    }
    ui->le_simPath->setText(filePath);
}

void ValidationDialog::on_btn_truePath_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择真实年份..."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_truePath->setText(filePath);
}

void ValidationDialog::on_btn_startPath_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择起始年份..."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_startPath->setText(filePath);
}

void ValidationDialog::on_btn_saveConfig_clicked() {
    QString filePath = ui->le_configPath->text();
    if (filePath == "") {
        QMessageBox::information(nullptr, "TIPS!", QString::fromLocal8Bit("请选择需要保存的配置文件"));
    } else {
        uI2Json(filePath);
        ui->btn_cal->setEnabled(true);
    }
}

void ValidationDialog::on_btn_saveOther_clicked() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    QString   filePath = QFileDialog::getSaveFileName(this, tr("Open File"), lastPath, tr("Text File(*.json)"));
    if (filePath == "") {
        return;
    }
    uI2Json(filePath);
    ui->le_configPath->setText(filePath);
    ui->btn_cal->setEnabled(true);
}

void ValidationDialog::on_btn_cal_clicked() {
    ui->pgb_process->setValue(0);
    ui->te_res->clear();
    bool useCPlus = true;
    if (useCPlus) {
        m_vt->setEvalConfigPath(ui->le_configPath->text());
        m_vt->start();
    } else {
        m_process = new QProcess(this);
        m_process->setProcessChannelMode(QProcess::MergedChannels);
        m_process->setReadChannel(QProcess::StandardOutput);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setRes2Te()));
        connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinshed()));
        QString program = MUTILS::EXEPATH;
        QString modeArg = "eval";
        if (!MUTILS::useScriptWithLocalEnv) {
            // 运行打包好的python程序，exe
            program.append(" -m " + modeArg);
            program.append(" -c " + ui->le_configPath->text());
            ui->te_res->append(program);
            qDebug() << program;
            m_process->start(program);
        } else {
            // 运行本地的python脚本
            QString pythonExePath = MUTILS::initPythonEnv(m_process);  // 初始化环境
            // 构造执行参数
            QStringList params;
            params << MUTILS::PYTHONSCRIPTPATH << "--mode=" + modeArg << "--config=" + ui->le_configPath->text();
            m_process->start(pythonExePath, params);
        }
    }

    ui->w_loading->start();
    ui->w_loading->setVisible(true);
    ui->btn_cal->setEnabled(false);
}

void ValidationDialog::setRes2Te() {
    QByteArray qbt = m_process->readAllStandardOutput();
    QString    msg = QString::fromLocal8Bit(qbt);
    QString    str = msg.simplified();
    int        pos = str.indexOf(rx);
    if (pos >= 0) {
        ui->pgb_process->setValue((rx.cap(1).toInt() * 1.0) / rx.cap(2).toInt() * 100);
    }
    ui->te_res->append(msg);
    ui->te_res->update();
}

void ValidationDialog::slotProcessFinshed() {
    ui->w_loading->stop();
    ui->w_loading->setVisible(false);
    ui->btn_cal->setEnabled(true);
}
