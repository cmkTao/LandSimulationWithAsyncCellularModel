#include "batchcasimdialog.h"

#include "ui_batchcasimdialog.h"

BatchCASimDialog::BatchCASimDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BatchCASimDialog) {
    ui->setupUi(this);

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    m_pool.setMaxThreadCount(sysInfo.dwNumberOfProcessors / 2);
    ui->sb_threadNum->setValue(sysInfo.dwNumberOfProcessors / 4);
    ui->sb_threadNum->setMaximum(sysInfo.dwNumberOfProcessors);
    m_summaryLogName = "summary.ini";
    QString pattern  = "(\\d*)/(\\d*)";
    rx               = QRegExp(pattern);

    ui->w_loading->setDotCount(15);
    ui->w_loading->setMaxDiameter(3);
    ui->w_loading->setMinDiameter(1);
    ui->w_loading->setVisible(false);

    QStringList headers(
        {"Config Path", "RepeatNum", "CurEpoch", "Status", "MeanIterTime", "kappa", "fom", "oa", "name", "progress"});
    //  ui->tw_configs->setRowCount(2);
    ui->tw_configs->setColumnCount(headers.size());
    ui->tw_configs->setHorizontalHeaderLabels(headers);
    ui->tw_configs->verticalHeader()->setVisible(false);
    //    ui->tw_configs->horizontalHeader()->resizeSection(0,284);
    for (int i = 1; i < headers.length(); i++) {
        ui->tw_configs->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

    ui->tw_configs->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_simThread = NULL;
    m_valThread = NULL;

    // 运行python的QProcess
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setRes2Te()));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotEvalProcessFinshed()));
    ui->widget_14->setVisible(false);
    connect(ui->rb_batchChangeParam, &QRadioButton::toggled, this, [=]() {
        if (ui->rb_batchChangeParam->isChecked()) {
            ui->widget_14->setVisible(true);
        } else {
            ui->widget_14->setVisible(false);
        }
    });
}

BatchCASimDialog::~BatchCASimDialog() {
    //    m_simThread->setStopFlag(true);
    //    if (m_process->state() == QProcess::Running) m_process->terminate();
    m_pool.waitForDone(10);
    delete ui;
}

void BatchCASimDialog::addOneConfigToTW(CBatchCaSimConfig *cb) {
    int row                                = ui->tw_configs->rowCount();
    m_rowNumPathMap[cb->getCaConfigPath()] = row;
    ui->tw_configs->setRowCount(row + 1);  // 新增一行
    ui->tw_configs->setItem(row, 0, genTWI(cb->getCaConfigPath()));
    ui->tw_configs->setItem(row, 1, genTWI(ui->sb_runTimes->value()));
    ui->tw_configs->setItem(row, 2, genTWI(0));
    ui->tw_configs->setItem(row, 3, genTWI(m_status.waiting));
    ui->tw_configs->setItem(row, 4, genTWI(cb->getMeanEndIterTimes()));
    ui->tw_configs->setItem(row, 5, genTWI(cb->m_meanValRes.kappa));
    ui->tw_configs->setItem(row, 6, genTWI(cb->m_meanValRes.fom));
    ui->tw_configs->setItem(row, 7, genTWI(cb->m_meanValRes.oa));
    ui->tw_configs->setItem(row, 8, genTWI(cb->getCurName()));
}

void BatchCASimDialog::createThread(CBatchCaSimConfig *cb) {
    if (m_simThread != NULL) {
        delete m_simThread;
        m_simThread = NULL;
    }
    if (cb->getCaMode() == "ACA") {
        m_simThread = new ACA(0, "", cb->getCaRatio());
        qDebug() << "ACA";
    } else if (cb->getCaMode() == "CA") {
        m_simThread = new CA(0, "");
    } else {
        qDebug() << "CA";
        QMessageBox::warning(this, QString::fromLocal8Bit("运行提示"),
            ui->rb_sim->isChecked() ? QString::fromLocal8Bit("模式不正确非ACA、CA=%1").arg(cb->getCaMode())
                                    : QString::fromLocal8Bit("验证"));
    }
    // 连接线程和UI的通信机制
    connect(m_simThread, SIGNAL(isDone()), this, SLOT(slotProcessFinshed()));
    connect(m_simThread, SIGNAL(signalSendMessage(QString)), this, SLOT(setMSGFromThread2UI(QString)));
    connect(m_simThread, SIGNAL(signalSendProcess(int)), this, SLOT(setProcess2Bar(int)));
    connect(m_simThread, SIGNAL(signalSendLandCounts(int *, int)), this, SLOT(slotSetLandCounts(int *, int)));
}

