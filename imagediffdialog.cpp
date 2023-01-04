#include "imagediffdialog.h"

#include "ui_imagediffdialog.h"

ImageDiffDialog::ImageDiffDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ImageDiffDialog) {
    ui->setupUi(this);
    tifImage_1 = NULL;
    tifImage_2 = NULL;

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->addButton(ui->rb_hR);
    m_btnGroup->addButton(ui->rb_vR);
    connect(m_btnGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(operatingModeButtonsToggled(int, bool)));

    connectSlot();
    if (AppConfig::autoLoadConfig) {
        disconnect(
            ui->tw_color, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem *)));
        ui->groupBox->setVisible(false);
        QStringList list = DEFAULTCONFIG::tifPathConfig.getDiffPair();
        ui->cb_config->addItems(list);
        connect(ui->cb_config, SIGNAL(currentIndexChanged(int)), this, SLOT(diffTypeChoiceSlot()));
        if (list.length() == 0) {
            return;
        }
        ui->cb_config->setCurrentIndex(0);
        emit diffTypeChoiceSlot();
        InitLandColorAndName(DEFAULTCONFIG::landConfigPath);
    } else {
        ui->cb_config->setVisible(false);
    }
}

ImageDiffDialog::~ImageDiffDialog() {
    delete ui;
    if (tifImage_1 != NULL) {
        tifImage_1->close();
        tifImage_1 = NULL;
    }
    if (tifImage_2 != NULL) {
        tifImage_2->close();
        tifImage_2 = NULL;
    }
}

void ImageDiffDialog::InitLandColorAndName(QString filePath)
{
    if (!MUTILS::isFileExist(filePath) || !filePath.endsWith("ini")) {
        return;
    }
    QSettingTools::getLandColorsNames(filePath, colorMap, nameMap);
    qDebug() << colorMap;
    qDebug() << nameMap;
    QList<double> keys = nameMap.keys();
    for (double key : keys) {
        int i = key - 1;
        ui->tw_color->item(i, 1)->setBackground(colorMap[key]);
        ui->tw_color->item(i, 1)->setSelected(false);
        ui->tw_color->item(i, 2)->setText(nameMap[key]);
        ui->tw_color->item(i, 2)->setSelected(false);
        setList.at(i)->setColor(colorMap[key]);
    }
    if (ui->cb_landCode->currentIndex() != 0) {
        QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap);
        ui->gv_map->setMapAndUpdate(imgItem);
    }
}

void ImageDiffDialog::operatingModeButtonsToggled(int id, bool status) {
    int tmp = m_btnGroup->checkedId();
    if (tmp == -2 && status == 1) {
        for (int i = 0; i < transMatrix.size(); i++) {
            for (int j = 0; j < transMatrix.size(); j++) {
                double tmp = ui->tw_transMatrix->item(i, j)->text().toDouble();
                tmp /= tifImage_1->getLandCountByLandCode(i + 1);
                ui->tw_transMatrix->item(i, j)->setText(QString::number(MUTILS::truncateDouble(tmp, 6)));
            }
        }
    }
    if (tmp == -3 && status == 1) {
        for (int i = 0; i < transMatrix.size(); i++) {
            for (int j = 0; j < transMatrix.size(); j++) {
                ui->tw_transMatrix->item(i, j)->setText(QString::number(transMatrix[i][j]));
            }
        }
    }
}

void ImageDiffDialog::slotColorTableTextChanged(int row, int col) {
    if (col != 2 || this->setList.size() == 0) return;
    QString text = ui->tw_color->item(row, col)->text().trimmed();
    if (text == "") text = QString::fromLocal8Bit("土地-%1").arg(row + 1);
    this->setList.at(row)->setLabel(text);
    nameMap[row + 1] = text;
}

void ImageDiffDialog::diffTypeChoiceSlot() {
    QStringList diffPair = ui->cb_config->currentText().split("-");
    qDebug() << diffPair;
    ui->le_img1->setText(DEFAULTCONFIG::namePathMap[diffPair[0]]);
    ui->le_img2->setText(DEFAULTCONFIG::namePathMap[diffPair[1]]);
    disconnect(ui->cb_landCode, SIGNAL(currentIndexChanged(int)), this, SLOT(getNewDatas()));
    qDebug() << ui->le_img1->text();
    qDebug() << ui->le_img2->text();
    ui->btn_confirm->click();
}

