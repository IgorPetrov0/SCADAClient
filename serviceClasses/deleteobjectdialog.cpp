#include "deleteobjectdialog.h"
#include "ui_deleteobjectdialog.h"

deleteObjectDialog::deleteObjectDialog(QWidget *parent, object *ob) :
    QDialog(parent),
    ui(new Ui::deleteObjectDialog)
{
    ui->setupUi(this);
    ui->nameLine->setText(ob->getName());
    ui->addressLine->setText(QString::number(ob->getAddress()));
    ui->descriptionText->document()->setPlainText(ob->getDescription());
    ui->typeLine->setText(ob->getTypeString());

    connect(ui->deleteAllButton,SIGNAL(clicked(bool)),this,SLOT(deleteAllSlot()));
    connect(ui->deleteObjectOnlyButton,SIGNAL(clicked(bool)),this,SLOT(deleteObjectOnlySlot()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
}
/////////////////////////////////////////////////////////////////////////
deleteObjectDialog::~deleteObjectDialog()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////////////
void deleteObjectDialog::deleteObjectOnlySlot(){
    done(DELETE_OBJECT_ONLY);
}
///////////////////////////////////////////////////////////////////////////
void deleteObjectDialog::deleteAllSlot(){
    done(DELETE_ALL);
}