void BatchCASimDialog::on_pb_targetPath_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择目标年份真实数据"), false, "Text File(*.tif)");
    if (filePath == "") return;
    ui->le_targetPath->setText(filePath);
    m_endYearTifPath = filePath;
}

void BatchCASimDialog::on_pb_logPath_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择保存位置..."), false, "Text File(*.ini)", true);
    if (filePath == "") return;
    ui->le_logPath->setText(filePath);
    m_summaryLogPath = filePath;
}

void BatchCASimDialog::on_pb_runDir_clicked() {
    QString filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置所在目录..."), true);
    if (filePath == "") return;
    ui->le_runDir->setText(filePath);
    m_batchSimDir = filePath;
    QDir dir(m_batchSimDir);
    if (!ui->cb_newRepeatNum->isChecked()) getEpochFromlogIniFile(dir.absoluteFilePath(m_summaryLogName));
    m_batchSimDirName = dir.dirName();
    dir.setFilter(QDir::Dirs);  // 只要目录
    QFileInfoList list = dir.entryInfoList();
    reset();
    for (QFileInfo fi : list) {
        CBatchCaSimConfig *cb = new CBatchCaSimConfig(fi.filePath(), ui->sb_runTimes->value());
        // 合法判断 + 去重
        if (cb->isValid() && !m_configMap.contains(cb->getCaConfigPath())) {
            m_configMap[cb->getCaConfigPath()] = cb;
            initCBBySumLogFile(cb);
            addOneConfigToTW(cb);  // 添加到表格
        }
    }
    initTable();
    if (ui->cb_toExcel->isChecked()) {
        ui->btn_start->setEnabled(false);
        ui->w_loading->start();
        ui->w_loading->setVisible(true);
        MUTILS::table2ExcelByHtml(ui->tw_configs, "Validation", dir.absoluteFilePath("validation.xlsx"));
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        ui->btn_start->setEnabled(true);
    }
}

QTableWidgetItem *BatchCASimDialog::genTWI(QString content) {
    QTableWidgetItem *_tmp1 = new QTableWidgetItem(content);
    _tmp1->setTextAlignment(Qt::AlignCenter);
    //    _tmp1->setTextAlignment(Qt::AlignRight);
    //    _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));  // <不可编辑>.
    return _tmp1;
}

QTableWidgetItem *BatchCASimDialog::genTWI(int content) { return genTWI(QString::number(content)); }

QTableWidgetItem *BatchCASimDialog::genTWI(double content) { return genTWI(QString::number(content)); }
QTableWidgetItem *BatchCASimDialog::genTWI(float content) { return genTWI(QString::number(content)); }

void BatchCASimDialog::startASimulation() {
    ui->pb_overall->setValue(m_curConfigNum);
    QString key = ui->tw_configs->item(m_curConfigNum, 0)->text();
    ui->tw_configs->item(m_curConfigNum, 3)->setText(m_status.running);
    CBatchCaSimConfig *cb = m_configMap[key];

    ui->pb_curConfig->setMaximum(cb->getEpoches());
    ui->pb_curConfig->setValue(m_curRepeatEpoch);

    ui->tw_configs->item(m_curConfigNum, 2)->setText(QString::number(m_curRepeatEpoch + 1));
    ui->pb_curConfig->setValue(m_curRepeatEpoch);
    ui->pb_curSim->setMaximum(cb->getIterTimes());
    createThread(cb);
    // 设置新的保存路径
    cb->setSimSavePath2Config(m_curRepeatEpoch + 1);
    m_simThread->setConfigPath(cb->getCaConfigPath());
    m_simThread->start();
}

void BatchCASimDialog::startEvalSimulation() {
    ui->pb_overall->setValue(m_curConfigNum);
    QString key = ui->tw_configs->item(m_curConfigNum, 0)->text();
    evalSimResult(m_configMap[key], true);
}

