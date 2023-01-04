#include "cadialog.h"

#include "ui_cadialog.h"
CADialog::CADialog(QWidget *parent) : QDialog(parent), ui(new Ui::CADialog) {
    ui->setupUi(this);

    // 初始化变量
    chart      = NULL;
    axisY      = NULL;
    axisX      = NULL;
    landCounts = NULL;

    ui->w_loading->setDotCount(15);
    ui->w_loading->setMaxDiameter(3);
    ui->w_loading->setMinDiameter(1);
    ui->w_loading->setVisible(false);
    pattern             = "at (\\d*) iteration";
    rx                  = QRegExp(pattern);
    caThread            = NULL;
    this->pause         = false;
    this->isinitedColor = false;
    if (AppConfig::autoLoadConfig) {
        ui->groupBox_3->setVisible(false);
        ui->btn_saveOther->setVisible(false);
        ui->gb_filePath->setVisible(false);
        ui->rb_one->setEnabled(false);
        ui->rb_two->setEnabled(false);
        qDebug() << "===1231";
        ui->comboBox->addItems(DEFAULTCONFIG::getYearsOfCA());
        qDebug() << "===";
        connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(yearChangeSlot()));
        ui->btn_chConfig->click();
        qDebug() << "==---==";
        ui->btn_start->setEnabled(true);

    } else {
        ui->groupBox_2->setVisible(false);
    }
    // 初始化
    //    this->imgItem = new QGraphicsPixmapItem();
    //    ui->gv_map->setMapAndUpdate(imgItem);

    // 只显示CA功能，隐藏ACA
    //    ui->label_8->setVisible(false);
    //    ui->doubleSpinBox->setVisible(false);
    //    ui->cb_caType->setVisible(false);

#ifdef QT_NO_DEBUG
#else
//    emit ui->btn_chConfig->click();
//    emit ui->btn_saveConfig->click();
#endif

    connect(ui->tw_colors, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem *)));
    connect(ui->tw_colors, SIGNAL(cellChanged(int, int)), this, SLOT(slotColorTableTextChanged(int, int)));
}

CADialog::~CADialog() {
    delete ui;
    //    caThread->terminate();
    //    if (caThread != nullptr && caThread->isRunning()) {
    //        caThread->terminate();
    //    }
}

void CADialog::on_btn_chConfig_clicked() {
    QString filePath;
    if (!AppConfig::autoLoadConfig) {
#ifdef QT_NO_DEBUG
        filePath
            = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置文件..."), false, "Text File(*.json)");
#else
        //    filePath = "E:/project/c/qt_project/test_demo/dg_demo/ca_config.json";
        filePath
            = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置文件..."), false, "Text File(*.json)");
#endif
        if (filePath == "") {
            return;
        }
    } else {
        if (DEFAULTCONFIG::caDefaultConfigPath.length() == 0) {
            QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("缺少CA模拟需要的配置文件！！！"));
            return;
        }
        filePath = DEFAULTCONFIG::caDefaultConfigPath[ui->comboBox->currentIndex()];
    }
    if (filePath == "") return;

    resetUI();
    ui->le_configPath->setText(filePath);

    if (json2Ui(filePath)) {
        ui->btn_prob->setEnabled(true);
        ui->btn_sp->setEnabled(true);
        ui->le_prob->setEnabled(true);
        ui->le_sp->setEnabled(true);
        ui->le_res->setEnabled(true);
        ui->gb_simConfig->setEnabled(true);
        ui->tab_matrix->setEnabled(true);
        ui->btn_saveConfig->setEnabled(true);
        ui->btn_saveOther->setEnabled(true);
        ui->btn_res->setEnabled(true);
    }
    if (MUTILS::isFileExist(ui->le_landuse->text())) {
        initTable();
        qDebug() << "1";
        initColorTable();
         qDebug() << "2";
        initChart();
         qDebug() << "3";
    }
}

