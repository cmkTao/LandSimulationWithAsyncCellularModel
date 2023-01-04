#include "cleanlandusedialog.h"

#include "ui_cleanlandusedialog.h"

CleanLandUseDialog::CleanLandUseDialog(QWidget *parent) : QDialog(parent), ui(new Ui::cleanLandUseDialog) {
    ui->setupUi(this);
}

CleanLandUseDialog::~CleanLandUseDialog() { delete ui; }

void CleanLandUseDialog::on_pushButton_2_clicked() {
    startTif
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择需要清洗的数据..."), false, "Text File(*.tif)");
    ui->le_start->setText(startTif);
}

void CleanLandUseDialog::on_pushButton_3_clicked() {
    targetTif = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择参照数据..."), false, "Text File(*.tif)");
    ui->le_target->setText(targetTif);
}

void CleanLandUseDialog::setMSGFromThread2UI(QString msg) { ui->te_res->append(msg); }

void CleanLandUseDialog::slotProcessFinshed() { ui->te_res->append(QString::fromLocal8Bit("清洗完毕!!!")); }

void CleanLandUseDialog::createThread() {
    cdt = new CleanLandDataThread(0, ui->le_start->text(), ui->le_target->text(), ui->le_save->text());
    // 连接线程和UI的通信机制
    connect(cdt, SIGNAL(isDone()), this, SLOT(slotProcessFinshed()));
    connect(cdt, SIGNAL(signalSendMessage(QString)), this, SLOT(setMSGFromThread2UI(QString)));
}

void CleanLandUseDialog::on_pushButton_5_clicked() {
    saveTif
        = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择保存路径..."), false, "Text File(*.tif)", true);
    ui->le_save->setText(saveTif);
}

void CleanLandUseDialog::on_pushButton_4_clicked() {
    createThread();
    this->cdt->start();
}