void BatchCASimDialog::saveLogs() {
    QString content = ui->te_res->toPlainText().trimmed();
    QDir    logDir  = getOrCreateLogsDir();
    QFile   file(logDir.absoluteFilePath(QString("%1.log").arg(m_curRepeatEpoch + 1)));
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);  //分行写入文件
        out << ui->te_res->toPlainText();
    }

    // 保存土地数量的发展
    Json::Value root;
    int         epochs = m_landCountInProcess.length();
    qDebug() << _msize(m_landCountInProcess.at(0)) / sizeof(int) << epochs;
    for (int i = 0; i < epochs; i++) {
        int nTypes = _msize(m_landCountInProcess.at(0)) / sizeof(int);
        for (int j = 0; j < nTypes; j++) {
            root["landCountsInProcess"][i][j] = Json::Value(m_landCountInProcess.at(i)[j]);
        }
    }
    QString logLandPath = logDir.absoluteFilePath(QString("%1_landCountsInProcess.json").arg(m_curRepeatEpoch));
    Json::StyledWriter sw;
    ofstream           os;
    os.open(logLandPath.toStdString());
    os << sw.write(root);
    os.close();

    // 重置
    ui->te_res->clear();
    qDeleteAll(m_landCountInProcess);
    m_landCountInProcess.clear();
}

QDir BatchCASimDialog::getOrCreateLogsDir() {
    QString key = ui->tw_configs->item(m_curConfigNum, 0)->text();
    QDir    dir(m_configMap[key]->getCurDir());
    QString logDirPath = dir.absoluteFilePath("Logs");
    if (!dir.exists("Logs")) {
        dir.mkdir("Logs");
    }
    return QDir(logDirPath);
}

void BatchCASimDialog::getEpochFromlogIniFile(QString logPath) {
    QSettings settings(logPath, QSettings::IniFormat);
    settings.beginGroup("summaryInfo");
    int tmp = settings.value("repeatNum").toInt();
    if (tmp == 0) {
        settings.setValue("repeatNum", ui->sb_runTimes->value());
    } else {
        ui->sb_runTimes->setValue(tmp);
    }
    settings.endGroup();
}