void CADialog::initTable() {
    SAFE_DELETE_ARRAY(landCounts);

    ui->tw_LUD->clear();
    ui->tw_CM->clear();
    ui->tw_WN->clear();
    QStringList labels = MUTILS::getRangeList(nTypes);
    int         col = 0, row = 0;

    TifDataEntity *tif = new TifDataEntity(ui->le_landuse->text());
    imgWidth           = tif->getCol();
    imgHeigth          = tif->getRow();
    nTypes             = tif->getNTypes();
    this->maxCounts    = 0;
    int tc;
    this->landCounts = new int[nTypes];
    for (int i = 0; i < this->nTypes; ++i) {
        tc                  = tif->getLandCountByLandCode(i + 1);
        this->landCounts[i] = tc;
        this->maxCounts     = this->maxCounts > tc ? this->maxCounts : tc;
    }

    ui->tw_LUD->setRowCount(2);
    ui->tw_LUD->setColumnCount(nTypes);
    ui->tw_LUD->setHorizontalHeaderLabels(labels);
    ui->tw_LUD->setVerticalHeaderLabels({"Initial Pixel Number", "Future Pixel Number"});
    for (int i = 0; i < nTypes; i++) {
        ui->tw_LUD->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    int i = 1;
    for (int tmp : landUseDemand) {
        QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
        _tmp0->setTextAlignment(Qt::AlignCenter);
        ui->tw_LUD->setItem(1, col, _tmp0);

        QTableWidgetItem *_tmp1 = new QTableWidgetItem(QString::number(tif->getLandCountByLandCode(i++)));
        _tmp1->setTextAlignment(Qt::AlignCenter);
        ui->tw_LUD->setItem(0, col, _tmp1);
        col++;
    }
    tif->close();
    delete tif;

    ui->tw_WN->setRowCount(1);
    ui->tw_WN->setColumnCount(nTypes);
    ui->tw_WN->setHorizontalHeaderLabels(labels);
    ui->tw_WN->verticalHeader()->setVisible(false);
    for (int i = 0; i < nTypes; i++) {
        ui->tw_WN->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    col = 0;
    for (double tmp : wnb) {
        QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
        _tmp0->setTextAlignment(Qt::AlignCenter);
        ui->tw_WN->setItem(0, col++, _tmp0);
    }

    ui->tw_CM->setRowCount(nTypes);
    ui->tw_CM->setColumnCount(nTypes);
    ui->tw_CM->setHorizontalHeaderLabels(labels);
    ui->tw_CM->setVerticalHeaderLabels(labels);
    for (int i = 0; i < nTypes; i++) {
        ui->tw_CM->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    col = 0;
    row = 0;
    for (QList<double> tmpList : costMatrix) {
        for (double tmp : tmpList) {
            QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(tmp));
            _tmp0->setTextAlignment(Qt::AlignCenter);
            ui->tw_CM->setItem(row, col++, _tmp0);
        }
        row++;
        col = 0;
    }
}

void CADialog::plotCurveChart() {}

QPen CADialog::getPenFromColor(QColor color, int width) {
    QPen splinePen;
    splinePen.setWidth(width);
    splinePen.setBrush(color);
    splinePen.setColor(color);
    return splinePen;
}

QTableWidgetItem *CADialog::getUEditQWI(QString str_) {
    QTableWidgetItem *_tmp0 = new QTableWidgetItem(str_);
    _tmp0->setTextAlignment(Qt::AlignCenter);
    _tmp0->setFlags(_tmp0->flags() & (~Qt::ItemIsEditable));  // <不可编辑>
    return _tmp0;
}

QTableWidgetItem *CADialog::getEditQWI(QString str_)
{
    QTableWidgetItem *_tmp0 = new QTableWidgetItem(str_);
    _tmp0->setTextAlignment(Qt::AlignCenter);
    return _tmp0;
}

void CADialog::updateImgInProcessSaveDir() {
    QFileInfo fileInfo(ui->le_configPath->text());
    imgInProcessSaveDir = fileInfo.path() + "/" + "logs_img_in_process";
    QDir dir;
    if (!dir.exists(imgInProcessSaveDir)) {
        qDebug() << "bu cun zai ";
        dir.mkdir(imgInProcessSaveDir);
    } else {
        if (dir.path() != imgInProcessSaveDir) {
            dir.setPath(imgInProcessSaveDir);
        }
        if (!dir.removeRecursively()) {
            qDebug() << QString::fromLocal8Bit("删除失败");
        } else {
            qDebug() << QString::fromLocal8Bit("删除成功");
            dir.mkdir(imgInProcessSaveDir);
        }
    }
}

void CADialog::saveChart() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap  p      = screen->grabWindow(ui->chart_landCounts->winId());
    QImage   image  = p.toImage();
    image.save(imgInProcessSaveDir + "/chart.png");
}

void CADialog::saveLogs() {
    QFile file(imgInProcessSaveDir + "/simProcess.log");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);  //分行写入文件
        out << ui->te_res->toPlainText();
    }
    Json::Value root;
    int         epochs = this->landCountInProcess.length();
    for (int i = 0; i < epochs; i++) {
        for (int j = 0; j < this->nTypes; j++) {
            root["landCountsInProcess"][i][j] = Json::Value(this->landCountInProcess[i][j]);
        }
    }
    QString            logLandPath = imgInProcessSaveDir + "/landCountsInProcess.json";
    Json::StyledWriter sw;
    ofstream           os;
    os.open(logLandPath.toStdString());
    os << sw.write(root);
    os.close();
    QMessageBox::information(
        nullptr, "Success!", QString::fromLocal8Bit("模拟过程保存成功： %1").arg(imgInProcessSaveDir));
}

