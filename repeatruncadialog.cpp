#include "repeatruncadialog.h"
#include "ui_repeatruncadialog.h"

RepeatRunCADialog::RepeatRunCADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RepeatRunCADialog)
{
    ui->setupUi(this);
}

RepeatRunCADialog::~RepeatRunCADialog()
{
    delete ui;
}
