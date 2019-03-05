#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include "reports/reportclass.h"
#include "reports/shiftreport.h"

namespace Ui {
class reportDialog;
}

class reportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit reportDialog(QWidget *parent = 0);
    ~reportDialog();
    void showReport(reportClass *report);

protected:
    void showReportShift(shiftReport *report);
    reportClass *currentReport;


private:
    Ui::reportDialog *ui;
};

#endif // REPORTDIALOG_H