void CADialog::uI2Json(QString jsonPath) {
    //根节点
    Json::Value root;
    root["usedYears"]   = Json::Value(ui->rb_one->isChecked() ? 1 : 2);
    root["landUsePath"] = Json::Value(ui->le_landuse->text().toStdString());
    root["probsPath"]   = Json::Value(ui->le_prob->text().toStdString());
    root["saveSimPath"] = Json::Value(ui->le_sp->text().toStdString());
    if (ui->le_res->text() != "") {
        root["restrictedPath"] = Json::Value(ui->le_res->text().toStdString());
    }
    root["degree"] = Json::Value(ui->dsb_Degree->value());

    //子节点
    Json::Value simConfig;
    simConfig["maxIterNum"]       = Json::Value(ui->sb_MIN->value());
    simConfig["neighboorhoodOdd"] = Json::Value(ui->sb_NO->value());
    root["simConfig"]             = Json::Value(simConfig);
    int tmp;
    int curSumLand = 0;
    int furSumLand = 0;
    for (int i = 0; i < nTypes; i++) {
        tmp = ui->tw_LUD->item(1, i)->text().toInt();
        curSumLand += ui->tw_LUD->item(0, i)->text().toInt();
        furSumLand += tmp;
        maxCounts = maxCounts > tmp ? maxCounts : tmp;
        root["landUseDemand"].append(tmp);
        root["weightOfNeighborhood"].append(ui->tw_WN->item(0, i)->text().toDouble());
        for (int j = 0; j < nTypes; j++) {
            root["costMatrix"][i][j] = Json::Value(ui->tw_CM->item(i, j)->text().toDouble());
        }
    }

    // 记录模拟类型
    switch (ui->cb_caType->currentIndex()) {
        case 1:
            root["caMode"]   = Json::Value("ACA");
            root["acaRatio"] = Json::Value(ui->doubleSpinBox->value());
            break;
        case 0:
        default:
            root["caMode"]   = Json::Value("CA");
            root["acaRatio"] = Json::Value(ui->doubleSpinBox->value());
            break;
    }

    // 记录土地对应的颜色
    QMapIterator<double, QColor> i(this->colorMap);
    QList<QString>               colorStrList;
    for (int k = 0; k < this->colorMap.size() + 1; k++) {
        colorStrList << " ";
    }
    while (i.hasNext()) {
        i.next();
        colorStrList[i.key()] = MUTILS::qColor2HexStr(i.value());
    }
    for (QString tStr : colorStrList) {
        root["colors"].append(tStr.toStdString());
    }

    if (ui->sp_endDiffValue->value() != 0) root["endDiffValue"] = ui->sp_endDiffValue->value();

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
    //    if (!AppConfig::autoLoadConfig) {
    //        DEFAULTCONFIG::tifPathConfig.startTifPath = ui->le_landuse->text();
    //        DEFAULTCONFIG::tifPathConfig.simTifPath   = ui->le_sp->text();
    //    }
    if (curSumLand != furSumLand) {
        QMessageBox::warning(nullptr, "warn!",
            QString::fromLocal8Bit("土地总量不一致 现状：%1；未来：%2；差距：%3")
                .arg(QString::number(curSumLand), QString::number(furSumLand),
                    QString::number(furSumLand - curSumLand)));
        qDebug() << QString::fromLocal8Bit("土地总量不一致 现状：%1；未来：%2；差距：%3")
                        .arg(QString::number(curSumLand), QString::number(furSumLand),
                            QString::number(furSumLand - curSumLand));
    }
}

