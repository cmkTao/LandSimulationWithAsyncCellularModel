#include "imagedialog.h"

#include <QMessageBox>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>

#include "entity/tifdataentity.h"
#include "ui_imagedialog.h"
#include "utils/config.h"
#include "utils/constValue.h"
#include "utils/mutils.h"
#include "utils/tifTools.h"

ImageDialog::ImageDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ImageDialog) {
    ui->setupUi(this);

    if (AppConfig::autoLoadConfig) {
        ui->cb_tifPath->setVisible(true);
        connect(ui->cb_tifPath, SIGNAL(currentIndexChanged(int)), this, SLOT(showTifSlot()));
        ui->cb_tifPath->addItems(DEFAULTCONFIG::tifPathConfig.getNoEmptyPathList());
        ui->cb_tifPath->setCurrentIndex(0);
    } else {
        ui->cb_tifPath->setVisible(false);
    }
    ui->export_2->setEnabled(!ui->graphicsView->getIsLandMap());
}

ImageDialog::~ImageDialog() {
    ui->graphicsView->CloseCurrentImg();
    delete ui;
}

void ImageDialog::readImage(QString filePath) {
    ui->graphicsView->ReadImg(filePath);
    this->tifFilePath = filePath;
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->treeView->setModel(ui->graphicsView->FileListModel());
    ui->tableView->setModel(ui->graphicsView->ImgMetaModel());

    // 初始化 R G B中的 下拉框
    int         rasterBandCount = ui->graphicsView->getRasterBandCount();
    QStringList combTexts;
    for (int i = 0; i < rasterBandCount; i++) {
        combTexts << QString::number(i + 1);
    }
    ui->comB_bandR->addItems(combTexts);
    ui->comB_bandR->setCurrentIndex(0);
    ui->comB_bandG->addItems(combTexts);
    ui->comB_bandG->setCurrentIndex(rasterBandCount > 1 ? 1 : 0);
    ui->comB_bandB->addItems(combTexts);
    ui->comB_bandB->setCurrentIndex(rasterBandCount > 2 ? 2 : 0);
    connect(ui->comB_bandR, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));
    connect(ui->comB_bandG, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));
    connect(ui->comB_bandB, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));

    // 多通道栅格禁用土地颜色设置
    if (ui->graphicsView->getIsLandMap()) {
        ui->tab_color->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        initColorTableView();
        QMap<int, int> m = ui->graphicsView->getLandCounts();
        initChartView(m);
        int numOfLand = ui->tabV_landColor->rowCount() - 1;
        for (int i = 1; i <= numOfLand; i++) {
            multiCodes[i] = true;
        }
    }
}

void ImageDialog::resetUI() {
    disconnect(ui->comB_bandR, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));
    disconnect(ui->comB_bandG, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));
    disconnect(ui->comB_bandB, SIGNAL(currentIndexChanged(int)), this, SLOT(showRGBBandByCombox()));
    ui->comB_bandB->clear();
    ui->comB_bandG->clear();
    ui->comB_bandR->clear();
    ui->qcharView->setChart(new QChart());
    ui->qchartViewPercent->setChart(new QChart());
    ui->tableView->clearSpans();
    ui->tabV_landColor->clearContents();
    disconnect(
                ui->tabV_landColor, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem *)));
}

void ImageDialog::InitLandNameAndColor(QString path)
{
    if (!MUTILS::isFileExist(path)) {
        return;
    }
    QSettingTools::getLandColorsNames(path, colorMap, nameMap);

    QList<double> keys = nameMap.keys();
    for (double key : keys) {
        int i = key - 1;
        ui->tabV_landColor->item(i, 1)->setBackground(colorMap[key]);
        ui->tabV_landColor->item(i, 1)->setSelected(false);
        ui->tabV_landColor->item(i, 2)->setText(nameMap[key]);
        ui->tabV_landColor->item(i, 1)->setSelected(false);
    }

    ui->graphicsView->setColorMap(colorMap);
    ui->graphicsView->showLandColorMap(multiCodes);
}

void ImageDialog::showTifSlot() {
    QString path = DEFAULTCONFIG::namePathMap[ui->cb_tifPath->currentText()];
    ui->graphicsView->CloseCurrentImg();
    ui->graphicsView->Init();
    resetUI();
    readImage(path);
    if (ui->graphicsView->isLandMap) InitLandNameAndColor(DEFAULTCONFIG::landConfigPath);
}

void ImageDialog::showRGBBandByCombox() {
    int band1 = ui->comB_bandR->currentIndex() + 1;
    int band2 = ui->comB_bandG->currentIndex() + 1;
    int band3 = ui->comB_bandB->currentIndex() + 1;
    ui->graphicsView->showRGBByBands(band1, band2, band3);
}

void ImageDialog::colorCellClicked(QTableWidgetItem *item) {
    QTableWidget *qtw = item->tableWidget();
    int           row = item->row();
    int           col = item->column();
    // 只改变第二列
    if (qtw->horizontalHeaderItem(col)->text() == "color") {
        int    key   = qtw->item(row, 0)->text().toInt();
        QColor color = QColorDialog::getColor(Qt::white, this, "选择颜色");
        item->setBackground(color);
        item->setSelected(false);
        colorMap[key] = color;
        ui->graphicsView->setColorMap(colorMap);
        ui->graphicsView->showLandColorMap(multiCodes);
    }
}