void ImageDiffDialog::connectSlot() {
    connect(ui->tw_color, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem *)));
    connect(ui->tw_color, SIGNAL(cellChanged(int, int)), this, SLOT(slotColorTableTextChanged(int, int)));
}

QString ImageDiffDialog::getPathFromDialog() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    QString   filePath;
    filePath = QFileDialog::getOpenFileName(this, "Open File", lastPath, "Text File(*.tif)");
    return filePath;
}

/**
 * @brief ImageDiffDialog::initColorTable
 * 初始化颜色表格
 */
void ImageDiffDialog::initColorTable() {
    QStringList headers = {"LandCode", "Color", "Name"};
    int         maxN    = tifImage_1->getMax();
    ui->tw_color->setRowCount(maxN);
    // 初始化表格
    ui->tw_color->setColumnCount(headers.size());
    // 设置每一列的宽度
    ui->tw_color->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tw_color->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tw_color->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tw_color->setHorizontalHeaderLabels(headers);
    ui->tw_color->verticalHeader()->setVisible(false);
    // 获取一组随机颜色
    colorMap = colorMap.size() == 0 ? MUTILS::getRandomColorsMap(maxN) : colorMap;
    QMapIterator<double, QColor> imap(colorMap);
    int                          row = 0;
    while (imap.hasNext()) {
        imap.next();
        ui->tw_color->setItem(row, 0, getUEditQWI(QString::number(imap.key())));

        QTableWidgetItem *_tmp1 = getUEditQWI("");
        _tmp1->setTextAlignment(Qt::AlignCenter);
        _tmp1->setBackground(imap.value());
        _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));
        ui->tw_color->setItem(row, 1, _tmp1);

        QString name = "";
        if (nameMap.contains(row + 1)) {
            name = nameMap[row + 1];
        }
        QTableWidgetItem *_tmp2 = new QTableWidgetItem(name);
        _tmp2->setTextAlignment(Qt::AlignCenter);
        ui->tw_color->setItem(row, 2, _tmp2);
        row++;
    }
}

QTableWidgetItem *ImageDiffDialog::getUEditQWI(QString str_) {
    QTableWidgetItem *_tmp0 = new QTableWidgetItem(str_);
    _tmp0->setTextAlignment(Qt::AlignCenter);
    _tmp0->setFlags(_tmp0->flags() & (~Qt::ItemIsEditable));  // <不可编辑>
    return _tmp0;
}

