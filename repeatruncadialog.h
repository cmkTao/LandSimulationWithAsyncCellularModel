#ifndef REPEATRUNCADIALOG_H
#define REPEATRUNCADIALOG_H

#include <QDialog>

namespace Ui {
class RepeatRunCADialog;
}

class RepeatRunCADialog : public QDialog
{
    Q_OBJECT

public:
    explicit RepeatRunCADialog(QWidget *parent = nullptr);
    ~RepeatRunCADialog();

private:
    Ui::RepeatRunCADialog *ui;
};

#endif // REPEATRUNCADIALOG_H