bool CADialog::json2Ui(QString jsonPath) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(jsonPath.toStdString(), ios::binary);
    bool         status;
    if (!in.is_open()) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1").arg(jsonPath));
        status = false;
    }
    if (reader.parse(in, root)) {
        ui->le_landuse->setText(MUTILS::string2Qstring(root["landUsePath"].asString()));
        if (root.isMember("probsType")) {
            QString probTypes = MUTILS::string2Qstring(root["probsType"].asString());
            if (probTypes == "fixed") {
                //                 ui->rb_file->setChecked(true);
            } else if (probTypes == "random") {
                //                 ui->rb_rand->setChecked(true);
            } else {
                //                 ui->rb_file->setChecked(true);
            }
        }
        ui->le_prob->setText(MUTILS::string2Qstring(root["probsPath"].asString()));
        ui->le_sp->setText(MUTILS::string2Qstring(root["saveSimPath"].asString()));
        if (root["usedYears"].asInt() == 2) {
            ui->rb_two->setChecked(true);
        } else {
            ui->rb_one->setChecked(true);
        }

        ui->sb_MIN->setValue(root["simConfig"]["maxIterNum"].asInt());
        ui->sb_NO->setValue(root["simConfig"]["neighboorhoodOdd"].asInt());
        ui->dsb_Degree->setValue(root["degree"].asDouble());

        if (root.isMember("restrictedPath")) {
            ui->le_res->setText(MUTILS::string2Qstring(root["restrictedPath"].asString()));
        }

        if (root.isMember("end")) {
            ui->le_res->setText(MUTILS::string2Qstring(root["restrictedPath"].asString()));
        }

        landUseDemand.clear();
        wnb.clear();
        costMatrix.clear();

        tempVal = root["landUseDemand"];
        nSize   = tempVal.size();
        nTypes  = nSize;
        for (int i = 0; i < nSize; i++) {
            landUseDemand.append(tempVal[i].asInt());
        }

        tempVal = root["weightOfNeighborhood"];
        for (int i = 0; i < nSize; i++) {
            this->wnb.append(tempVal[i].asDouble());
        }

        tempVal = root["costMatrix"];
        for (int i = 0; i < nSize; i++) {
            QList<double> temp;
            for (int j = 0; j < nSize; j++) {
                temp.append(tempVal[i][j].asDouble());
            }
            costMatrix.append(temp);
        }

        // 初始化CA模式
        if (root.isMember("caMode")) {
            if (root["caMode"].asString() == "ACA") {
                ui->cb_caType->setCurrentIndex(1);
                ui->doubleSpinBox->setValue(root["acaRatio"].asDouble());
            } else {
                ui->cb_caType->setCurrentIndex(0);
                if (root["acaRatio"].asDouble() != 0) ui->doubleSpinBox->setValue(root["acaRatio"].asDouble());
            }
        }

        // 读取颜色
        if (root.isMember("colors")) {
            if (root["colors"].size() == nSize + 1) {
                this->isinitedColor = true;
                for (int k = 1; k <= nSize; k++) {
                    this->colorMap[k] = MUTILS::hexStr2QColor(MUTILS::string2Qstring(root["colors"][k].asString()));
                }
            }
        }

        if (root.isMember("endDiffValue")) {
            ui->sp_endDiffValue->setValue(root["endDiffValue"].asInt());
        }

        //        initTable();
        //        initChart();
        status = true;

    } else {
        QMessageBox::critical(nullptr, "Error!", QString("fail to parse file %1").arg(jsonPath));
        status = false;
    }
    in.close();
    return status;
}

void CADialog::resetUI() {
    ui->le_configPath->setText("");
    ui->le_sp->setText("");
    ui->le_landuse->setText("");
    ui->le_sp->setText("");
    ui->le_res->setText("");
    ui->dsb_Degree->setValue(0.1);
    ui->sb_MIN->setValue(35);
    ui->sb_NO->setValue(3);
    ui->rb_one->setChecked(true);
}