void ImageDialog::sltTooltip(bool status, int index, QBarSet *barset) {
    QString msg = QString::fromLocal8Bit("数量：%1").arg(barset->at(index));
    QToolTip::showText(QCursor::pos(), msg);
}

void ImageDialog::showColorMapsByLandCodes() {
    //    QCheckBox * cb    = dynamic_cast<QCheckBox *>(QObject::sender());  //找到信号发送者
    QCheckBox * cb      = dynamic_cast<QCheckBox *>(QObject::sender());            //找到信号发送者
    QModelIndex index   = ui->tabV_landColor->indexAt(cb->parentWidget()->pos());  //定位按钮
    int         row     = index.row();
    multiCodes[row + 1] = !multiCodes[row + 1];
    ui->graphicsView->showLandColorMap(multiCodes);
}

void ImageDialog::initColorTableView() {
    colorMap = ui->graphicsView->getColorMap();
    // 初始化表格
    QStringList headers = {"LandCode", "color", "Name", "Visible"};
    ui->tabV_landColor->setRowCount(colorMap.size());
    ui->tabV_landColor->setColumnCount(headers.size());
    // 设置每一列的宽度
    ui->tabV_landColor->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tabV_landColor->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tabV_landColor->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tabV_landColor->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tabV_landColor->setHorizontalHeaderLabels(headers);
    ui->tabV_landColor->verticalHeader()->setVisible(false);
    QMapIterator<double, QColor> imap(colorMap);
    int                          row = 0;
    while (imap.hasNext()) {
        imap.next();
        if (ui->graphicsView->getNoDataValue() == 0 && imap.key() == 0) {
            row = colorMap.size() - 1;
        }
        QTableWidgetItem *_tmp0 = new QTableWidgetItem(QString::number(imap.key()));
        _tmp0->setTextAlignment(Qt::AlignCenter);
        _tmp0->setFlags(_tmp0->flags() & (~Qt::ItemIsEditable));  // <不可编辑>
        ui->tabV_landColor->setItem(row, 0, _tmp0);

        QTableWidgetItem *_tmp1 = new QTableWidgetItem("");
        _tmp1->setTextAlignment(Qt::AlignCenter);
        _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));  // <不可编辑>
        _tmp1->setBackground(imap.value());
        _tmp1->setFlags(_tmp1->flags() & (~Qt::ItemIsEditable));
        ui->tabV_landColor->setItem(row, 1, _tmp1);

        if (row == colorMap.size() - 1) {
            ui->tabV_landColor->setItem(row, 2, new QTableWidgetItem(QString::fromLocal8Bit("无效值")));
            ui->tabV_landColor->setItem(row, 3, new QTableWidgetItem(""));
        } else {
            QString name = QString::fromLocal8Bit("土地-%1").arg(row + 1);
            if (nameMap.contains(row + 1)) {
                name = nameMap[row + 1] == "" ? name : nameMap[row + 1];
            } else {
                nameMap[row + 1] = name;
            }
            ui->tabV_landColor->setItem(row, 2, new QTableWidgetItem(name));
            QWidget *    widget = new QWidget;
            QHBoxLayout *layout = new QHBoxLayout;
            QCheckBox *  box    = new QCheckBox;
            box->setChecked(true);
            layout->addWidget(box);
            layout->setMargin(0);
            layout->setAlignment(box, Qt::AlignCenter);
            widget->setLayout(layout);
            connect(box, SIGNAL(stateChanged(int)), this, SLOT(showColorMapsByLandCodes()));
            ui->tabV_landColor->setCellWidget(row, 3, widget);
        }
        row++;
        if (imap.key() == 0) {
            row = 0;
        }
    }
    connect(
        ui->tabV_landColor, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(colorCellClicked(QTableWidgetItem *)));
}

