#ifndef CLEANLANDUSEDIALOG_H
#define CLEANLANDUSEDIALOG_H

#include <QDialog>

#include "alglib/cleanlanddatathread.h"
#include "utils/mutils.h"

namespace Ui {
class cleanLandUseDialog;
}

class CleanLandUseDialog : public QDialog {
    Q_OBJECT

public:
    explicit CleanLandUseDialog(QWidget *parent = nullptr);
    ~CleanLandUseDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void setMSGFromThread2UI(QString msg);
    void slotProcessFinshed();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::cleanLandUseDialog *ui;
    void                    createThread();
    CleanLandDataThread *   cdt;
    QString                 startTif;
    QString                 targetTif;
    QString                 saveTif;
};

#endif  // CLEANLANDUSEDIALOG_H
