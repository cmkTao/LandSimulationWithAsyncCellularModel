#include "genprobimagedialog.h"

#include "ui_genprobimagedialog.h"

GenProbImageDialog::GenProbImageDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GenProbImageDialog) {
    ui->setupUi(this);
}

GenProbImageDialog::~GenProbImageDialog() { delete ui; }

void GenProbImageDialog::on_pushButton_clicked() {
    // 构造运行所需参数，保存到临时json文件中
    Json::Value root;
    if (landUseFilePath == "" || saveDir == "") {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("选择文件路径/保存路径！！！"));
        return;
    }

    root["landPath"] = Json::Value(ui->le_landPath->text().toStdString());
    root["saveDir"]  = Json::Value(ui->le_dir->text().toStdString());

    QString types = "";
    if (ui->cb_One->isChecked()) {
        types.append("1,");
    }
    if (ui->cb_Random->isChecked()) {
        types.append("2,");
    }
    if (ui->cb_NormalRandom->isChecked()) {
        types.append("3,");
    }
    if (types == "") {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("至少选择一个生成方式！！！"));
        return;
    }
    types.remove(types.length() - 1, 1);  //去除最后一个逗号

    root["probTypes"] = Json::Value(types.toStdString());
    root["twoYears"]  = Json::Value(ui->rb_one->isChecked() ? 1 : 2);
    QString jsonPath  = saveDir + "/" + MUTILS::genRandomFileName("genProb", ".json");
    //输出到文件
    ofstream           os;
    Json::StyledWriter sw;
    os.open(jsonPath.toStdString());
    os << sw.write(root);
    os.close();

    // 调用python程序
    ui->textEdit->clear();
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    m_process->setReadChannel(QProcess::StandardOutput);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setRes2Te()));
    //    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotProcessFinshed()));

    // 运行本地的python脚本
    QString pythonExePath = MUTILS::initPythonEnv(m_process);  // 初始化环境
    // 构造执行参数
    QStringList params;
    params << MUTILS::PYTHONSCRIPTPATH << "--mode=genProb"
           << "--config=" + jsonPath;
    qDebug() << params;
    m_process->start(pythonExePath, params);
}

void GenProbImageDialog::setRes2Te() {
    QByteArray qbt = m_process->readAllStandardOutput();
    QString    msg = QString::fromLocal8Bit(qbt);
    ui->textEdit->append(msg);
    ui->textEdit->update();
}

void GenProbImageDialog::on_pushButton_2_clicked() {
    landUseFilePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择土地利用数据..."), false, "Text File(*.tif)");
    if (landUseFilePath == "") {
        return;
    }
    ui->le_landPath->setText(landUseFilePath);
}

void GenProbImageDialog::on_pushButton_3_clicked() {
    saveDir = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择图像保存目录..."), true, "");
    if (saveDir == "") {
        return;
    }
    ui->le_dir->setText(saveDir);
}