void CADialog::yearChangeSlot() { ui->btn_chConfig->click(); }

void CADialog::colorCellClicked(QTableWidgetItem *item) {
    QTableWidget *qtw = item->tableWidget();
    int           row = item->row();
    int           col = item->column();
    // 只改变第二列
    if (qtw->horizontalHeaderItem(col)->text() != "Color") {
        return;
    }
    int    key   = qtw->item(row, 0)->text().toInt();
    QColor color = QColorDialog::getColor(Qt::white, this, QString::fromLocal8Bit("选择颜色"));
    item->setBackground(color);
    item->setSelected(false);
    colorMap[key] = color;
    series[key]->setPen(getPenFromColor(color));
}

void CADialog::slotColorTableTextChanged(int row, int col) {
    if (col == 2 && series.size() != 0) {
        // 曲线名称默认为土地像素编号
        QString name   = landNames.value(row, ui->tw_colors->item(row, col)->text());
        landNames[row] = name;
        series[row + 1]->setName(name == "" ? QString("%1").arg(row + 1) : name);
    }
}

void CADialog::setVisibleStatus() {
    QCheckBox * cb              = dynamic_cast<QCheckBox *>(QObject::sender());       //找到信号发送者
    QModelIndex index           = ui->tw_colors->indexAt(cb->parentWidget()->pos());  //定位按钮
    int         row             = index.row();
    this->isVisibleMap[row + 1] = !this->isVisibleMap[row + 1];
}

void CADialog::on_btn_saveConfig_clicked() {
    QString filePath = ui->le_configPath->text();
    if (filePath == "") {
        QMessageBox::information(nullptr, "TIPS!", QString::fromLocal8Bit("请选择需要保存的配置文件"));
    } else {
        uI2Json(filePath);
        ui->btn_start->setEnabled(true);
    }
}

void CADialog::on_btn_saveOther_clicked() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    QString   filePath = QFileDialog::getSaveFileName(this, tr("Open File"), lastPath, tr("Text File(*.json)"));
    if (filePath == "") {
        return;
    }
    uI2Json(filePath);
    ui->le_configPath->setText(filePath);
    ui->btn_start->setEnabled(true);
}

void CADialog::on_btn_lu_clicked() {
    QString filePath;
    filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择土地利用数据..."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_landuse->setText(filePath);
    // 未加载配置文件
    if (landUseDemand.size() == 0) {
        TifDataEntity *tif = new TifDataEntity(filePath);
        nTypes             = tif->getNTypes();
        for (int i = 0; i < nTypes; i++) {
            landUseDemand.append(0);
            wnb.append(0);
            QList<double> tmpList;
            for (int j = 0; j < nTypes; j++) {
                tmpList.append(0);
            }
            costMatrix.append(tmpList);
        }
        if (ui->le_configPath->text() != "") {
            return;
        }
        ui->btn_prob->setEnabled(true);
        ui->btn_sp->setEnabled(true);
        ui->le_prob->setEnabled(true);
        ui->le_sp->setEnabled(true);
        ui->le_res->setEnabled(true);
        ui->gb_simConfig->setEnabled(true);
        ui->tab_matrix->setEnabled(true);
        ui->btn_saveConfig->setEnabled(true);
        ui->btn_saveOther->setEnabled(true);
        ui->btn_res->setEnabled(true);
        tif->close();  // 关闭，避免加载过多
        delete tif;
    }

    // 初始化默认值
    initTable();
    initColorTable();
    initChart();
}

void CADialog::on_btn_prob_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择土地利用数据...", false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_prob->setText(filePath);
}

void CADialog::on_btn_sp_clicked() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    QString   filePath = QFileDialog::getSaveFileName(this, tr("Open File"), lastPath, tr("Text File(*.tif)"));
    ui->le_sp->setText(filePath);
}