void BatchCASimDialog::on_btn_start_clicked() {
    QString tmpMsg = "";
    if (ui->rb_sim->isChecked())
        tmpMsg = QString::fromLocal8Bit("模拟");
    else if (ui->rb_eval->isChecked())
        tmpMsg = QString::fromLocal8Bit("验证");
    else if (ui->rb_batchChange->isChecked())
        tmpMsg = QString::fromLocal8Bit("批量改起点/prob");
    else if (ui->rb_batchChangeParam->isChecked())
        tmpMsg = QString::fromLocal8Bit("批量参数");
    if (QMessageBox::question(this, QString::fromLocal8Bit("运行提示"), tmpMsg, QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::No) {
        return;
    }
    ui->btn_start->setEnabled(false);
    ui->te_res->clear();
    int configCount = m_configMap.size();
    if (configCount == 0) return;
    ui->pb_overall->setMaximum(configCount);
    ui->pb_overall->setValue(0);
    ui->w_loading->start();
    ui->w_loading->setVisible(true);
    m_curConfigNum   = 0;  // 运行第一个配置
    m_curRepeatEpoch = 0;  // 运行第一个配置，第1轮
    if (ui->rb_eval->isChecked()) {
        startEvalSimulation();
    } else if (ui->rb_sim->isChecked()) {
        //        ();
        startSimulationByThreadPool();
    } else if (ui->rb_batchChangeParam->isChecked()) {  // 批量修改参数
        ui2ParamJson();
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        ui->btn_start->setEnabled(true);
    } else {  // 批量修改模拟起点和概率
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        if (m_startYearTifPath != "" || m_probTifPath != "") {
            for (int i = 0; i < m_configMap.size(); i++) {
                QString            key = ui->tw_configs->item(i, 0)->text();
                CBatchCaSimConfig *cb  = m_configMap[key];
                if (ui->le_startPath->text().trimmed() != "")
                    cb->setValueToJsonByKey("landUsePath", ui->le_startPath->text());
                if (ui->le_probPath->text().trimmed() != "")
                    cb->setValueToJsonByKey("probsPath", ui->le_probPath->text());
            }
            QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量修改完毕"));
        } else {
            QMessageBox::warning(this, QString::fromLocal8Bit("缺失数据"),
                QString::fromLocal8Bit("批量修改需要模拟起始tif或prob文件至少一个"));
        }
    }
}

void BatchCASimDialog::setMSGFromThread2UI(QString msg) { ui->te_res->append(msg); }

void BatchCASimDialog::slotProcessFinshed() {
    QString key = ui->tw_configs->item(m_curConfigNum, 0)->text();
    m_configMap[key]->setEndIterTimes(m_configMap[key]->getEndIterTimes() + m_landCountInProcess.length());
    ui->tw_configs->item(m_curConfigNum, 4)->setText(QString::number(m_configMap[key]->getMeanIterTimes()));
    saveLogs();                                                // 保存日志
    m_curRepeatEpoch++;                                        // 重复运行次数+1
    if (m_curRepeatEpoch >= m_configMap[key]->getEpoches()) {  // 一个配置已经运行完所有次数
        m_curConfigNum++;                                      // 运行下一个配置
        if (m_curConfigNum >= m_configMap.size()) {
            ui->tw_configs->item(m_curConfigNum - 1, 3)->setText(m_status.finished);
            ui->pb_overall->setValue(m_curConfigNum);
            ui->pb_curConfig->setValue(m_curRepeatEpoch);
            ui->w_loading->stop();
            ui->w_loading->setVisible(false);
            m_configMap[key]->resetSimPath2Config();  //重置配置
            saveSummaryLogToIniFile(m_configMap[key]);
            m_configMap[key]->setEndIterTimes(0);
            QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量模拟完毕"));
            ui->btn_start->setEnabled(true);
            return;
        }  // 所有配置都重复多次运行完毕
        if (ui->le_targetPath->text().trimmed() != "") {
            m_configMap[key]->genEvalConfig(ui->le_targetPath->text());  // 生成用于验证的配置文件
        }

        // 开启下一个配置的运行
        saveSummaryLogToIniFile(m_configMap[key]);
        m_configMap[key]->setEndIterTimes(0);
        ui->tw_configs->selectRow(m_curConfigNum);
        m_configMap[key]->resetSimPath2Config();  // 重置配置
        ui->tw_configs->item(m_curConfigNum - 1, 3)->setText(m_status.finished);
        ui->pb_overall->setValue(m_curConfigNum);      // 总体 重置
        m_curRepeatEpoch = 0;                          // 重置重复运行轮数
        ui->pb_curConfig->setValue(m_curRepeatEpoch);  // 多次运行 重置
        startASimulation();
    } else {  // 当前配置需要再次重复运行
        ui->pb_curConfig->setValue(m_curRepeatEpoch);
        startASimulation();
    }
}

void BatchCASimDialog::slotEvalProcessFinshed() {
    QString content = ui->te_res->toPlainText().trimmed();
    QDir    logDir  = getOrCreateLogsDir();
    QFile   file(logDir.absoluteFilePath(QString("%1_eval.log").arg(m_curRepeatEpoch + 1)));
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);  //分行写入文件
        out << ui->te_res->toPlainText();
    }
    //    ui->te_res->clear();

    // 记录统计指标
    Json::Reader reader;
    Json::Value  root;
    QString      key = ui->tw_configs->item(m_curConfigNum, 0)->text();
    QDir         dir(m_configMap[key]->getCurDir());
    //从文件中读取，保证当前文件有test.json文件
    QString  sumPath = dir.absoluteFilePath("summary_val.json");
    ifstream in(sumPath.toStdString(), ios::binary);
    bool     status;
    if (!in.is_open()) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1").arg(sumPath));
        status = false;
    }
    // 获取多次运行的平均结果
    if (reader.parse(in, root)) {
        m_configMap[key]->m_meanValRes.kappa = root["Mean"]["kappa"].asDouble();

        m_configMap[key]->m_meanValRes.fom = root["Mean"]["fom"].asDouble();

        m_configMap[key]->m_meanValRes.oa = root["Mean"]["oa"].asDouble();
    }
    ui->tw_configs->item(m_curConfigNum, 5)->setText(QString::number(m_configMap[key]->m_meanValRes.kappa));
    ui->tw_configs->item(m_curConfigNum, 6)->setText(QString::number(m_configMap[key]->m_meanValRes.fom));
    ui->tw_configs->item(m_curConfigNum, 7)->setText(QString::number(m_configMap[key]->m_meanValRes.oa));

    saveSummaryLogToIniFile(m_configMap[key], "eval");

    if (++m_curConfigNum >= m_configMap.size()) {
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        ui->pb_overall->setValue(m_curConfigNum);
        QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量验证完毕"));
        return;
    }
    startEvalSimulation();
}

