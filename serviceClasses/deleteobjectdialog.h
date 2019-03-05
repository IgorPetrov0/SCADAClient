#ifndef DELETEOBJECTDIALOG_H
#define DELETEOBJECTDIALOG_H

#include <QDialog>
#include "object.h"

enum deleteVAriants{
    DELETE_ALL=2,
    DELETE_OBJECT_ONLY
};


namespace Ui {
class deleteObjectDialog;
}

class deleteObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteObjectDialog(QWidget *parent, object *ob);
    ~deleteObjectDialog();


protected slots:
    void deleteObjectOnlySlot();
    void deleteAllSlot();

private:
    Ui::deleteObjectDialog *ui;
};

#endif // DELETEOBJECTDIALOG_H