void CADialog::on_btn_start_clicked() {
    qDebug() << QThread::currentThreadId() << "---UI";
    imgCount = 0;
    updateImgInProcessSaveDir();
    ui->pgb_process->setMaximum(ui->sb_MIN->value());
    ui->pgb_process->setValue(0);

    axisY->setRange(0, maxCounts);
    axisX->setRange(0, ui->sb_MIN->value());
    for (int i = 0; i < this->nTypes; ++i) {
        this->series[i + 1]->clear();
    }

    ui->te_res->clear();

    createThread();
    caThread->setConfigPath(ui->le_configPath->text());
    //    m_process = new QProcess(this);
    //    m_process->setProcessChannelMode(QProcess::MergedChannels);
    //    m_process->setReadChannel(QProcess::StandardOutput);
    //    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setRes2Te()));
    //    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinshed()));
    //    QString program = MUTILS::EXEPATH;
    //    QString modeArg = "ca";
    //    program.append(" -m " + modeArg);
    //    program.append(" -c " + ui->le_configPath->text());
    //    ui->te_res->append(program);
    //    qDebug() << program;
    //    m_process->start(program);
    caThread->start();
    ui->w_loading->start();
    ui->w_loading->setVisible(true);
    ui->btn_start->setEnabled(false);
    ui->btn_stop->setEnabled(true);
    ui->btn_pause->setEnabled(true);
}

void CADialog::setRes2Te() {
    QByteArray qbt = m_process->readAllStandardOutput();
    QString    msg = QString::fromLocal8Bit(qbt);
    QString    str = msg.simplified();
    int        pos = str.indexOf(rx);
    if (pos >= 0) {
        ui->pgb_process->setValue(rx.cap(1).toInt() + 1);
    }
    ui->te_res->append(msg);
    //    ui->te_res->update();
}

void CADialog::slotProcessFinshed() {
    //    ui->pgb_epochs->setValue(ui->sb_Epochs->value() + 1);
    ui->te_res->append(QString::fromLocal8Bit("模拟完毕！ "));
    ui->w_loading->stop();
    ui->w_loading->setVisible(false);
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setEnabled(false);
    ui->btn_pause->setEnabled(false);

    saveChart();
    saveLogs();

    if (caThread) {
        delete caThread;
        caThread = NULL;
    }
    //    VLDReportLeaks();
}

void CADialog::on_btn_stop_clicked() {
    //    m_process->kill();
    //    delete m_process;
    caThread->setStopFlag(true);
    //    ui->te_res->append(QString::fromLocal8Bit("运行提前终止!!!"));
    //    ui->w_loading->stop();
    //    ui->w_loading->setVisible(false);
    //    ui->btn_start->setEnabled(true);
    //    ui->btn_stop->setEnabled(false);
    //    ui->btn_pause->setEnabled(false);
}

void CADialog::on_btn_res_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择限制图层...", false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_res->setText(filePath);
}

void CADialog::sltTooltip(QPointF point, bool status) { return; }

void CADialog::setMSGFromThread2UI(QString msg) { ui->te_res->append(msg); }

void CADialog::setProcess2Bar(int k) { ui->pgb_process->setValue(k); }

void CADialog::slotSetImage(float *imgData, GDALRasterBand *band) {
    if (!MUTILS::showCASimulationProcessImages) return;
    //    MUTILS::getColorMap(imgData, band, colorMap, false, this->isVisibleMap, this->imgItem);
    //    this->imgItem->setPixmap(MUTILS::getColorMap(imgData, band, colorMap, false, this->isVisibleMap));
    QGraphicsPixmapItem *it = MUTILS::getColorMap(imgData, band, colorMap, false, this->isVisibleMap, NULL);
    ui->gv_map->setMapAndUpdate(it);
    ++imgCount;
    QString path = imgInProcessSaveDir + QString("/%1.png").arg(imgCount);
    ui->gv_map->saveImage(path, imgWidth, imgHeigth);
}

void CADialog::slotSetLandCounts(int *landCounts, int key) {
    int        diff;
    QList<int> list;
    for (int i = 0; i < this->nTypes; ++i) {
        this->series[i + 1]->append(QPointF(key, landCounts[i]));
        diff = ui->tw_LUD->item(1, i)->text().toInt();
        ui->tw_colors->item(i, 5)->setText(QString("%1").arg(landCounts[i]));
        ui->tw_colors->item(i, 6)->setText(QString("%1").arg(diff - landCounts[i]));
        list << landCounts[i];
    }
    this->landCountInProcess << list;
}

