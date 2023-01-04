#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <utils/constValue.h>
#include <utils/global.h>
#include "utils/appconfig.h"

#include <QButtonGroup>
#include <QFileDialog>
#include <QMainWindow>s
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void radioBtnSlot();
    void openTif();
    void openDiffDialog();
    void openANNDialog();
    void openCADialog();
    void openEvalDialog();
    void openCleanDialog();
    void openCleanLandDialog();
    void openGenProbImageDialog();
    void openBatchSimDialog();
    void openDuplicateConfigDialog();
    void areasChoiceSlot();

    void on_btn_open_clicked();

    void on_btn_ana_clicked();

    void on_btn_ANN_clicked();

    void on_btn_CA_clicked();

    void on_btn_CA_2_clicked();

    void on_btn_cleanData_clicked();

private:
    void enableRegion(bool flag);
    // attribute
    Ui::MainWindow *ui;

    // functions
    void connectSlots();

    void loadAppConfig();

    void loadSimulationConfig();

    QButtonGroup *groupButton1;

    QString m_defaultConfigPath;
    QString m_area;
};
#endif  // MAINWINDOW_H
