/**
 * @projectName   qtmflus
 * @brief         摘要
 * @author        cmk
 * @date          2020-11-04
 */

#include "mutils.h"

#include <QCoreApplication>

/**
 * @brief MUTILS::ImgSketch
 * 将float数据转为unsign char数据，便于构建图像
 * @param buffer float数组
 * @param currentBand 当前band
 * @param bandSize band的大小
 * @param noValue band的无效值
 * @return
 */
unsigned char *MUTILS::ImgSketch(float *buffer, GDALRasterBand *currentBand, int bandSize, double noValue) {
    unsigned char *resBuffer = new unsigned char[bandSize];
    double         max, min, _temp;
    double         minmax[2];

    currentBand->ComputeRasterMinMax(1, minmax);
    min = minmax[0];
    max = minmax[1];
    if (min <= noValue && noValue <= max) {
        min = 0;
    }
    for (int i = 0; i < bandSize; i++) {
        _temp = buffer[i];
        if (_temp > max || _temp == noValue) {
            resBuffer[i] = 255;
        } else if (buffer[i] <= max && buffer[i] >= min) {
            resBuffer[i] = static_cast<uchar>(255 - 255 * (max - buffer[i]) / (max - min));
        } else {
            resBuffer[i] = 0;
        }
    }

    return resBuffer;
}

/**
 * @brief MUTILS::combineRGBBand2Img
 * 将各个通道的数据组合为一张图像,传入unsigned char *数据
 * @param width 图像的宽
 * @param height 图像的高
 * @param rBandUC red通道
 * @param gBandUC green通道
 * @param bBandUC blue通道
 * @return QGraphicsPixmapItem
 */
QGraphicsPixmapItem *MUTILS::combineRGBBand2Img(int width, int height, unsigned char *rBandUC, unsigned char *gBandUC,
    unsigned char *bBandUC, QGraphicsPixmapItem *item) {
    int            bytePerLine = (width * 24 + 31) / 8;
    unsigned char *allBandUC   = new unsigned char[bytePerLine * height * 3];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            allBandUC[h * bytePerLine + w * 3 + 0] = rBandUC[h * width + w];
            allBandUC[h * bytePerLine + w * 3 + 1] = gBandUC[h * width + w];
            allBandUC[h * bytePerLine + w * 3 + 2] = bBandUC[h * width + w];
        }
    }
    if (item != NULL) {
        item->setPixmap(QPixmap::fromImage(QImage(allBandUC, width, height, bytePerLine, QImage::Format_RGB888)));
        delete[] allBandUC;
        return NULL;
    } else {
        QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem(
            QPixmap::fromImage(QImage(allBandUC, width, height, bytePerLine, QImage::Format_RGB888)));
        delete[] allBandUC;
        return imgItem;
        //        return new QGraphicsPixmapItem(
        //            QPixmap::fromImage(QImage(allBandUC, width, height, bytePerLine, QImage::Format_RGB888)));
    }
    //    QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem(
    //        QPixmap::fromImage(QImage(allBandUC, width, height, bytePerLine, QImage::Format_RGB888)));

    //    return imgItem;
}

/**
 * @brief MUTILS::getColorMap
 * 为土地利用数据设置颜色
 * @param floatDatas float类型的数组
 * @param currentBand 当前的band
 * @param colorMap 颜色字典
 * @param gray 是否获取灰度图，默认为彩色图，
 * 这时传入的floatDatas中只有NoDataValue和其他(如1)两种值
 * @return QGraphicsPixmapItem
 */
