#ifndef CLEANDATADIALOG_H
#define CLEANDATADIALOG_H

#include <QDialog>

#include "alglib/cleandatathread.h"
#include "entity/tifdataentity.h"
#include "utils/mutils.h"
#include "utils/tifTools.h"

namespace Ui {
class CleanDataDialog;
}

class CleanDataDialog : public QDialog {
    Q_OBJECT

public:
    explicit CleanDataDialog(QWidget *parent = nullptr);
    ~CleanDataDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void setMSGFromThread2UI(QString msg);
    void slotProcessFinshed();
    void setProcess2Bar(int, int);
    void setMaxIterNum(int);

private:
    void createThread();

    Ui::CleanDataDialog *ui;

    CleanDataThread *cdt;
};

#endif  // CLEANDATADIALOG_H