void CADialog::initChart() {
//    SAFE_DELETE(chart);
//    SAFE_DELETE(axisX);
//    SAFE_DELETE(axisY);
    qDeleteAll(series);
    series.clear();
    //    ui->chart_landCounts->close();

    chart = new QChart();
    chart->setTitle(QString::fromLocal8Bit("土地数量变化"));
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    axisX->setTickCount(1);
    axisY->setTickCount(1);
    axisX->setLabelFormat("%d");
    axisY->setLabelFormat("%d");
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisX->setTitleText("Iteratioin");
    axisY->setTitleText("pixels of each land");
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    for (int i = 0; i < this->nTypes; ++i) {
        series[i + 1] = new QSplineSeries(this);
        chart->addSeries(series[i + 1]);
        series[i + 1]->setPen(getPenFromColor(colorMap[i + 1]));
        series[i + 1]->append(QPointF(0, landCounts[i]));
        series[i + 1]->attachAxis(axisX);
        series[i + 1]->attachAxis(axisY);
        series[i + 1]->setName(QString("%1").arg(i + 1));
        connect(series[i + 1], SIGNAL(hovered(QPointF, bool)), this, SLOT(sltTooltip(QPointF, bool)));
    }
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chart_landCounts->setChart(chart);
}

void CADialog::initColorTable() {
    ui->tw_colors->clear();
    // 初始化颜色表格
    QStringList headers = {"LandCode", "Color", "Name", "Visible", "future", "curr", "diff"};
    int         maxN    = this->nTypes;
    if (!this->isinitedColor) {
        // 获取一组随机颜色
        colorMap            = MUTILS::getRandomColorsMap(maxN);
        this->isinitedColor = true;
    }
    QString landConfigPath = DEFAULTCONFIG::landConfigPath;
    if (AppConfig::autoLoadConfig && landConfigPath.endsWith("ini") && MUTILS::isFileExist(landConfigPath)) {
         QSettingTools::getLandColorsNames(landConfigPath, colorMap, nameMap);
    }
    qDebug() << colorMap;
    qDebug() << nameMap;
    colorMap = !this->isinitedColor ? MUTILS::getRandomColorsMap(maxN) : colorMap;
    ui->tw_colors->setRowCount(maxN);
    // 初始化表格
    ui->tw_colors->setColumnCount(headers.size());
    // 设置每一列的宽度
    ui->tw_colors->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_colors->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tw_colors->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tw_colors->setHorizontalHeaderLabels(headers);
    ui->tw_colors->verticalHeader()->setVisible(false);

    int                          row = 0;
    while (row < maxN) {
        ui->tw_colors->setItem(row, 0, getUEditQWI(QString::number(row + 1)));

        QTableWidgetItem *_tmp1 = getUEditQWI("");
        //        _tmp1->setTextAlignment(Qt::AlignCenter);
        _tmp1->setBackground(colorMap[row + 1]);
        //        _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));
        ui->tw_colors->setItem(row, 1, _tmp1);

//        QTableWidgetItem *_tmp2 = new QTableWidgetItem();
//        _tmp2->setTextAlignment(Qt::AlignCenter);
//        ui->tw_colors->setItem(row, 2, _tmp2);

        if (nameMap.contains(row + 1)) {
            ui->tw_colors->setItem(row, 2, getEditQWI(nameMap[row + 1]));
        } else {
            ui->tw_colors->setItem(row, 2, getEditQWI(""));
        }


        QHBoxLayout *layout = new QHBoxLayout;
        QCheckBox *  box    = new QCheckBox;
        box->setChecked(true);
        layout->addWidget(box);
        layout->setMargin(0);
        layout->setAlignment(box, Qt::AlignCenter);
        QWidget *    widget = new QWidget;
        widget->setLayout(layout);
        connect(box, SIGNAL(stateChanged(int)), this, SLOT(setVisibleStatus()));
        ui->tw_colors->setCellWidget(row, 3, widget);

        this->isVisibleMap[row + 1] = true;

        QTableWidgetItem *_tmp3 = getUEditQWI(ui->tw_LUD->item(1, row)->text());
        ui->tw_colors->setItem(row, 4, _tmp3);

        QTableWidgetItem *_tmp4 = getUEditQWI(ui->tw_LUD->item(0, row)->text());
        ui->tw_colors->setItem(row, 5, _tmp4);

        QTableWidgetItem *_tmp5 = getUEditQWI("0");
        ui->tw_colors->setItem(row, 6, _tmp5);

        row++;
    }
     QMapIterator<double, QColor> imap(colorMap);
//    while (imap.hasNext()) {
//        imap.next();
//        ui->tw_colors->setItem(row, 0, getUEditQWI(QString::number(imap.key())));

//        QTableWidgetItem *_tmp1 = getUEditQWI("");
//        //        _tmp1->setTextAlignment(Qt::AlignCenter);
//        _tmp1->setBackground(imap.value());
//        //        _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));
//        ui->tw_colors->setItem(row, 1, _tmp1);

////        QTableWidgetItem *_tmp2 = new QTableWidgetItem();
////        _tmp2->setTextAlignment(Qt::AlignCenter);
////        ui->tw_colors->setItem(row, 2, _tmp2);

//        if (nameMap.contains(row + 1)) {
//            ui->tw_colors->setItem(row, 2, getEditQWI(nameMap[row + 1]));
//        } else {
//            ui->tw_colors->setItem(row, 2, getEditQWI(""));
//        }


//        QHBoxLayout *layout = new QHBoxLayout;
//        QCheckBox *  box    = new QCheckBox;
//        box->setChecked(true);
//        layout->addWidget(box);
//        layout->setMargin(0);
//        layout->setAlignment(box, Qt::AlignCenter);
//        QWidget *    widget = new QWidget;
//        widget->setLayout(layout);
//        connect(box, SIGNAL(stateChanged(int)), this, SLOT(setVisibleStatus()));
//        ui->tw_colors->setCellWidget(row, 3, widget);

//        this->isVisibleMap[imap.key()] = true;

//        QTableWidgetItem *_tmp3 = getUEditQWI(ui->tw_LUD->item(1, row)->text());
//        ui->tw_colors->setItem(row, 4, _tmp3);

//        QTableWidgetItem *_tmp4 = getUEditQWI(ui->tw_LUD->item(0, row)->text());
//        ui->tw_colors->setItem(row, 5, _tmp4);

//        QTableWidgetItem *_tmp5 = getUEditQWI("0");
//        ui->tw_colors->setItem(row, 6, _tmp5);

//        row++;
//    }
}