void BatchCASimDialog::slotEvalProcessFinshed(QList<QList<double>> valRes) {
    QString content     = ui->te_res->toPlainText().trimmed();
    QDir    logDir      = getOrCreateLogsDir();
    QString evalLogPath = logDir.absoluteFilePath("eval_log.ini");
    //    QFile   file(logDir.absoluteFilePath(QString("%1_eval.log").arg(m_curRepeatEpoch + 1)));
    //    if (file.open(QIODevice::WriteOnly)) {
    //        QTextStream out(&file);  //分行写入文件
    //        out << ui->te_res->toPlainText();
    //    }
    //    file.close();

    //    ui->te_res->clear();

    // 记录每一轮的评价指标
    QSettings settings(evalLogPath, QSettings::IniFormat);
    for (int i = 0; i < valRes.size(); i++) {
        if (i == valRes.size() - 1) {
            settings.beginGroup("Mean");
        } else {
            settings.beginGroup(QString("epoch_%1").arg(i + 1));
        }
        settings.setValue("OA", valRes.at(i).at(0));
        settings.setValue("Kappa", valRes.at(i).at(1));
        settings.setValue("Fom", valRes.at(i).at(2));
        settings.endGroup();
    }

    // 获取多次运行的平均结果
    QString       key                    = ui->tw_configs->item(m_curConfigNum, 0)->text();
    QList<double> meanVal                = valRes.at(valRes.size() - 1);
    m_configMap[key]->m_meanValRes.oa    = meanVal[0];
    m_configMap[key]->m_meanValRes.kappa = meanVal[1];
    m_configMap[key]->m_meanValRes.fom   = meanVal[2];

    ui->tw_configs->item(m_curConfigNum, 5)->setText(QString::number(m_configMap[key]->m_meanValRes.kappa));
    ui->tw_configs->item(m_curConfigNum, 6)->setText(QString::number(m_configMap[key]->m_meanValRes.fom));
    ui->tw_configs->item(m_curConfigNum, 7)->setText(QString::number(m_configMap[key]->m_meanValRes.oa));

    saveSummaryLogToIniFile(m_configMap[key], "eval");

    if (++m_curConfigNum >= m_configMap.size()) {
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        ui->pb_overall->setValue(m_curConfigNum);
        QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量验证完毕"));
        ui->btn_start->setEnabled(true);
        return;
    }
    startEvalSimulation();
}

void BatchCASimDialog::setProcess2Bar(int k) { ui->pb_curSim->setValue(k); }

void BatchCASimDialog::slotSetLandCounts(int *landCounts, int key) {
    //    QList<int> list;
    int  n   = _msize(landCounts) / sizeof(int);
    int *tmp = new int[n];
    for (int i = 0; i < n; ++i) {
        tmp[i] = landCounts[i];
    }
    m_landCountInProcess << tmp;
}

void BatchCASimDialog::setRes2Te() {
    QByteArray qbt = m_process->readAllStandardOutput();
    QString    msg = QString::fromLocal8Bit(qbt);
    QString    str = msg.simplified();
    int        pos = str.indexOf(rx);
    if (pos >= 0) {
        ui->pb_curSim->setValue((rx.cap(1).toInt() * 1.0) / rx.cap(2).toInt() * 100);
    }
    ui->te_res->append(msg);
    //    ui->te_res->update();
}

void BatchCASimDialog::saveSummaryLogToIniFile(CBatchCaSimConfig *cb, QString mode) {
    QString path = ui->le_logPath->text();
    if (path == "") {
        QDir dir(ui->le_runDir->text());
        path = dir.absoluteFilePath("summary.ini");
    }
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    QString gName = cb->getCurConfigDirName();
    settings.beginGroup(gName);
    if (mode == "sim") {                                             // 模拟阶段只重置迭代次数
        settings.setValue("meanIterTImes", cb->getMeanIterTimes());  // 平均迭代次数
        settings.setValue("repeat", cb->getEpoches());               // 重复运行次数
    } else {
        settings.setValue("repeat", cb->getEpoches());  // 重复运行次数
        settings.setValue("oa", QString::number(cb->m_meanValRes.oa, 'f', 5));
        settings.setValue("kappa", QString::number(cb->m_meanValRes.kappa, 'f', 5));
        settings.setValue("fom", QString::number(cb->m_meanValRes.fom, 'f', 5));
    }
    settings.endGroup();
}

