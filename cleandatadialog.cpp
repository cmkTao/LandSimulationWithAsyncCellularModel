#include "cleandatadialog.h"

#include "ui_cleandatadialog.h"

CleanDataDialog::CleanDataDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CleanDataDialog) {
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit("清洗数据"));
}

CleanDataDialog::~CleanDataDialog() { delete ui; }

void CleanDataDialog::on_pushButton_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择输入驱动力目录...", true);
    if (filePath == "") {
        return;
    }
    ui->le_in_dir->setText(filePath);
}

void CleanDataDialog::on_pushButton_2_clicked() {
    QString filePath;
    filePath = MUTILS::getFileFromDialog(this, "选择输出驱动力目录...", true);
    if (filePath == "") {
        return;
    }
    ui->le_out_dir->setText(filePath);
}

void CleanDataDialog::on_pushButton_3_clicked() {
    QString filePath;
    filePath
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择土地利用数据..."), false, "Text File(*.tif)");
    if (filePath == "") {
        return;
    }
    ui->le_landUsePath->setText(filePath);
}

void CleanDataDialog::on_pushButton_4_clicked() {
    ui->textEdit->clear();
    createThread();
    ui->pushButton_4->setEnabled(false);
    this->cdt->start();
}

void CleanDataDialog::setMSGFromThread2UI(QString msg) { ui->textEdit->append(msg); }

void CleanDataDialog::slotProcessFinshed() {
    ui->textEdit->append(QString::fromLocal8Bit("清洗完毕!!!"));
    ui->pushButton_4->setEnabled(true);
}

void CleanDataDialog::setProcess2Bar(int k, int m) { ui->progressBar->setValue(k); }

void CleanDataDialog::setMaxIterNum(int k) { ui->progressBar->setMaximum(k); }

void CleanDataDialog::createThread() {
    cdt = new CleanDataThread(
        0, ui->le_in_dir->text(), ui->le_out_dir->text(), ui->le_landUsePath->text(), ui->spinBox->value());
    // 连接线程和UI的通信机制
    connect(cdt, SIGNAL(isDone()), this, SLOT(slotProcessFinshed()));
    connect(cdt, SIGNAL(signalSendMessage(QString)), this, SLOT(setMSGFromThread2UI(QString)));
    connect(cdt, SIGNAL(signalSendProcess(int, int)), this, SLOT(setProcess2Bar(int, int)));
    connect(cdt, SIGNAL(signalSendMaxIterNum(int)), this, SLOT(setMaxIterNum(int)));
}