QGraphicsPixmapItem *MUTILS::getColorMap(float *floatDatas, GDALRasterBand *currentBand, QMap<double, QColor> colorMap,
    bool gray, const QMap<int, bool> multiCodes, QGraphicsPixmapItem *item) {
    double min, max, minmax[2];
    currentBand->ComputeRasterMinMax(1, minmax);
    int imgWidth       = currentBand->GetXSize();
    int imgHeight      = currentBand->GetYSize();
    min                = minmax[0];
    max                = minmax[1];
    double NoDataValue = currentBand->GetNoDataValue();
    // 土地类型不能超过 限制20
    if (max - min > CONSTANTVALUE::MAX_LAND_COUNT) {
        QMessageBox::warning(
            nullptr, QString::fromLocal8Bit("运行警告提示"), QString::fromLocal8Bit("土地类型数量必须<20"));
        return NULL;
    }
    // 默认为随机颜色
    if (colorMap.size() < max) {
        for (int i = min; i <= max; i++) {
            colorMap[i] = QColor(rand() % 256, rand() % 256, rand() % 256);
        }
    }
    // 无效值白色
    colorMap[NoDataValue] = QColor(255, 255, 255);
    QColor         tempColor;
    unsigned char *rBandUC = new unsigned char[imgWidth * imgHeight];
    unsigned char *gBandUC = new unsigned char[imgWidth * imgHeight];
    unsigned char *bBandUC = new unsigned char[imgWidth * imgHeight];
    double         pixelValue;
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        pixelValue = floatDatas[i];
        if (!MUTILS::inRange(max, min, pixelValue) || !gray) {
            if (multiCodes.value(pixelValue, true)) {
                tempColor = colorMap.value(pixelValue, colorMap[NoDataValue]);
            } else {
                tempColor = colorMap[NoDataValue];
            }
        } else {
            // 灰度图除无效值外为黑色
            tempColor = QColor(0, 0, 0);
        }
        rBandUC[i] = static_cast<uchar>(tempColor.red());
        gBandUC[i] = static_cast<uchar>(tempColor.green());
        bBandUC[i] = static_cast<uchar>(tempColor.blue());
    }
    //    QGraphicsPixmapItem *imgItem = combineRGBBand2Img(imgWidth, imgHeight, rBandUC, gBandUC, bBandUC);
    //    return imgItem;
    QGraphicsPixmapItem *imgItem = combineRGBBand2Img(imgWidth, imgHeight, rBandUC, gBandUC, bBandUC, item);
    delete[] rBandUC;
    delete[] gBandUC;
    delete[] bBandUC;
    return imgItem;
}

/**
 * @brief MUTILS::getRandomColor
 * 获取一个随机颜色
 * @return
 */
QColor MUTILS::getRandomColor() { return QColor(rand() % 256, rand() % 256, rand() % 256); }

/**
 * @brief MUTILS::getRandomColors
 * 获取一组随机颜色
 * @param nums
 * @return
 */
QList<QColor> MUTILS::getRandomColors(int nums) {
    QList<QColor> res;
    for (int i = 0; i < nums; i++) {
        res << getRandomColor();
    }
    return res;
}

/**
 * @brief MUTILS::getRandomColorsMap
 * 获取颜色字典，
 * @param nums 颜色个数
 * @param start key的起始大小，默认从1开始
 * @return
 */
QMap<double, QColor> MUTILS::getRandomColorsMap(int nums, int start) {
    QMap<double, QColor> res;
    for (int i = 0; i < nums; i++) {
        res[start++] = getRandomColor();
    }
    return res;
}

QStringList MUTILS::getRangeList(int nums, int start) {
    QStringList res;
    for (int i = 0; i < nums; i++) {
        res << QString::number(start++);
    }
    return res;
}

bool MUTILS::equalNoData(double noData, double value) {
    QString str1 = QString::number(noData, 'f', 3);
    QString str2 = QString::number(value, 'f', 3);
    return str1 == str2;
}

bool MUTILS::inRange(double max, double min, double value) { return value <= max && value >= min; }

QString MUTILS::getFileFromDialog(
    QWidget *parent, QString title, bool isDir, QString suffixs, bool isSave, bool isMulti) {
    QSettings setting("./Setting.ini", QSettings::IniFormat);  //为了能记住上次打开的路径
    QString   lastPath = setting.value("LastFilePath").toString();
    if (lastPath == "") {
        lastPath = LASTPATH;
    }
    QString filePath;
    if (isDir) {
        filePath = QFileDialog::getExistingDirectory(parent, title, lastPath);
    } else {
        if (isSave) {
            filePath = QFileDialog::getSaveFileName(parent, title, lastPath, suffixs);
        } else {
            filePath = isMulti ? QFileDialog::getOpenFileNames(parent, title, lastPath, suffixs).join(" ")
                               : QFileDialog::getOpenFileName(parent, title, lastPath, suffixs);
        }
    }
    if (!filePath.isEmpty()) {
        setting.setValue("LastFilePath", filePath);  //记录路径到QSetting中保存
    }
    if (AppConfig::useAbsoluePath) {
        return filePath;
    } else {
        return getRelativeFilePath2ExeDir(filePath);
    }
}

QString MUTILS::string2Qstring(string tmp) { return QString(QString::fromLocal8Bit(tmp.c_str())); }

int *MUTILS::copyFromFloatArray(int *srcArray, int len) {
    int *newArray = new int[len];
    for (int i = 0; i < len; ++i) {
        newArray[i] = srcArray[i];
    }
    return newArray;
}

int MUTILS::getRandIntInRange(int low, int high) { return QRandomGenerator::system()->bounded(low, high); }

