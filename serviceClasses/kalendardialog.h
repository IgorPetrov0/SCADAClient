#ifndef KALENDARDIALOG_H
#define KALENDARDIALOG_H

#include <QDialog>

namespace Ui {
class kalendarDialog;
}

class kalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit kalendarDialog(QWidget *parent = 0);
    ~kalendarDialog();
    QDate getStartDate();
    QDate getStopDate();


protected slots:
    void startDateSelectedSlot();
    void stopDateSelectedSlot();


private:
    Ui::kalendarDialog *ui;
};

#endif // KALENDARDIALOG_H