void ImageDiffDialog::initTransTable() {
    int         maxN     = tifImage_1->getMax();
    QStringList Hheaders = MUTILS::getRangeList(maxN);
    QStringList Vheaders = MUTILS::getRangeList(maxN);
    Hheaders << QString::fromLocal8Bit("img1-总和");
    Vheaders << QString::fromLocal8Bit("img2-总和");
    ui->tw_transMatrix->setRowCount(maxN + 1);
    // 初始化表格
    ui->tw_transMatrix->setColumnCount(Hheaders.size());
    // 设置每一列的宽度
    for (int i = 0; i < maxN + 1; i++) {
        ui->tw_transMatrix->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    ui->tw_transMatrix->setHorizontalHeaderLabels(Hheaders);
    ui->tw_transMatrix->setVerticalHeaderLabels(Vheaders);
    int row = 0, col = 0;
    int landCount1 = 0;
    int landCount2 = 0;
    for (QList<int> tem_ : transMatrix) {
        for (int v : tem_) {
            ui->tw_transMatrix->setItem(row, col++, getUEditQWI(QString::number(v)));
        }
        landCount1 += tifImage_1->getLandCountByLandCode(row + 1);
        ui->tw_transMatrix->setItem(
            row, col, getUEditQWI(QString::number(tifImage_1->getLandCountByLandCode(row + 1))));
        row++;
        col = 0;
    }
    // 添加最后一行
    for (int i = 0; i < maxN; i++) {
        landCount2 += tifImage_2->getLandCountByLandCode(i + 1);
        ui->tw_transMatrix->setItem(row, i, getUEditQWI(QString::number(tifImage_2->getLandCountByLandCode(i + 1))));
    }
    ui->tw_transMatrix->setItem(row, maxN, getUEditQWI(QString("1_%1/2_%2").arg(landCount1).arg(landCount2)));
}

/**
 * @brief ImageDiffDialog::initTransBarChart
 * 初始化柱状图
 */
void ImageDiffDialog::initTransBarChart() {
    ui->widget_5->setEnabled(true);
    int         itemp      = 0;
    int         subMax     = 0;
    int         currIndex  = ui->cb_landCode->currentIndex();
    int         maxN       = tifImage_1->getMax();
    QStringList categories = MUTILS::getRangeList(maxN);
    //    QList<QBarSet *> setList;
    //    setList.clear();
    if (setList.size() == 0) {
        for (QString strTmp : categories) {
            setList << new QBarSet(QString::fromLocal8Bit("土地-%1").arg(strTmp));
        }
    }
    int maxCounts = 0;
    for (int i = 0; i < maxN; i++) {
        qDebug() << transMatrix[i];
        for (int j = 0; j < maxN; j++) {
            int tmp   = transMatrix[j][i];
            maxCounts = tmp > maxCounts ? tmp : maxCounts;
            if (i + 1 == currIndex) {
                subMax = tmp > subMax ? tmp : subMax;
            }
            *setList[i] << tmp;
        }
        setList.at(i)->setColor(colorMap[i + 1]);
    }

    if (currIndex != 0) {
        maxCounts = subMax;
    }

    maxCounts += 100;
    // number chart
    QBarSeries *series = new QBarSeries();
    connect(series, SIGNAL(hovered(bool, int, QBarSet *)), this, SLOT(sltTooltip(bool, int, QBarSet *)));

    for (QBarSet *tmp : setList) {
        if (currIndex == 0) {
            series->append(tmp);
        } else {
            if (itemp + 1 == currIndex) {
                series->append(tmp);
                break;
            } else {
                itemp++;
            }
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("The sum pixels of each land type");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->addAxis(axis, Qt::AlignBottom);
    series->attachAxis(axis);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxCounts);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);               //设置图例为显示状态
    chart->legend()->setAlignment(Qt::AlignBottom);  //设置图例的显示位置在底部
    ui->qchart_trans->setChart(chart);
}

void ImageDiffDialog::on_btn_img1_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择图像1.."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_img1->setText(filePath);
    imgPath1 = filePath;
}

void ImageDiffDialog::on_btn_img2_clicked() {
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择图像2.."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_img2->setText(filePath);
    imgPath2 = filePath;
}

/**
 * @brief ImageDiffDialog::on_btn_confirm_clicked
 * 确认按钮
 */
void ImageDiffDialog::on_btn_confirm_clicked() {
    // 重置
    if (tifImage_1 != NULL) {
        tifImage_1->close();
        tifImage_1 = NULL;
    }

    if (tifImage_2 != NULL) {
        tifImage_2->close();
        tifImage_2 = NULL;
    }

    ui->gv_map->CloseCurrentImg();
    ui->gv_map->Init();

    //    ui->tw_color->clearContents();
    //    ui->tw_transMatrix->clearContents();
    //    ui->qchart_trans->setChart(new QChart());
    ui->cb_landCode->clear();

    // 禁用文件选择部分
    ui->le_img1->setEnabled(false);
    ui->le_img2->setEnabled(false);
    ui->btn_img1->setEnabled(false);
    ui->btn_img2->setEnabled(false);
    //    ui->btn_confirm->setEnabled(false);
    imgPath1 = ui->le_img1->text();
    imgPath2 = ui->le_img2->text();
    //    imgPath1 = "E:/project/LUCC/software/hgs/hgs_datas/12n.tif";
    //    imgPath2 = "E:/project/LUCC/software/hgs/hgs_datas/17n.tif";
    //    imgPath1 = "E:/project/LUCC/software/FLUS_V2.4/testdata/dg2001coor.tif";
    //    imgPath2 = "E:/project/LUCC/software/FLUS_V2.4/testdata/dg2006true.tif";
    // 初始化两张tif
    tifImage_1 = new TifDataEntity(imgPath1);
    tifImage_2 = new TifDataEntity(imgPath2);

    if (ui->cb_legal->isChecked()) {
        datas                        = tifImage_1->getDiffOfLegalData(tifImage_2);
        QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap, true);
        ui->gv_map->setMapAndUpdate(imgItem);
        return;
    }

    transMatrix = tifImage_1->getTransitionMatrix(tifImage_2);

    QFileInfo fi(imgPath1);
    QFileInfo ci(fi.absoluteDir().path() + "/" + "colors.ini");
    if (ci.exists()) QSettingTools::getLandColorsNames(ci.path(), colorMap, nameMap);

    // 初始化颜色表格
    initColorTable();

    // 初始化转化表格
    initTransTable();

    // 初始设置灰度图
    datas                        = tifImage_1->getDiffData(tifImage_2, 0);
    QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap, true);
    ui->gv_map->setMapAndUpdate(imgItem);

    // 初始化下拉框
    QStringList combTexts;
    int         max_ = tifImage_1->getMax();
    for (int i = 0; i <= max_; i++) {
        combTexts << QString::number(i);
    }
    ui->cb_landCode->addItems(combTexts);
    connect(ui->cb_landCode, SIGNAL(currentIndexChanged(int)), this, SLOT(getNewDatas()));

    // 初始化转化柱状图
    this->setList.clear();
    initTransBarChart();
}