double MUTILS::getRandDoubleInRange(double low, double high) {
    return QRandomGenerator::system()->generateDouble() * high + low;
}

QList<QList<int>> MUTILS::splitN2Ranges(int N, int seqNums) {
    QList<QList<int>> ra;
    int               st = N / seqNums;
    for (int i = 0; i < seqNums; i++) {
        if (i == seqNums - 1) {
            ra << QList<int>{i * st, N - 1};
        } else {
            ra << QList<int>{i * st, (i + 1) * st - 1};
        }
    }
    return ra;
}

int **MUTILS::getNeiOffset(int neiWidth) {
    int   _numWindows = neiWidth * neiWidth - 1;
    int   i, k, f;
    int **direction = new int *[_numWindows];
    for (i = 0; i < _numWindows; i++) {
        direction[i] = new int[2];
    }
    // loop
    i = 0;
    for (k = -(neiWidth - 1) / 2; k <= (neiWidth - 1) / 2; k++) {
        for (f = -(neiWidth - 1) / 2; f <= (neiWidth - 1) / 2; f++) {
            if (!(k == 0 && f == 0)) {
                direction[i][0] = k;
                direction[i][1] = f;
                //                qDebug() << k << f;
                i++;
            }
        }
    }
    return direction;
}

float MUTILS::getTimeDiff(QTime time) {
    int   timeDiff = time.elapsed();
    float f        = timeDiff / 1000.0;
    return f;
}

bool MUTILS::isFileExist(QString fullFileName) {
    QFileInfo fileInfo(fullFileName);
    if (fileInfo.isFile()) {
        return true;
    }
    return false;
}

QString MUTILS::getFileNameByPath(QString filePath) {
    QFileInfo fi = QFileInfo(filePath);
    return fi.exists() ? fi.fileName() : "";
}

QString MUTILS::getRelativeFilePath2ExeDir(QString filePath) {
    QDir dir(QCoreApplication::applicationDirPath());
    return dir.relativeFilePath(filePath);
}

QString MUTILS::initPythonEnv(QProcess *p) {
    // python 的路径 以 anaconda为例
    QString envName       = "devEnv";                                //  anaconda中环境名称
    QString condaPath     = "F:\\software\\devSoftwares\\anaconda";  // anaconda安装路径
    QString condaEnvPath  = condaPath + "\\envs";                    // anaconda目录中保存环境的位置
    QString pythonHome    = condaEnvPath + "\\" + envName;
    QString pythonPath    = pythonHome + "\\Lib";
    QString pythonExePath = pythonHome + "\\python.exe";

    // python项目路径
    QString projectPath = "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\code\\prob";

    // 设置环境
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PYTHONHOME", pythonHome);
    env.insert("PYTHONPATH", pythonPath);
    p->setProcessEnvironment(env);

    // 设置执行时的工作目录
    p->setWorkingDirectory(projectPath);
    return pythonExePath;
}

QString MUTILS::genRandomFileName(QString prefix, QString suffix) {
    QDateTime time  = QDateTime::currentDateTime();  //获取当前时间
    int       timeT = time.toTime_t();               //将当前时间转为时间戳
    return prefix + QString::number(timeT) + suffix;
}

QColor MUTILS::hexStr2QColor(QString hexString) {
    QColor c(hexString.toUInt(NULL, 16));
    return c;
}

QString MUTILS::qColor2HexStr(QColor c) {
    QRgb    mRgb    = qRgb(c.red(), c.green(), c.blue());
    QString mRgbStr = QString::number(mRgb, 16);
    return mRgbStr;
}

QDir MUTILS::getDirFromFilePath(QString filePath) {
    QFileInfo fi(filePath);
    return fi.dir();
}

void MUTILS::saveDelete(char *p) {
    if (p) {
        delete[](p);
        (p) = NULL;
    }
}

double MUTILS::truncateDouble(double value, int num) {
    QString str = QString::number(value, 'f', num);
    return str.toDouble();
}