void BatchCASimDialog::initCBBySumLogFile(CBatchCaSimConfig *cb) {
    QString path = ui->le_logPath->text();
    if (path == "") {
        QDir dir(ui->le_runDir->text());
        path = dir.absoluteFilePath("summary.ini");
    }
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    QString gName = cb->getCurConfigDirName();
    settings.beginGroup(gName);  // 模拟阶段只重置迭代次数

    cb->setMeanEndIterTimes(settings.value("meanIterTimes").toInt());
    cb->m_meanValRes.oa    = settings.value("oa").toDouble();
    cb->m_meanValRes.kappa = settings.value("kappa").toDouble();
    cb->m_meanValRes.fom   = settings.value("fom").toDouble();
    settings.endGroup();
}

void BatchCASimDialog::evalSimResult(CBatchCaSimConfig *cb, bool useCPlus) {
    ui->pb_curSim->setValue(0);
    if (useCPlus) {  // 使用c++
        m_valThread = new ValidationThread(0);
        m_valThread->setEvalConfigPath(cb->getEvalConfigPath());
        connect(m_valThread, SIGNAL(isDone(QList<QList<double>>)), this,
            SLOT(slotEvalProcessFinshed(QList<QList<double>>)));
        m_valThread->start();
    } else {  // 使用python
        QString program = MUTILS::EXEPATH;
        QString modeArg = "eval";
        if (!MUTILS::useScriptWithLocalEnv) {
            // 运行打包好的python程序，exe
            program.append(" -m " + modeArg);
            program.append(" -c " + cb->getEvalConfigPath());
            ui->te_res->append(program);
            qDebug() << program;
            m_process->start(program);
        } else {
            // 运行本地的python脚本
            QString pythonExePath = MUTILS::initPythonEnv(m_process);  // 初始化环境
            // 构造执行参数
            QStringList params;
            params << MUTILS::PYTHONSCRIPTPATH << "--mode=" + modeArg << "--config=" + cb->getEvalConfigPath();
            m_process->start(pythonExePath, params);
        }
    }
}

void BatchCASimDialog::reset() {
    ui->tw_configs->clearContents();
    m_configMap.clear();
    m_rowNumPathMap.clear();
}

QStringList BatchCASimDialog::GetMultiDirectory() {
    QFileDialog fileDlg(this, tr("Select Directory"), "");
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
    fileDlg.setOption(QFileDialog::DontUseNativeDialog, true);
    QListView *listView = fileDlg.findChild<QListView *>("listView");
    if (listView) listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    QTreeView *treeView = fileDlg.findChild<QTreeView *>();
    if (treeView) treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if (fileDlg.exec()) {
        QStringList folders = fileDlg.selectedFiles();
        return folders;
    }
    return QStringList();
}

void BatchCASimDialog::startSimulationByThreadPool() {
    m_numOfRuningTask = ui->tw_configs->rowCount();
    m_pool.setMaxThreadCount(ui->sb_threadNum->value());
    for (int i = 0; i < ui->tw_configs->rowCount(); i++) {
        ui->tw_configs->item(i, 3)->setText(m_status.waiting);
        CBatchCaSimConfig * cb  = m_configMap[ui->tw_configs->item(i, 0)->text()];
        CommonRunnableTask *crt = new CommonRunnableTask(CommonRunnableTask::Sim, cb, i);
        connect(
            crt, SIGNAL(signalEpochFinished(int, int, int)), this, SLOT(slotRunnableOneEpochFinshed(int, int, int)));
        connect(crt, SIGNAL(finished(int)), this, SLOT(slotRunnableFinshed(int)));
        connect(crt, SIGNAL(signalStartRun(int)), this, SLOT(slotTaskStart(int)));
        m_pool.start(crt);
        crt->setAutoDelete(true);
        QThread::msleep(200);  // 必须间隔一段时间再启动，不然会使程序崩溃
    }
}