void CADialog::on_btn_pause_clicked() {
    pause = !pause;
    if (pause) {
        ui->btn_pause->setIcon(QIcon(":/img/start.png"));
        ui->btn_stop->setEnabled(false);
    } else {
        ui->btn_pause->setIcon(QIcon(":/img/pause.png"));
        ui->btn_stop->setEnabled(true);
    }
    caThread->setPauseFlag(pause);
}

void CADialog::createThread() {
    switch (ui->cb_caType->currentIndex()) {
        case 1:
            if (Global::useV2) {
                caThread = new ACCA_V2(0, "");
            } else {
                caThread = new ACA(0, "", ui->doubleSpinBox->value());
            }
            break;
        case 0:
        default:
            if (Global::useV2) {
                caThread = new CA_V2(0, "");
            } else {
                caThread = new CA(0, "");
            }
            break;
    }
    initColorTable();
    // 连接线程和UI的通信机制
    connect(caThread, SIGNAL(isDone()), this, SLOT(slotProcessFinshed()));
    connect(caThread, SIGNAL(signalSendMessage(QString)), this, SLOT(setMSGFromThread2UI(QString)));
    connect(caThread, SIGNAL(signalSendProcess(int)), this, SLOT(setProcess2Bar(int)));
    connect(caThread, SIGNAL(signalSendLandCounts(int *, int)), this, SLOT(slotSetLandCounts(int *, int)));
    connect(caThread, SIGNAL(signalSendImagData(float *, GDALRasterBand *)), this,
        SLOT(slotSetImage(float *, GDALRasterBand *)));
    //    connect(ui->tw_colors, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem
    //    *))); connect(ui->tw_colors, SIGNAL(cellChanged(int, int)), this, SLOT(slotColorTableTextChanged(int, int)));
}

void CADialog::on_btn_start_clicked(bool checked) {}