void MUTILS::table2ExcelByHtml(QTableWidget *table, QString title, QString excelPath) {
    //    QString fileName = QFileDialog::getSaveFileName(
    //        table, "保存", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Excel 文件(*.xls
    //        *.xlsx)");
    qDebug() << excelPath;
    QString fileName = excelPath;
    if (fileName != "") {
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application"))  //连接Excel控件
        {
            excel->dynamicCall("SetVisible (bool Visible)", "false");  //不显示窗体
            excel->setProperty("DisplayAlerts",
                false);  //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
            QAxObject *workbooks = excel->querySubObject("WorkBooks");       //获取工作簿集合
            workbooks->dynamicCall("Add");                                   //新建一个工作簿
            QAxObject *workbook  = excel->querySubObject("ActiveWorkBook");  //获取当前工作簿
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            int i, j;
            // QTablewidget 获取数据的列数
            int colcount = table->columnCount();
            // QTablewidget 获取数据的行数
            int rowcount = table->rowCount();

            // QTableView 获取列数
            // int colount=ui->tableview->model->columnCount();
            // QTableView 获取行数
            // int rowcount=ui->tableview->model->rowCount();

            QAxObject *cell, *col;
            //标题行
            cell = worksheet->querySubObject("Cells(int,int)", 1, 1);
            cell->dynamicCall("SetValue(const QString&)", title);
            cell->querySubObject("Font")->setProperty("Size", 18);
            //调整行高
            worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
            //合并标题行
            QString cellTitle;
            cellTitle.append("A1:");
            cellTitle.append(QChar(colcount - 1 + 'A'));
            cellTitle.append(QString::number(1));
            QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
            range->setProperty("WrapText", true);
            range->setProperty("MergeCells", true);
            range->setProperty("HorizontalAlignment", -4108);  // xlCenter
            range->setProperty("VerticalAlignment", -4108);    // xlCenter
            //列标题
            for (i = 1; i < colcount; i++) {
                QString columnName;
                columnName.append(QChar(i + 'A'));
                columnName.append(":");
                columnName.append(QChar(i + 'A'));
                col = worksheet->querySubObject("Columns(const QString&)", columnName);
                col->setProperty("ColumnWidth", table->columnWidth(i) / 6);
                cell = worksheet->querySubObject("Cells(int,int)", 2, i + 1);
                // QTableWidget 获取表格头部文字信息
                columnName = table->horizontalHeaderItem(i)->text();
                // QTableView 获取表格头部文字信息
                // columnName=ui->tableView_right->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
                cell->dynamicCall("SetValue(const QString&)", columnName);
                cell->querySubObject("Font")->setProperty("Bold", true);
                cell->querySubObject("Interior")->setProperty("Color", QColor(191, 191, 191));
                cell->setProperty("HorizontalAlignment", -4108);  // xlCenter
                cell->setProperty("VerticalAlignment", -4108);    // xlCenter
            }

            //数据区

            // QTableWidget 获取表格数据部分
            for (i = 0; i < rowcount; i++) {
                for (j = 1; j < colcount; j++) {
                    worksheet->querySubObject("Cells(int,int)", i + 3, j + 1)
                        ->dynamicCall("SetValue(const QString&)", table->item(i, j) ? table->item(i, j)->text() : "");
                }
            }

            // QTableView 获取表格数据部分
            //  for(i=0;i<rowcount;i++) //行数
            //     {
            //         for (j=0;j<colcount;j++)   //列数
            //         {
            //             QModelIndex index = ui->tableView_right->model()->index(i, j);
            //             QString strdata=ui->tableView_right->model()->data(index).toString();
            //             worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const
            //             QString&)", strdata);
            //         }
            //     }

            //画框线
            QString lrange;
            lrange.append("A2:");
            lrange.append(colcount - 1 + 'A');
            lrange.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", lrange);
            range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
            range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
            //调整数据区行高
            QString rowsName;
            rowsName.append("2:");
            rowsName.append(QString::number(table->rowCount() + 2));
            range = worksheet->querySubObject("Range(const QString&)", rowsName);
            range->setProperty("RowHeight", 20);
            workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName));  //保存至fileName
            //            workbook->dynamicCall("SaveAs(const QString&)", fileName);  //保存至fileName
            workbook->dynamicCall("Close()");  //关闭工作簿
            excel->dynamicCall("Quit()");      //关闭excel
            delete excel;
            excel = NULL;
            // QMessageBox::information(this,tr("提示"),tr("数据已保存"));
            //            if (QMessageBox::question(NULL, QString::fromLocal8Bit("完成"),
            //                    QString::fromLocal8Bit("文件已经导出，是否现在打开？"), QMessageBox::Yes |
            //                    QMessageBox::No)
            //                == QMessageBox::Yes) {
            //                QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
            //            }
        } else {
            QMessageBox::warning(NULL, "错误", "未能创建 Excel 对象，请安装 Microsoft Excel。", QMessageBox::Apply);
        }
    }
}

QStringList MUTILS::getSubDirName(QString dirPath)
{
//    qDebug() << "curr ==> "<< QDir::currentPath();
    QDir dir(dirPath);
    QStringList dirNameList;
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
    foreach (auto fi, fileList) {
        if (fi.isDir()) {
            dirNameList << fi.fileName();
        }
    }
    return dirNameList;
}