void ImageDialog::initChartView(QMap<int, int> landCounts) {
    //![1]
    QBarSet *              set0 = new QBarSet("numbers");
    QBarSet *              set1 = new QBarSet("percentage");
    QStringList            categories;
    QMapIterator<int, int> imap(landCounts);
    int                    maxCounts = 0;
    int                    sumPixels = 0;
    while (imap.hasNext()) {
        imap.next();
        categories << QString::number(imap.key());
        *set0 << imap.value();
        maxCounts = imap.value() > maxCounts ? imap.value() : maxCounts;
        sumPixels += imap.value();
    }

    imap.toFront();
    double _temp;
    while (imap.hasNext()) {
        imap.next();
        _temp = imap.value() / (sumPixels * 1.0);
        *set1 << QString::number(_temp, 'f', 4).toDouble() * 100;
    }

    // number chart
    QBarSeries *series = new QBarSeries();
    connect(series, SIGNAL(hovered(bool, int, QBarSet *)), this, SLOT(sltTooltip(bool, int, QBarSet *)));
    series->append(set0);

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

    // percentage chart
    QBarSeries *series_per = new QBarSeries();
    connect(series_per, SIGNAL(hovered(bool, int, QBarSet *)), this, SLOT(sltTooltip(bool, int, QBarSet *)));
    series_per->append(set1);
    QChart *chart_per = new QChart();
    chart_per->addSeries(series_per);
    chart_per->setTitle("The percentage of each land type");
    chart_per->setAnimationOptions(QChart::SeriesAnimations);
    QBarCategoryAxis *axis_per = new QBarCategoryAxis();
    axis_per->append(categories);
    chart_per->addAxis(axis_per, Qt::AlignBottom);
    series_per->attachAxis(axis_per);
    QValueAxis *axisY_per = new QValueAxis();
    axisY_per->setRange(0, 100);
    chart_per->addAxis(axisY_per, Qt::AlignLeft);
    series_per->attachAxis(axisY_per);
    chart_per->legend()->setVisible(true);  //设置图例为显示状态
    chart_per->legend()->setAlignment(Qt::AlignBottom);

    ui->qcharView->setChart(chart);
    ui->qchartViewPercent->setChart(chart_per);
}

void ImageDialog::on_export_2_clicked() {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    QString   filePath = QFileDialog::getSaveFileName(this, tr("Open File"), lastPath, tr("Text File(*.tif)"));
    if (filePath == "") {
        return;
    }
    qDebug() << filePath;
    TifDataEntity *outPutTifData = new TifDataEntity(this->tifFilePath);

    int bc = outPutTifData->getBandCounts();
    int rr = 100;
    int cc = 100;
    for (int i = 0; i < bc; i++) qDebug() << outPutTifData->getValueByBandAndPos(i, rr, cc) << " ";
    return;

    float *          buffer         = new float[outPutTifData->getNumOfAllBands()];
    CVALUE::PROBMODE probType       = CVALUE::PROBMODE(ui->comboBox->currentIndex());
    float *          randLayerValue = new float[outPutTifData->getBandCounts()];
    // 同一层使用相同概率值
    for (int i = 0; i < outPutTifData->getBandCounts(); i++) {
        randLayerValue[i] = MUTILS::getRandDoubleInRange(0, 1);
    }
    int imageSize = outPutTifData->getNumOfAllPixels();
    for (int j = 0; j < outPutTifData->getBandCounts(); j++) {
        for (int i = 0; i < imageSize; i++) {
            int tmpIndex = j * imageSize + i;
            switch (probType) {
                case CVALUE::PROBMODE::FIXED:  // 固定值1（所有层所有位置）
                    buffer[tmpIndex] = 1;
                    break;
                case CVALUE::PROBMODE::RANDOMLAYERSAME:  // 随机值（同一层所有位置用一个概率值）
                    buffer[tmpIndex] = randLayerValue[j];
                    break;
                case CVALUE::PROBMODE::RANDOM:  // 随机值（不同层不同位置）
                default:
                    buffer[tmpIndex] = MUTILS::getRandDoubleInRange(0, 1);
                    break;
            }
        }
    }
    bool res = TIFTOOLS::writeTIF2File<float>(
        buffer, outPutTifData->getDataType(), filePath, outPutTifData->getBandCounts(), outPutTifData);
    if (res) {
        QMessageBox::information(nullptr, "Success!", QString::fromLocal8Bit("文件导出成功 %1").arg(filePath));
    } else {
        QMessageBox::critical(nullptr, "Success!", QString::fromLocal8Bit("配置文件保存失败： %1").arg(filePath));
    }
}

void ImageDialog::on_pushButton_clicked() {
    int len = ui->tabV_landColor->rowCount();
    if (len == 0) return;
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择文件..."), false, "Text File(*.ini)");
    if (filePath == "") return;
    QSettingTools::getLandColorsNames(filePath, colorMap, nameMap);

    QList<double> keys = nameMap.keys();
    for (double key : keys) {
        int i = key - 1;
        ui->tabV_landColor->item(i, 1)->setBackground(colorMap[key]);
        ui->tabV_landColor->item(i, 1)->setSelected(false);
        ui->tabV_landColor->item(i, 2)->setText(nameMap[key]);
        ui->tabV_landColor->item(i, 1)->setSelected(false);
    }

    ui->graphicsView->setColorMap(colorMap);
    ui->graphicsView->showLandColorMap(multiCodes);
}

void ImageDialog::on_pushButton_2_clicked() {
    int len = ui->tabV_landColor->rowCount();
    if (len == 0) return;
    QString filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择保存位置..."), false, "Text File(*.ini)", true);
    qDebug() << filePath;
    if (filePath == "") return;
    QMutableMapIterator<double, QString> i(nameMap);
    while (i.hasNext()) {
        i.next();
        QString name = ui->tabV_landColor->item(i.key() - 1, 2)->text().trimmed();
        if (name != "") i.setValue(name);
    }
    QSettingTools::saveLandColorsNames(filePath, colorMap, nameMap);
    QMessageBox::information(nullptr, "Success!", QString::fromLocal8Bit("配置文件保存成功： %1").arg(filePath));
}