void BatchCASimDialog::on_btn_stop_clicked() {}

void BatchCASimDialog::on_pushButton_clicked() {
    QStringList dirPathsList = GetMultiDirectory();
    if (dirPathsList.size() == 0) return;
    reset();
    QFileInfo fi(dirPathsList.at(0));
    QDir      parDir = fi.dir();
    ui->le_runDir->setText(parDir.path());
    m_batchSimDir     = parDir.path();
    m_batchSimDirName = parDir.dirName();
    if (!ui->cb_newRepeatNum->isChecked()) getEpochFromlogIniFile(parDir.absoluteFilePath(m_summaryLogName));
    for (QString path : dirPathsList) {
        CBatchCaSimConfig *cb = new CBatchCaSimConfig(path, ui->sb_runTimes->value());
        // 合法判断 + 去重
        if (cb->isValid() && !m_configMap.contains(cb->getCaConfigPath())) {
            m_configMap[cb->getCaConfigPath()] = cb;
            initCBBySumLogFile(cb);
            addOneConfigToTW(cb);  // 添加到表格
        }
    }
    initTable();
}

void BatchCASimDialog::on_pb_starPath_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择模拟起点tif"), false, "Text File(*.tif)");
    if (filePath == "") return;
    ui->le_startPath->setText(filePath);
    m_startYearTifPath = filePath;
}

void BatchCASimDialog::on_pb_probFile_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择适应性概率tif"), false, "Text File(*.tif)");
    if (filePath == "") return;
    ui->le_probPath->setText(filePath);
    m_probTifPath = filePath;
    ui->gb_simConfig->setEnabled(true);
    ui->tab_matrix->setEnabled(true);
}