// ===================== slots ================================
void ImageDiffDialog::colorCellClicked(QTableWidgetItem *item) {
    QTableWidget *qtw = item->tableWidget();
    int           row = item->row();
    int           col = item->column();
    // 只改变第二列
    if (qtw->horizontalHeaderItem(col)->text() != "Color") {
        return;
    }
    int    key   = qtw->item(row, 0)->text().toInt();
    QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
    item->setBackground(color);
    item->setSelected(false);
    colorMap[key] = color;
    if (ui->cb_landCode->currentIndex() != 0) {
        QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap);
        ui->gv_map->setMapAndUpdate(imgItem);
    }
}

void ImageDiffDialog::sltTooltip(bool status, int index, QBarSet *barset) {
    QString msg = QString::fromLocal8Bit("%1 转化为 土地%2 的数量：%3")
                      .arg(barset->label())
                      .arg(index + 1)
                      .arg(barset->at(index));
    QToolTip::showText(QCursor::pos(), msg);
}

void ImageDiffDialog::getNewDatas() {
    int currIndex                = ui->cb_landCode->currentIndex();
    datas                        = tifImage_1->getDiffData(tifImage_2, currIndex);
    QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap, currIndex == 0);
    ui->gv_map->setMapAndUpdate(imgItem);
    initTransBarChart();
}

void ImageDiffDialog::on_pushButton_clicked() {
    if (setList.size() == 0) return;
    int     len = setList.size();
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择保存位置..."), false, "Text File(*.ini)", true);
    qDebug() << filePath;
    if (filePath == "") return;

    QSettingTools::saveLandColorsNames(filePath, colorMap, nameMap);
    QMessageBox::information(nullptr, "Success!", QString::fromLocal8Bit("配置文件保存成功： %1").arg(filePath));
}

void ImageDiffDialog::on_pushButton_2_clicked() {
    int len = this->setList.size();
    if (len == 0) return;
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择文件..."), false, "Text File(*.ini)");
    if (filePath == "") return;

    QSettingTools::getLandColorsNames(filePath, colorMap, nameMap);
    qDebug() << colorMap;
    qDebug() << nameMap;
    QList<double> keys = nameMap.keys();
    for (double key : keys) {
        int i = key - 1;
        ui->tw_color->item(i, 1)->setBackground(colorMap[key]);
        ui->tw_color->item(i, 1)->setSelected(false);
        ui->tw_color->item(i, 2)->setText(nameMap[key]);
        ui->tw_color->item(i, 2)->setSelected(false);
        setList.at(i)->setColor(colorMap[key]);
    }
    if (ui->cb_landCode->currentIndex() != 0) {
        QGraphicsPixmapItem *imgItem = MUTILS::getColorMap(datas, tifImage_1->getBand(1), colorMap);
        ui->gv_map->setMapAndUpdate(imgItem);
    }
}