void BatchCASimDialog::initTable() {
    ui->tw_LUD->clear();
    ui->tw_CM->clear();
    ui->tw_WN->clear();
    if (ui->tw_configs->rowCount() == 0) return;
    QString            key = ui->tw_configs->item(0, 0)->text();
    CBatchCaSimConfig *cb  = m_configMap[key];
    m_landUseDemand        = cb->getLandUseDemand();
    m_wnb                  = cb->getWnb();
    m_costMatrix           = cb->getCostMatrix();
    ui->sp_endDiffValue->setValue(cb->getEndDiffValue());
    ui->sb_MIN->setValue(cb->getMaxIter());
    ui->sb_NO->setValue(cb->getNeiOdd());
    qDebug() << m_landUseDemand;

    int col = 0, row = 0;

    //    TifDataEntity *tif       = new TifDataEntity(ui->le_startPath->text());
    //    int            imgWidth  = tif->getCol();
    //    int            imgHeigth = tif->getRow();
    m_nTypes           = m_landUseDemand.size();
    QStringList labels = MUTILS::getRangeList(m_nTypes);
    this->m_maxCounts  = 0;
    int tc;
    //    this->m_landCounts = new int[m_nTypes];
    //    for (int i = 0; i < m_nTypes; ++i) {
    //        tc                    = tif->getLandCountByLandCode(i + 1);
    //        this->m_landCounts[i] = tc;
    //        this->m_maxCounts     = this->m_maxCounts > tc ? this->m_maxCounts : tc;
    //    }

    //    for (int i = 0; i < m_nTypes; i++) {
    //        m_landUseDemand.append(0);
    //        m_wnb.append(0);
    //        QList<double> tmpList;
    //        for (int j = 0; j < m_nTypes; j++) {
    //            tmpList.append(0);
    //        }
    //        m_costMatrix.append(tmpList);
    //    }

    ui->tw_LUD->setRowCount(2);
    ui->tw_LUD->setColumnCount(m_nTypes);
    ui->tw_LUD->setHorizontalHeaderLabels(labels);
    ui->tw_LUD->setVerticalHeaderLabels({"Future Pixel Number"});
    for (int i = 0; i < m_nTypes; i++) {
        ui->tw_LUD->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    int i = 1;
    for (int tmp : m_landUseDemand) {
        QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
        _tmp0->setTextAlignment(Qt::AlignCenter);
        ui->tw_LUD->setItem(0, col, _tmp0);

        //        QTableWidgetItem *_tmp1 = new QTableWidgetItem(QString::number(tif->getLandCountByLandCode(i++)));
        //        _tmp1->setTextAlignment(Qt::AlignCenter);
        //        ui->tw_LUD->setItem(0, col, _tmp1);
        col++;
    }
    //    tif->close();
    //    delete tif;

    ui->tw_WN->setRowCount(1);
    ui->tw_WN->setColumnCount(m_nTypes);
    ui->tw_WN->setHorizontalHeaderLabels(labels);
    ui->tw_WN->verticalHeader()->setVisible(false);
    for (int i = 0; i < m_nTypes; i++) {
        ui->tw_WN->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    col = 0;
    for (double tmp : m_wnb) {
        QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
        _tmp0->setTextAlignment(Qt::AlignCenter);
        ui->tw_WN->setItem(0, col++, _tmp0);
    }

    ui->tw_CM->setRowCount(m_nTypes);
    ui->tw_CM->setColumnCount(m_nTypes);
    ui->tw_CM->setHorizontalHeaderLabels(labels);
    ui->tw_CM->setVerticalHeaderLabels(labels);
    for (int i = 0; i < m_nTypes; i++) {
        ui->tw_CM->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    col = 0;
    row = 0;
    for (QList<double> tmpList : m_costMatrix) {
        for (double tmp : tmpList) {
            QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
            _tmp0->setTextAlignment(Qt::AlignCenter);
            ui->tw_CM->setItem(row, col++, _tmp0);
        }
        row++;
        col = 0;
    }
}

void BatchCASimDialog::ui2ParamJson() {
    int tmp;
    int curSumLand = 0;
    int furSumLand = 0;
    for (int i = 0; i < m_nTypes; i++) {
        tmp = ui->tw_LUD->item(0, i)->text().toInt();
        curSumLand += ui->tw_LUD->item(0, i)->text().toInt();
        furSumLand += tmp;
        m_maxCounts        = m_maxCounts > tmp ? m_maxCounts : tmp;
        m_landUseDemand[i] = tmp;
        m_wnb[i]           = ui->tw_WN->item(0, i)->text().toDouble();
        for (int j = 0; j < m_nTypes; j++) {
            m_costMatrix[i][j] = ui->tw_CM->item(i, j)->text().toDouble();
        }
    }

    for (int i = 0; i < m_configMap.size(); i++) {
        QString            key = ui->tw_configs->item(i, 0)->text();
        CBatchCaSimConfig *cb  = m_configMap[key];
        cb->setLandUseDemand(m_landUseDemand);
        cb->setWnb(m_wnb);
        cb->setCostMatrix(m_costMatrix);
        cb->setMaxIter(ui->sb_MIN->value());
        cb->setNeiOdd(ui->sb_NO->value());
        cb->setEndDiffValue(ui->sp_endDiffValue->value());
        cb->updateToJsonFile();
        cb->print();
    }
    QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量修改完毕"));
}

void BatchCASimDialog::on_btn_start_clicked(bool checked) {}

void BatchCASimDialog::slotRunnableFinshed(int row) {
    ui->tw_configs->item(row, 3)->setText(m_status.finished);
    QString key = ui->tw_configs->item(row, 0)->text();
    saveSummaryLogToIniFile(m_configMap[key]);  // 保存日志
    ui->tw_configs->item(row, 4)->setText(QString::number(m_configMap[key]->getMeanIterTimes()));
    m_configMap[key]->resetSimPath2Config();  // 重置
    if (--m_numOfRuningTask == 0) {
        ui->w_loading->stop();
        ui->w_loading->setVisible(false);
        ui->btn_start->setEnabled(true);
        QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("批量模拟完毕"));
    }
}

void BatchCASimDialog::slotRunnableOneEpochFinshed(int row, int epoch, int endIterTimes) {
    ui->tw_configs->item(row, 2)->setText(QString::number(epoch));
    QString key = ui->tw_configs->item(row, 0)->text();
    m_configMap[key]->setEndIterTimes(m_configMap[key]->getEndIterTimes() + endIterTimes);
    ui->tw_configs->item(row, 4)->setText(QString::number(m_configMap[key]->getMeanIterTimes()));
}

void BatchCASimDialog::slotTaskStart(int row) { ui->tw_configs->item(row, 3)->setText(m_status.running); }
